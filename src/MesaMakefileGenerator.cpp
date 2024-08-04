#include "Mesa.h"
#include "MesaGenerator.h"
#include "MesaUtils.h"

Mesa::Generator::Generator() = default;

std::string Mesa::MakefileGenerator::generate(std::shared_ptr<Workspace> workspace) {
    LOG("Generating Makefile for workspace...\n");

    std::string compilerPath;

    if (workspace->properties.count(Property::CompilerName) == 0) {
        LOG("No compiler set!");
        std::exit(0);
    }

    LOG("Checking for compiler: %s\n",
        workspace->properties[Property::CompilerName].c_str());

    std::vector<std::string> compilers =
            workspace->compilers.at(workspace->properties[Property::CompilerName]);

    bool fComp = false;
    for (auto &compiler: compilers) {
        LOG("Checking for compiler at: %s\n", compiler.c_str());
        if (std::filesystem::exists(compiler)) {
            LOG("Using compiler at: %s\n", compiler.c_str());

            compilerPath = compiler;
            fComp = true;

            break;
        }
    }

    if (!fComp) {
        LOG("Could not find a suitable compiler to use...");
        std::exit(EXIT_FAILURE);
    }

    std::string binDir, cxxVersion;

    if (workspace->properties.find(Property::BuildDirectory) ==
        workspace->properties.end()) {
        LOG("No build directory set, using bin as default!");

        binDir = "bin";
    } else {
        binDir = workspace->properties[Property::BuildDirectory];
    }

    if (workspace->properties.find(Property::CXXVersion) == workspace->properties.end()) {
        LOG("No C++ standard set, using 11 as default!");

        cxxVersion = "11";
    } else {
        cxxVersion = workspace->properties[Property::CXXVersion];
    }

    bool enableColor = false;

    if (workspace->properties.find(Property::EnableColor) != workspace->properties.end()) {
        enableColor = workspace->properties[Property::EnableColor] == "true" ? true : false;
    }

    std::string result = "# This Makefile was generated by Mesa v2.1\n";
    result += "# Generation Date: " + std::to_string(std::time(nullptr)) + "\n";
    result += "# DO NOT EDIT THIS FILE AS IT WILL BE RE-GENERATED\n\n";

    result += "################### VARIABLES ###################\n\n";

    if (enableColor) {
        result += "COLOR_RED := $(shell echo -e \"\\033[31m\")\n";
        result += "COLOR_GREEN := $(shell echo -e \"\\033[33m\")\n";
        result += "COLOR_BLUE := $(shell echo -e \"\\033[34m\")\n";
        result += "COLOR_CYAN := $(shell echo -e \"\\033[36m\")\n";
        result += "COLOR_NORM := $(shell echo -e \"\\033[0\\;39m\")\n\n";
        result += "STYLE_ITALIC := $(shell echo -e \"\\033[3m\")\n";
        result += "STYLE_ULINE := $(shell echo -e \"\\033[4m\")\n";
        result += "STYLE_NORM := $(shell echo -e \"\\033[0m\")\n";
    }

    result += "CXX := " + Util_EscapeString(compilerPath) + "\n";
    result += "I_CPPFLAGS := -DMESA_BUILD\n";
    result += "BIN_DIR := " + binDir + "\n";
    result += "OBJ_DIR := $(BIN_DIR)/objs\n";

    for (auto &project: workspace->projects) {
        if (project->isCMake) continue;


        std::string defines;
        std::string includeDirs;
        std::string linkOpts = "-L$(BIN_DIR) " + project->linkOptions;
        std::string staticLibs;
        std::string sharedLibs;

        for (auto &lib: project->sharedLibraries) {
            std::string libPath = lib;

            sharedLibs += "$(BIN_DIR)/" + libPath + " ";
        }

        for (auto &lib: project->staticLibraries) {
            std::string libPath = lib;
            staticLibs += "$(BIN_DIR)/" + libPath + " ";
        }

        for (auto &opt: project->compilerDefines) {
            defines += "-D" + opt.first + "=" + opt.second + " ";
        }

        for (auto &include: project->includeDirectories) {
            defines += "-I" + include.generic_string() + " ";
            includeDirs += "$(wildcard " + include.generic_string() +
                           "/*.h) $(wildcard " + include.generic_string() + "/*.hpp) ";
        }

        if (project->buildType == BuildType::SharedLibrary) {
            defines += " -fPIC ";
        }

        defines = Util_TrimString(defines);
        includeDirs = Util_TrimString(includeDirs);
        linkOpts = Util_TrimString(linkOpts);

        std::string cxxVersionFlag = "-std=c++" + cxxVersion;

        result +=
                Util_FixString(project->name) + "_INCDIRS := " + includeDirs + "\n";

        result += Util_FixString(project->name) + "_CPPFLAGS := " + defines + " " +
                  project->compilerOptions + cxxVersionFlag + "\n";

        result += Util_FixString(project->name) + "_LDFLAGS := " + linkOpts + "\n";

        result += Util_FixString(project->name) + "_STATIC_LIBS := " + staticLibs + "\n";

        result += Util_FixString(project->name) + "_DYN_LIBS := " + sharedLibs + "\n";
    }

    result += "\n################### PROJECTS ###################\n\n";

    std::string projectList;
    for (auto &project: workspace->projects) {
        if (project->isCMake) continue;

        projectList += Util_FixString(project->name) + " ";
    }

    result += "all: " + projectList + "\n\n";
    result += "clean:\n";
    result += "\t@echo $(COLOR_BLUE)[RM]$(COLOR_NORM) Purging contents of $(STYLE_ULINE)$(BIN_DIR)/objs/$(STYLE_NORM)\n";
    result += "\t@rm -rf $(BIN_DIR)/objs/*\n\n";
    result += "Prep:\n";
    result += "\t@echo $(COLOR_BLUE)[MKDIR]$(COLOR_NORM) Creating $(STYLE_ULINE)$(OBJ_DIR)$(STYLE_NORM)\n";
    result += "\t@mkdir -p $(OBJ_DIR)\n";

    for (auto &project: workspace->projects) {
        if (project->isCMake) continue;

        result += "\t@mkdir -p $(OBJ_DIR)/" + Util_FixString(project->name) + "\n";
    }

    result += "\n";

    result += "projects:\n";
    result += "\t@echo \"### Project List ###\"\n";

    for (auto &project: workspace->projects) {
        if (project->isCMake) continue;

        std::string type;

        switch (project->buildType) {
            case BuildType::Executable:
                type = "EXE";
                break;
            case BuildType::SharedLibrary:
                type = "DLL";
                break;
            case BuildType::StaticLibrary:
                type = "LIB";
                break;
        }

        result += "\t@echo \"\t* [" + type + "] '" + project->name + "' > $(BIN_DIR)/" + project->outputName + "\"\n";

        for (auto &pkg: project->packageList) {
            result += "\t@echo \"\t\t* Requires: $(STYLE_ITALIC)'" + pkg + "'$(STYLE_NORM)\"\n";
        }
    }

    result += "\n";

    for (auto &project: workspace->projects) {
        if (project->isCMake) continue;

        std::string fileList;

        for (auto &file: project->files) {
            fileList += file.generic_string() + " ";
        }

        std::vector<std::filesystem::path> objectFiles;
        std::string objFileListBlob;
        std::string objDir = "$(OBJ_DIR)/" + Util_FixString(project->name);

        for (auto &file: project->files) {
            objFileListBlob +=
                    objDir + "/" + Util_FixString(file.generic_string()) + ".o ";
        }

        // Generate compile steps for each source code file
        BuildType buildType = project->buildType;

        for (auto &file: project->files) {
            std::string objFileName = Util_FixString(file.generic_string()) + ".o";
            std::string projectCppFlags =
                    "$(" + Util_FixString(project->name) + "_CPPFLAGS)";
            std::string projectIncDirs =
                    "$(" + Util_FixString(project->name) + "_INCDIRS)";

            result += objDir + "/" + objFileName + ": " + file.generic_string() +
                      " " + projectIncDirs + "\n";
            result += "\t@echo $(COLOR_BLUE)[CXX]$(COLOR_NORM) " + file.generic_string() + "\n";
            result += "\t@$(CXX) $(CPPFLAGS) " + projectCppFlags +
                      " $(I_CPPFLAGS) -c " + file.generic_string() + " -o " + objDir +
                      "/" + objFileName + "\n";
            result += "\n";

            objectFiles.push_back(objFileName);
        }

        std::string outName = Util_EscapeString(project->outputName);
        if (outName.empty()) {
            LOG("Output name for project %s is empty!\n", project->name.c_str());

            std::exit(EXIT_FAILURE);
        }

        if (buildType == BuildType::SharedLibrary) {
            outName = "lib" + outName;
#if defined(_WIN32)
            outName += ".dll";
#elif defined(__unix__)
            outName += ".so";
#endif
        } else if (buildType == BuildType::Executable) {
#if defined(_WIN32)
            outName += ".exe";
#endif
        } else if (buildType == BuildType::StaticLibrary) {
#if defined(_WIN32)
            outName += ".lib";
#elif defined(__unix)
            outName += ".a";
#endif
        }

        result +=
                Util_FixString(project->name) + ": Prep " + objFileListBlob + "\n";

        std::string type;

        switch (buildType) {
            case BuildType::Executable:
                type = "EXE";
                break;
            case BuildType::SharedLibrary:
                type = "DLL";
                break;
            case BuildType::StaticLibrary:
                type = "LIB";
                break;
        }

        result += "\t@echo $(COLOR_GREEN)[" + type + "]$(COLOR_NORM) Linking " + project->name + " \\> $(STYLE_ULINE)$(BIN_DIR)/" +
                  outName + "$(STYLE_NORM)\n";

        std::string projectLdFlags = "$(" + Util_FixString(project->name) + "_LDFLAGS)";
        std::string projectStaticLibs = "$(" + Util_FixString(project->name) + "_STATIC_LIBS)";
        std::string projectDynLibs = "$(" + Util_FixString(project->name) + "_DYN_LIBS)";

        std::string rPath = " -Wl,-rpath $(BIN_DIR) ";

        if (buildType == BuildType::Executable) {
            result +=
                    "\t@$(CXX) -o $(BIN_DIR)/" + outName + " " + objFileListBlob + " " + projectLdFlags + " " + projectStaticLibs +  rPath + projectDynLibs + "\n";
        } else if (buildType == BuildType::StaticLibrary) {
            result += "\t@ar rcs $(BIN_DIR)/" + outName + " " + objFileListBlob;
        } else {
            result += "\t@$(CXX) -shared -Wl,-soname," + outName + " -o $(BIN_DIR)/" + outName + " " + objFileListBlob + " " + projectLdFlags + " -Wl,--whole-archive " + projectStaticLibs + " -Wl,--no-whole-archive\n";
        }

        result += "\n";
    }

    result += "\n";

    std::string phonyExtra;
    for (auto &task: workspace->tasks) {
        result += "task\\:" + task.first + ":\n";
        result += "\t@echo \"[TASK] Running task '" + task.first + "'\"\n";
        result += "\t@$(shell " + task.second + ")\n";

        phonyExtra += task.first + " ";

        result += "\n";
    }

    result += "tasks:\n";
    result += "\t@echo \"### Task List: ###\"\n";

    for (auto &task: workspace->tasks) {
        result += "\t@echo \"\t* " + task.first + "\"\n";
    }

    result += "\n";

    /*
    make --always-make --dry-run \
 | grep -wE 'gcc|g\+\+|c\+\+' \
 | grep -w '\-c' \
 | jq -nR '[inputs|{directory:".", command:., file: match(" [^ ]+$").string[1:]}]' \
    */

    result += ".ONESHELL:\ncompdb:\n";
    result += "\tmake --always-make --dry-run \\\n";
    result += "\t| grep -wE 'clang|clang\\+\\+' \\\n";
    result += "\t| grep -w '\\-c' \\\n";
    result += "\t| jq -nR '[inputs|{directory:\".\", command:., file: match(\" [^ ]+$$\").string[1:]}]' > compile_commands.json";
    result += "\n";

    result += ".PHONY: clean compdb " + phonyExtra + "\n";

    return result;
}
