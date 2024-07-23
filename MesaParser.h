#pragma once
#include "Mesa.h"
#include <memory>
#include <string>
#include <vector>


namespace Mesa {
struct ParsedFile {
  std::vector<Statement> statements;
};

class Parser {
public:
  Parser(const std::string &data);

  ParsedFile parse();

private:
  std::string m_data;
};
}; // namespace Mesa