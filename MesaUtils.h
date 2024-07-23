#pragma once
#include "Mesa.h"
#include <string>
#include <vector>


#define LOG(format, ...)   \
    fprintf(stderr, "> "); \
    fprintf(stderr, format, ##__VA_ARGS__);

namespace Mesa {
    std::string Util_TrimString(std::string input);

    std::string Util_FixString(const std::string &input);

    std::vector<std::string> Util_SplitString(const std::string &input,
                                              const std::string &delimiter);

    std::string Util_EscapeString(const std::string &input);

    std::string Util_EvalString(std::shared_ptr<Workspace> workspace,
                                const std::string &string);
};// namespace Mesa