/**
 * @file number_rule.cpp
 * @brief Implementation of the FNumberRule class.
 */

// Include the header file for the number rule
#include "rule/number_rule.hpp"

bool FNumberRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Store the starting position of the match attempt
    size_t startPos = index;

    // Check if the current character is a digit
    if (std::isdigit(text[index]))
    {
        // Continue moving forward while the current character is a digit
        while (index < text.size() && std::isdigit(text[index]))
        {
            // Move to the next character
            index++;
        }

        // Set token type and lexeme
        token.type   = eTokenType::Number;
        token.lexeme = text.substr(startPos, index - startPos);

        // Return true to indicate a successful match
        return true;
    }

    // Return false if no number is found
    return false;
}
