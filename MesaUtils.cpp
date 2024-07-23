#include "MesaUtils.h"
#include "Mesa.h"
#include <algorithm>
#include <cstdarg>
#include <memory>
#include <vector>


std::string Mesa::Util_TrimString(std::string input) {
    input.erase(input.begin(),
                std::find_if(input.begin(), input.end(),
                             [](unsigned char ch) { return !std::isspace(ch); }));

    return input;
}

std::string Mesa::Util_FixString(const std::string &input) {
    std::string res;

    for (char cChar: input) {
        if (cChar == ' ' || cChar == '/' || cChar == '\\') {
            res += '_';
        } else {
            res += cChar;
        }
    }

    return res;
}

std::vector<std::string> Mesa::Util_SplitString(const std::string &input,
                                                const std::string &delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = input.find(delimiter, pos_start)) != std::string::npos) {
        token = input.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(input.substr(pos_start));
    return res;
}

std::string Mesa::Util_EscapeString(const std::string &input) {
    std::string res;

    for (char cChar: input) {

        if (cChar == '\\') {
            res += "\\";
        } else if (cChar == ' ') {
            res += "\\";
        }

        res += cChar;
    }

    return res;
}

std::string Mesa::Util_EvalString(std::shared_ptr<Mesa::Workspace> workspace,
                                  const std::string &string) {
    std::string data;

    std::string varName;
    bool writeVarName = false;

    for (char cChar: string) {
        if (cChar == '$') {
            varName.clear();
            writeVarName = true;

            continue;
        } else if (cChar == ' ' && writeVarName) {
            if (workspace->variables.find(varName) == workspace->variables.end()) {
                LOG("Failed to eval statement: No such variable with name: %s\n",
                    varName.c_str());

                std::exit(EXIT_FAILURE);
            }

            data += workspace->variables.at(varName);

            writeVarName = false;

            continue;
        }

        if (writeVarName) {
            varName += cChar;
        } else {
            data += cChar;
        }
    }

    // If we encounter no space by the end of the eval just append the variable
    // content
    if (writeVarName) {
        if (workspace->variables.find(varName) == workspace->variables.end()) {
            LOG("Failed to eval statement: No such variable with name: %s\n",
                varName.c_str());

            std::exit(EXIT_FAILURE);
        }

        data += workspace->variables.at(varName);
    }

    return Util_TrimString(data);
}
