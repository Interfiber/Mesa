#pragma once
#include "MesaScriptlet.h"

namespace Mesa {
    class PackagePkgConfigScriptlet : public Scriptlet {
    public:
        PackagePkgConfigScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

};