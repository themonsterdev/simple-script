/**
 * @file boolean_rule.cpp
 * @brief Implementation of the FBooleanRule class.
 */

// Include the header file for the boolean rule
#include "rule/boolean_rule.hpp"

bool FBooleanRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Store the starting position of the match attempt
    size_t startPos = index;

    // Check if the current character is 't' or 'f' (the first letter of true or false)
    if (text[index] == 't' || text[index] == 'f')
    {
        // Check if the word "true" is found
        if (text.substr(index, 4) == "true")
        {
            // Update the index to point to the end of the word "true"
            index += 4;

            // Set token type and lexeme for "true"
            token.type = eTokenType::Boolean;
            token.lexeme = "true";

            // Return true to indicate a successful match
            return true;
        }
        // Check if the word "false" is found
        else if (text.substr(index, 5) == "false")
        {
            // Update the index to point to the end of the word "false"
            index += 5;

            // Set token type and lexeme for "false"
            token.type   = eTokenType::Boolean;
            token.lexeme = "false";

            // Return true to indicate a successful match
            return true;
        }
    }

    // Return false if no boolean is found
    return false;
}
