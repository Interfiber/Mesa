#include "CMakeScriptlets.h"
#include "Mesa.h"
#include "MesaUtils.h"
#include <cstdlib>
#include <filesystem>

Mesa::ImportCMakeScriptlet::ImportCMakeScriptlet() {
    name = "ImportCMake";
    isProjectIsolated = false;
}

void Mesa::ImportCMakeScriptlet::onRun(std::shared_ptr<Workspace> workspace, const std::string &value) {
    LOG("Importing CMake project from: %s\n", value.c_str());

    if (!std::filesystem::exists(value)) {
        LOG("Failed to import CMake project! No such file or directory!\n");

        std::exit(EXIT_FAILURE);
    }

    std::filesystem::path cmakeListsPath = std::filesystem::path(value) / std::filesystem::path("CMakeLists.txt");

    if (!std::filesystem::exists(cmakeListsPath)) {
        LOG("Failed to import CMake project! CMakeLists.txt not found at: %s\n", cmakeListsPath.c_str());

        std::exit(EXIT_FAILURE);
    }

    LOG("Configuring & building cmake project...\n\n");

    int exitCode = std::system(("/bin/bash -c 'cd " + value + "; mkdir -p .msacmakeimport; cd .msacmakeimport; cmake -G" + Mesa::preferredCMakeGenerator + " -S .. -B .; cmake --build . 2>&1'").c_str());

    if (exitCode == EXIT_FAILURE) {
        LOG("CMake configuration process failed!\n");

        std::exit(exitCode);
    }

    LOG("Creating cmake project for Mesa...\n");

    std::string projectName = std::filesystem::path(value).filename();

    workspace->projects.push_back(std::make_shared<Mesa::Project>());
    workspace->currentProject++;

    workspace->projects[workspace->currentProject]->name = "CMake:" + projectName;
    workspace->projects[workspace->currentProject]->rootDir = value + "/.msacmakeimport";
    workspace->projects[workspace->currentProject]->isCMake = true;
}

Mesa::PackageCMakeScriptlet::PackageCMakeScriptlet() {
    name = "PackageCMake";
    isProjectIsolated = true;
}

void Mesa::PackageCMakeScriptlet::onRun(std::shared_ptr<Workspace> workspace, const std::string &value) {
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

    std::string projectName = "CMake:" + k;
    std::string libName = v;

    std::filesystem::path libFile;
    bool linkStatic = false;

    for (auto &project: workspace->projects) {
        if (project->isCMake && projectName == projectName) {
#if defined(__unix__)
            libFile = project->rootDir / ("lib" + libName + ".so");
#elif defined(_WIN32)
            libFile = project->rootDir / ("lib" + libName + ".so");
#endif

            if (!std::filesystem::exists(libFile)) {
                linkStatic = true;

#if defined(__unix__)
                libFile.replace_extension(".a");
#elif defined(_WIN32)
                libFile.replace_extension(".lib");
#endif
            }

            break;
        }
    }

    if (libFile.empty() || !std::filesystem::exists(libFile)) {
        LOG("Failed to find suitable library to link against!\n");

        if (!libFile.empty()) LOG("Last checked path: %s\n", libFile.c_str());

        std::exit(EXIT_FAILURE);
    }

    std::filesystem::path linkRootDir = libFile.parent_path();
    std::filesystem::path libFinal = libFile.filename();

    // Resolve the symlink!

    std::string binDir;

    if (workspace->properties.find(Property::BuildDirectory) ==
        workspace->properties.end()) {
        LOG("No build directory set, using bin as default!");

        binDir = "bin";
    } else {
        binDir = workspace->properties[Property::BuildDirectory];
    }


    while (std::filesystem::is_symlink(libFile)) {
        libFile = std::filesystem::path(libFile.parent_path()) / std::filesystem::read_symlink(libFile);

        LOG("Resolved path to: %s\n", libFile.c_str());


        std::filesystem::path outFile(binDir / libFile.filename());

        if (std::filesystem::exists(outFile)) {
            std::filesystem::remove(outFile);
        }

        std::filesystem::copy(libFile, outFile);

        libFinal = libFile.filename();
    }

    if (!linkStatic) {
        workspace->projects[workspace->currentProject]->sharedLibraries.push_back(libFinal);
    } else {
        workspace->projects[workspace->currentProject]->staticLibraries.push_back(libFile);
    }

    std::filesystem::path outFile = std::filesystem::path(binDir) / std::filesystem::path(libFile.filename().generic_string());

    if (std::filesystem::exists(outFile)) {
        std::filesystem::remove(outFile);
    }

    std::filesystem::copy(libFile, std::filesystem::path(binDir) / std::filesystem::path(libFile.filename().generic_string()));
}
