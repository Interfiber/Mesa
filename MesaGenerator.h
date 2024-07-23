#pragma once
#include "Mesa.h"
#include <memory>
#include <string>

namespace Mesa {
class Generator {
public:
  Generator();

  virtual std::string generate(std::shared_ptr<Workspace> workspace) = 0;
};

/**
 * Converts a processed Mesa workspace into a GNU Makefile
 */
class MakefileGenerator : public Generator {
public:
  MakefileGenerator() = default;

  std::string generate(std::shared_ptr<Workspace> workspace) override;
};
}; // namespace Mesa