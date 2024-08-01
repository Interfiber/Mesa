#include "ProjectScriptlets.h"
#include "Mesa.h"
#include "MesaUtils.h"
#include <cstdlib>

Mesa::ProjectScriptlet::ProjectScriptlet() {
    name = "Project";
    isProjectIsolated = true;
}

void Mesa::ProjectScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                   const std::string &value) {
    workspace->projects[workspace->currentProject]->name = value;

    LOG("Set project name to: %s\n", value.c_str());
}

Mesa::IncludeScriptlet::IncludeScriptlet() {
    name = "Include";
    isProjectIsolated = true;
}

void Mesa::IncludeScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                   const std::string &value) {
    workspace->projects[workspace->currentProject]->includeDirectories.push_back(
            Util_EvalString(workspace, value));
}

Mesa::CompilerDefineScriptlet::CompilerDefineScriptlet() {
    name = "CompilerDefine";
    isProjectIsolated = true;
}

void Mesa::CompilerDefineScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                          const std::string &value) {
    std::string k, v;

    bool writeToV = false;

    for (char cChar: value) {
        if (cChar == ' ')
            writeToV = true;

        if (writeToV) {
            v += cChar;
        } else {
            k += cChar;
        }
    }

    k = Util_TrimString(k);
    v = Util_TrimString(v);

    k = Util_EvalString(workspace, k);
    v = Util_EvalString(workspace, v);

    workspace->projects[workspace->currentProject]->compilerDefines.insert(
            {k, v});
}

Mesa::FileScriptlet::FileScriptlet() {
    name = "File";
    isProjectIsolated = true;
}

void Mesa::FileScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                const std::string &value) {
    workspace->projects[workspace->currentProject]->files.push_back(value);
}

Mesa::ConfigScriptlet::ConfigScriptlet() {
    name = "Config";
    isProjectIsolated = true;
}

void Mesa::ConfigScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                  const std::string &value) {
    std::string k, v;

    bool writeToV = false;

    for (char cChar: value) {
        if (cChar == ' ')
            writeToV = true;

        if (writeToV) {
            v += cChar;
        } else {
            k += cChar;
        }
    }

    k = Util_TrimString(k);
    v = Util_TrimString(v);

    v = Util_EvalString(workspace, v);

    if (k == "OutputName") {
        workspace->projects[workspace->currentProject]->outputName = v;
    } else if (k == "BuildType") {
        if (v == "Executable") {
            workspace->projects[workspace->currentProject]->buildType =
                    BuildType::Executable;
        } else if (v == "SharedLibrary") {
            workspace->projects[workspace->currentProject]->buildType =
                    BuildType::SharedLibrary;
        } else if (v == "StaticLibrary") {
            workspace->projects[workspace->currentProject]->buildType =
                    BuildType::StaticLibrary;
        } else {
            LOG("Invalid build type!\n");

            std::exit(EXIT_FAILURE);
        }
    } else if (k == "OptimizationMode") {
        if (v == "None") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-O0 ";
        } else if (v == "O1") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-O1 ";
        } else if (v == "O2") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-O2 ";
        } else if (v == "O3") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-O3 ";
        } else if (v == "OFast") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-Ofast ";
        } else {
            LOG("Invalid OptimizationMode of: %s\n", v.c_str());

            std::exit(EXIT_FAILURE);
        }
    } else if (k == "WarningMode") {
        if (v == "None") {
        } else if (v == "Wall") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-Wall ";
        } else {
            LOG("Invalid warning mode of: %s\n", v.c_str());
            std::exit(EXIT_FAILURE);
        }
    } else if (k == "ErrorMode") {
        if (v == "None") {
        } else if (v == "Werror") {
            workspace->projects[workspace->currentProject]->compilerOptions += "-Werror ";
        } else {
            LOG("Invalid error mode of: %s\n", v.c_str());
            std::exit(EXIT_FAILURE);
        }
    }
}

Mesa::PackageScriptlet::PackageScriptlet() {
    name = "Package";
    isProjectIsolated = true;
}

void Mesa::PackageScriptlet::onRun(std::shared_ptr<Workspace> workspace, const std::string &value) {
    bool f = false;
    for (auto &project: workspace->projects) {
        if (project->name == value) {
            std::string buildPath = project->outputName;

            if (project->buildType == BuildType::SharedLibrary) {
                workspace->projects[workspace->currentProject]->linkOptions += " -l" + buildPath;
            } else if (project->buildType == BuildType::StaticLibrary) {
                workspace->projects[workspace->currentProject]->staticLibraries.push_back(buildPath);
            } else {
                LOG("Cannot link against executable!");
                std::exit(EXIT_FAILURE);
            }

            workspace->projects[workspace->currentProject]->packageList.push_back(project->name);

            f = true;
            break;
        }
    }

    if (!f) {
        LOG("Failed to find package with name of: %s\n", value.c_str());
        std::exit(EXIT_FAILURE);
    }
}
