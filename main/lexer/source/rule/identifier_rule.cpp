/**
 * @file identifier_rule.cpp
 * @brief Implementation of the FIdentifierRule class.
 */

// Include the header file for the identifier rule
#include "rule/identifier_rule.hpp"

// Define the list of keywords
static constexpr auto KEYWORDS =
{
    "var",
    "print",
};

bool FIdentifierRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Store the starting position of the match attempt
    size_t start = index;

    // Check if the current character is a letter or an underscore
    if (isalpha(text[index]) || text[index] == '_')
    {
        // Move to the next character
        index++;

        // Continue moving forward while the current character is alphanumeric or an underscore
        while (isalnum(text[index]) || text[index] == '_')
        {
            // Move to the next character
            index++;
        }

        // Set token type and lexeme
        token.type   = eTokenType::Identifier;
        token.lexeme = text.substr(start, index - start);

        // Check if the identifier is a keyword
        for (const auto& keyword : KEYWORDS)
        {
            if (token.lexeme == keyword)
            {
                // Set token type to Keyword if it matches a keyword
                token.type = eTokenType::Keyword;

                // Exit the loop since the keyword is found
                break;
            }
        }

        // Return true to indicate a successful match
        return true;
    }

    // Return false if no identifier is found
    return false;
}
