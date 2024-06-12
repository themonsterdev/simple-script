#pragma once

#include "lexer/rule/string_rule.hpp"
#include "lexer/exception/lexical_exception.hpp"

bool FStringRule::Match(const std::string& text, size_t& index, FToken& token) const
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
        if (quoteChar == '`')
        {
            token.SetType(eTokenType::StringFormatLiteral);
        }
        else
        {
            token.SetType(eTokenType::String);
        }
        token.SetLexeme(text.substr(startPos + 1, index - startPos - 2));
        return true;
    }
    return false;
}
