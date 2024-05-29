/**
 * @file comment_rule.cpp
 * @brief Implementation of the FCommentRule class.
 */

// Include the header file for the comment rule
#include "rule/comment_rule.hpp"

bool FCommentRule::Match(const std::string& text, size_t& index, SToken& token) const
{
    // Store the starting position of the match attempt
    size_t startPos = index;

    // Check for single-line comment
    if (text.substr(index, 2) == "//")
    {
        // Move past the "//" characters
        index += 2;

        // Find the end of the line or the end of the text
        while (index < text.size() && text[index] != '\n')
        {
            // Move to the next character
            index++;
        }

        // Set token type and lexeme
        token.type   = eTokenType::Comment;
        token.lexeme = text.substr(startPos, index - startPos);

        // Return true to indicate a successful match
        return true;
    }
    // Check for multi-line comment
    else if (text.substr(index, 2) == "/*")
    {
        // Move past the "/*" characters
        index += 2;

        // Find the end of the comment or the end of the text
        while (index + 2 <= text.size())
        {
            if (text.substr(index, 2) == "*/")
            {
                // Move past the "*/" characters
                index += 2;

                // Exit the loop since the end of the comment is found
                break;
            }

            // Move to the next character
            index++;
        }

        // Set token type and lexeme
        token.type   = eTokenType::Comment;
        token.lexeme = text.substr(startPos, index - startPos);

        // Return true to indicate a successful match
        return true;
    }

    // Return false if no comment is found
    return false;
}
