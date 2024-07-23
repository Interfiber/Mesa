#pragma once
#include "Mesa.h"
#include <memory>
#include <string>


namespace Mesa {
class Scriptlet {
public:
  Scriptlet() = default;

  std::string name;
  bool isProjectIsolated = false;

  virtual void onRun(std::shared_ptr<Workspace> workspace,
                     const std::string &scriptValue) = 0;
};
}; // namespace Mesa