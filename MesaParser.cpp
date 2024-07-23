#include "MesaParser.h"
#include "MesaUtils.h"

using namespace Mesa;

#define State_IsComment (1 << 1)
#define State_IsStatement (1 << 2)
#define State_PushIntoValue (1 << 3)

Parser::Parser(const std::string &data) { m_data = data; }

ParsedFile Parser::parse() {
    std::vector<Statement> statements;

    Statement cStatement{};

    int state = 0;

    for (char cChar: m_data) {
        if (cChar == '#' && !(state & State_IsComment)) {
            state |= State_IsComment;

            continue;
        }

        if (cChar == '%' && !(state & State_IsStatement)) {
            state |= State_IsStatement;

            continue;
        }

        if (state & State_IsStatement) {
            if (cChar == ' ' && (state & State_IsStatement) &&
                !(state & State_PushIntoValue)) {
                state |= State_PushIntoValue;
            }

            if (state & State_PushIntoValue) {
                cStatement.value += cChar;
            } else {
                cStatement.key += cChar;
            }
        }

        if (cChar == '\n' && state & State_IsStatement) {
            state = state & ~State_IsStatement;
            state = state & ~State_PushIntoValue;

            cStatement.key = Util_TrimString(cStatement.key);
            cStatement.value = Util_TrimString(cStatement.value);

            if (!cStatement.key.empty() && cStatement.key.back() == '\n')
                cStatement.key.pop_back();
            if (!cStatement.value.empty() && cStatement.value.back() == '\n')
                cStatement.value.pop_back();

            statements.push_back(cStatement);

            cStatement.key.clear();
            cStatement.value.clear();
        }

        if (cChar == '\n' && state & State_IsComment) {
            state = state & ~State_IsComment;

            continue;
        }
    }

    ParsedFile file{};
    file.statements = statements;

    return file;
}
