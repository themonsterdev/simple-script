#pragma once

#include "rule/string_rule.hpp"
#include "exception/lexical_exception.hpp"

bool FStringRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    size_t startPos = index;
    char quoteChar = text[index++];
    if (quoteChar == '"' || quoteChar == '\'' || quoteChar == '`')
    {
        while (index < text.size() && text[index] != quoteChar)
        {
            if (text[index] == '\\' && index + 1 < text.size())
            {
                index += 2;
            }
            else
            {
                index++;
            }
        }
        if (index >= text.size() || text[index] != quoteChar)
        {
            throw FLexicalException("Unterminated string literal");
        }
        index++;
        token.type   = eTokenType::String;
        token.lexeme = text.substr(startPos + 1, index - startPos - 2);
        return true;
    }
    return false;
}
