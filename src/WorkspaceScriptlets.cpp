#include "WorkspaceScriptlets.h"
#include "Mesa.h"
#include "MesaParser.h"
#include "MesaProcessor.h"
#include "MesaUtils.h"
#include <fstream>


Mesa::WorkspaceNameScriptlet::WorkspaceNameScriptlet() { name = "Workspace"; }

void Mesa::WorkspaceNameScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                         const std::string &value) {
    workspace->name = value;

    LOG("Workspace name set to: %s\n", value.c_str());
}

Mesa::VariableScriptlet::VariableScriptlet() { name = "Variable"; }

void Mesa::VariableScriptlet::onRun(std::shared_ptr<Workspace> workspace,
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

    workspace->variables.insert({ k, Util_EvalString(workspace, v) });
}

Mesa::ImportScriptlet::ImportScriptlet() { name = "Import"; }

void Mesa::ImportScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                  const std::string &val) {
    std::string value = val;
    std::vector<std::string> split = Util_SplitString(value, ":");

    value = Util_TrimString(value);

    if (split.size() == 2) {
        if (split[0] == "data") {
            split[1] = Util_TrimString(split[1]);

            // Find library path
            std::filesystem::path libraryPath;

            for (auto &libSearchPath : Mesa::librarySearchPaths) {
                if (std::filesystem::exists(libSearchPath))  {
                    libraryPath = libSearchPath;
                    break;
                }
            }

            if (libraryPath.empty()) {
                LOG("Failed to find Library path, searched all avalible paths:\n");

                for (auto &p : Mesa::librarySearchPaths) { LOG("\t%s\n", p.c_str()); }

                std::exit(EXIT_FAILURE);
            }

            std::ifstream ifs(libraryPath / split[1]);

            std::string data;
            std::string line;

            while (std::getline(ifs, line)) {
                data += line + "\n";
            }

            Mesa::Parser parser(data);
            Mesa::ParsedFile file = parser.parse();

            Mesa::Processor processor(file);
            processor.buildProject(workspace);

            LOG("Imported data project from: %s/%s\n", libraryPath.c_str(), split[1].c_str());

            return;
        }
    }

    LOG("Importing project from: %s\n", value.c_str());

    if (!std::filesystem::exists(value)) {
        LOG("Current Working Directory = %s\n",
            std::filesystem::current_path().generic_string().c_str());
        LOG("Cannot open project file! No such file or directory!\n");

        std::exit(EXIT_FAILURE);
    }

    std::ifstream ifs(value);

    std::string data;
    std::string line;

    while (std::getline(ifs, line)) {
        data += line + "\n";
    }

    Mesa::Parser parser(data);
    Mesa::ParsedFile file = parser.parse();

    Mesa::Processor processor(file);

    workspace->projects.push_back(std::make_shared<Project>());
    workspace->currentProject = workspace->projects.size() - 1;

    processor.buildProject(workspace);
}

Mesa::PropertyScriptlet::PropertyScriptlet() { name = "Property"; }

void Mesa::PropertyScriptlet::onRun(std::shared_ptr<Workspace> workspace,
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

    if (k == "CompilerName") {
        workspace->properties.insert({Property::CompilerName, v});
    } else if (k == "BuildDirectory") {
        workspace->properties.insert({Property::BuildDirectory, v});
    } else if (k == "EnableColor") {
        workspace->properties.insert({ Property::EnableColor, v });
    } else if (k == "C++Standard") {
        workspace->properties.insert({ Property::CXXVersion, v });
    } else {
        LOG("Invalid property with name of: %s\n", k.c_str());

        std::exit(EXIT_FAILURE);
    }
}


Mesa::TaskScriptlet::TaskScriptlet() {
    name = "Task";
    isProjectIsolated = false;
}

void Mesa::TaskScriptlet::onRun(std::shared_ptr<Workspace> workspace,
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

    workspace->tasks.insert({k, v});
}