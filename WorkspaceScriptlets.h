#pragma once
#include "MesaScriptlet.h"

namespace Mesa {
    class WorkspaceNameScriptlet : public Scriptlet {
    public:
        WorkspaceNameScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

    class VariableScriptlet : public Scriptlet {
    public:
        VariableScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

    class ImportScriptlet : public Scriptlet {
    public:
        ImportScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

    class PropertyScriptlet : public Scriptlet {
    public:
        PropertyScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };
}// namespace Mesa