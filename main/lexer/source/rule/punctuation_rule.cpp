/**
 * @file punctuation_rule.cpp
 * @brief Implementation of the FPunctuationRule class.
 */

// Include the header file for the punctuation rule
#include "rule/punctuation_rule.hpp"

/**
 * @brief Function to check if a character is punctuation.
 * @param c The character to check.
 * @return True if the character is punctuation (comma, semicolon, or period), false otherwise.
 */
static bool IsPunctuation(const char c)
{
    switch (c) {
    case ',':   // Check for comma
    case ';':   // Check for semicolon
    case '.':   // Check for period
        return true;
    default:
        return false;
    }
}

bool FPunctuationRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Get the current character from the text
    char currentChar = text[index];

    // Check if the current character is punctuation
    if (IsPunctuation(currentChar))
    {
        // Set token type to Punctuation
        token.type = eTokenType::Punctuation;

        // Set token lexeme to the current character
        token.lexeme = currentChar;

        // Move to the next character
        index++;

        // Return true to indicate a successful match
        return true;
    }

    // Return false if the current character is not punctuation
    return false;
}
