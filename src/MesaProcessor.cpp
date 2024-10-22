#include "MesaProcessor.h"
#include "CMakeScriptlets.h"
#include "MesaUtils.h"
#include "ProjectScriptlets.h"
#include "StdScriptlets.h"
#include "WorkspaceScriptlets.h"

using namespace Mesa;

Processor::Processor(const ParsedFile &file) {
    m_file = file;

    addScriptlet<WorkspaceNameScriptlet>();
    addScriptlet<VariableScriptlet>();
    addScriptlet<ImportScriptlet>();

    addScriptlet<ProjectScriptlet>();
    addScriptlet<IncludeScriptlet>();
    addScriptlet<CompilerDefineScriptlet>();
    addScriptlet<FileScriptlet>();

    addScriptlet<DefineCompilerScriptlet>();
    addScriptlet<PropertyScriptlet>();
    addScriptlet<ConfigScriptlet>();
    addScriptlet<PackageScriptlet>();
    addScriptlet<TaskScriptlet>();

    addScriptlet<ImportCMakeScriptlet>();
    addScriptlet<PackageCMakeScriptlet>();
}

std::shared_ptr<Workspace> Processor::buildWorkspace() {
    std::shared_ptr<Workspace> workspace = std::make_shared<Workspace>();

    // Set default variables
    workspace->variables.insert(
            {"CTime.UnixTimestamp", std::to_string(std::time(nullptr))});

    auto tm = std::time(nullptr);

    char *dt = (char *) malloc(26 * sizeof(char));
    if (dt == nullptr)
        abort();

#if defined(_WIN32)
    ctime_s(dt, 26, &tm);
#elif defined(__unix__)
    ctime_r(&tm, dt);
#endif

    std::string formattedTime(dt);
    formattedTime = Util_TrimString(formattedTime);
    formattedTime = Util_EscapeString(formattedTime);
    if (formattedTime.back() == '\n')
        formattedTime.pop_back();

    workspace->variables.insert({"CTime.Formatted", formattedTime});

    free(dt);

    for (auto &statement: m_file.statements) {
        if (statement.value.empty())
            continue;

        bool f = false;

        for (auto &scriptlet: m_scriptlets) {
            if (scriptlet->name == statement.key) {
                scriptlet->onRun(workspace, statement.value);
                f = true;

                break;
            }
        }

        if (!f) {
            LOG("Failed to find scriptlet for: %s", statement.key.c_str());

            std::exit(EXIT_FAILURE);
        }
    }

    return workspace;
}

void Mesa::Processor::buildProject(std::shared_ptr<Workspace> workspace) {
    for (auto &statement: m_file.statements) {
        if (statement.value.empty())
            continue;

        bool f = false;

        for (auto &scriptlet: m_scriptlets) {
            if (scriptlet->name == statement.key && scriptlet->isProjectIsolated) {
                scriptlet->onRun(workspace, statement.value);
                f = true;

                break;
            }
        }

        if (!f) {
            LOG("Failed to find scriptlet for: %s", statement.key.c_str());

            std::exit(EXIT_FAILURE);
        }
    }
}
