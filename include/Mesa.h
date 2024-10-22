#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Base Mesa data types

namespace Mesa {
    // Faster, and less log spam
    const std::string preferredCMakeGenerator = "Ninja";
    
    enum class Property { CompilerName,
                          BuildDirectory, EnableColor, CXXVersion };

    enum class Config { OutputName,
                        BuildType, OptimizationMode, WarningMode, ErrorMode, EnableDebugSymbols };

    enum class BuildType { Executable,
                           SharedLibrary,
                           StaticLibrary };

    /**
     * List of paths for data projects to be located
     */
    static std::vector<std::filesystem::path> librarySearchPaths = {
        "/usr/share/Mesa/Library",
        "/usr/local/share/Mesa/Library",
        "/Mesa/Library",
        "./Library"
    };

    class Project {
    public:
        Project() = default;

        std::string name;
        std::filesystem::path rootDir;
        std::string outputName;

        bool isCMake = false;

        BuildType buildType = BuildType::Executable;

        std::unordered_map<std::string, std::string> compilerDefines;
        std::string linkOptions;
        std::string compilerOptions;


        std::vector<std::string> packageList;
        std::vector<std::filesystem::path> files;
        std::vector<std::filesystem::path> sharedLibraries;
        std::vector<std::filesystem::path> staticLibraries;
        std::vector<std::filesystem::path> includeDirectories;
    };

    class Workspace {
    public:
        Workspace() = default;

        std::string name;
        std::filesystem::path rootDir;

        int currentProject = -1;

        std::unordered_map<Property, std::string> properties;
        std::vector<std::shared_ptr<Project>> projects;
        std::unordered_map<std::string, std::string> variables;
        std::unordered_map<std::string, std::vector<std::string>> compilers;
        std::unordered_map<std::string, std::string> tasks;
    };

    struct Statement {
        std::string key;
        std::string value;
    };
};// namespace Mesa
