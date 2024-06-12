/**
 * @file identifier_rule.cpp
 * @brief Implementation of the FIdentifierRule class.
 */

// Include the header file for the identifier rule
#include "lexer/rule/identifier_rule.hpp"

// Define the list of keywords
static constexpr auto KEYWORDS =
{
    // Conditional
    "if",
    "else",

    // Declaration
    "var",
    "const",
    "enum",

    // Loop
    "do",
    "for",
    "while",

    // Scope
    "then",
    "end",

    // Functions
    "function",

    // Control Structures
    "switch",
    "case",
    "break",    // unused
    "default",
    "continue",
    "return",

    // Data Types
    "int",      // unused
    "float",    // unused
    "bool",     // unused
    "string",   // unused

    // Data Structures
    "array",    // unused
    "list",     // unused
    "map",      // unused
    "set",      // unused

    // Input/Output
    "input",
    "output",   // unused
    "println",  // unused
    "print",

    // Error Handling
    "try",
    "catch",
    "finally",
    "throw",
    "assert",

    // File Operations
    "open",
    "close",
    "read",
    "write",

    // Memory Management
    "new",      // unused
    "delete",   // unused

    // Object-Oriented Programming
    "class",
    "abstract",
    "interface",
    "final",
    "extends",
    "implements",
    "trait",
    "constructor",  // unused
    "destructor",   // unused
    "private",
    "protected",
    "public",
    "use",

    // String Manipulation
    "substring",    // unused
    "concatenate"   // unused
};

bool FIdentifierRule::Match(const std::string& text, size_t& index, FToken& token) const
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
        token.SetType(eTokenType::Identifier);
        token.SetLexeme(text.substr(start, index - start));

        if (token.IsSameLexeme("else") && text[index] == ' ')
        {
            // Move to the next character
            index++;

            FToken elseToken;
            if (Match(text, index, elseToken) && elseToken.IsSameLexeme("if"))
            {
                token.SetType(eTokenType::Keyword);
                token.SetLexeme("else if");
            }
        }

        // Check if the identifier is a keyword
        for (const auto& keyword : KEYWORDS)
        {
            if (token.IsSameLexeme(keyword))
            {
                // Set token type to Keyword if it matches a keyword
                token.SetType(eTokenType::Keyword);

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
