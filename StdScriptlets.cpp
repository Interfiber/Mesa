#include "StdScriptlets.h"
#include "MesaUtils.h"

Mesa::DefineCompilerScriptlet::DefineCompilerScriptlet() {
  name = "DefineCompiler";
  isProjectIsolated = true;
}

void Mesa::DefineCompilerScriptlet::onRun(std::shared_ptr<Workspace> workspace,
                                          const std::string &value) {
  auto &compilers = workspace->compilers;

  std::string k, v;

  bool writeToV = false;

  for (char cChar : value) {
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

  if (compilers.count(k) == 0) {
    compilers.insert({k, {}});
  }

  compilers[k].push_back(v);

  LOG("Added new compiler: %s = %s\n", k.c_str(), v.c_str());
}