#pragma once
#include "MesaScriptlet.h"

namespace Mesa {

    class ImportCMakeScriptlet : public Scriptlet {
    public:
        ImportCMakeScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

    class PackageCMakeScriptlet : public Scriptlet {
    public:
        PackageCMakeScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

};// namespace Mesa