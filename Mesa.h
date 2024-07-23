#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

// Base Mesa data types

namespace Mesa {
    enum class Property { CompilerName,
                          BuildDirectory };

    enum class Config { OutputName,
                        BuildType };

    enum class BuildType { Executable,
                           SharedLibrary,
                           StaticLibrary };

    class Project {
    public:
        Project() = default;

        std::string name;
        std::filesystem::path rootDir;
        std::string outputName;

        BuildType buildType = BuildType::Executable;

        std::unordered_map<std::string, std::string> compilerDefines;
        std::string linkOptions;
        std::string compilerOptions;

        std::vector<std::filesystem::path> files;
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
    };

    struct Statement {
        std::string key;
        std::string value;
    };
};// namespace Mesa