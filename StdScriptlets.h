#pragma once
#include "MesaScriptlet.h"

namespace Mesa {
    class DefineCompilerScriptlet : public Scriptlet {
    public:
        DefineCompilerScriptlet();

        void onRun(std::shared_ptr<Workspace> workspace,
                   const std::string &value) override;
    };

};// namespace Mesa