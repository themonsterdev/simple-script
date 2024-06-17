/**
 * @file delimiter_rule.cpp
 * @brief Implementation of the FDelimiterRule class.
 */

// Include the header file for the delimiter rule
#include "lexer/rule/delimiter_rule.hpp"

bool FDelimiterRule::Match(const std::string& text, size_t& index, FToken& token) const
{
    // Define a string containing the delimiters
    const std::string delimiters = "[](),:";

    // Check if the current character is one of the delimiters
    if (delimiters.find(text[index]) != std::string::npos)
    {
        // Set token type to Delimiter
        token.SetType(eTokenType::Delimiter);

        // Set token lexeme to the current character
        token.SetLexeme(text.substr(index, 1));

        // Move to the next character
        index++;

        // Return true to indicate a successful match
        return true;
    }

    // Return false if the current character is not a delimiter
    return false;
}
