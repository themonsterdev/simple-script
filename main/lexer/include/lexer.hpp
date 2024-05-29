/**
 * @file lexer.hpp
 * @brief Declaration of the FLexer class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary headers
#include "rule/interface/lexical_rule.hpp"  // For ILexicalRule
#include "token.hpp"                        // For SToken

/**
 * @brief Lexer class for lexical analysis.
 * This class tokenizes the input source code based on given lexical rules.
 */
class FLexer final
{
    LexicalRuleVector m_rules;      // Vector of lexical rules
    const std::string& m_source;    // Reference to the input source code
    size_t m_index;                 // Current index in the source code
    uint32_t m_line;                // Current line number
    uint32_t m_column;              // Current column number

public:

    /**
     * @brief Constructs a new FLexer object with the given source code.
     * @param source The source code to tokenize.
     */
    FLexer(const std::string& source);

    /**
     * @brief Tokenizes the source code.
     * @return A vector of tokens extracted from the source code.
     */
    TokenVector Tokenize();

    /**
     * @brief Checks if there are more tokens to process.
     * @return True if there are more tokens, false otherwise.
     */
    bool HasNextToken() const;

    /**
     * @brief Peeks at the next token without consuming it.
     * @param n The number of tokens to skip (default is 0)
     * @return The next token.
     */
    SToken PeekNextToken(size_t n = 0);

    /**
     * @brief Gets the next token and advances the lexer's position.
     * @param n The number of tokens to skip (default is 0).
     * @return The next token.
     */
    SToken GetNextToken(size_t n = 0);

private:

    /**
     * @brief Skips whitespace characters.
     */
    void SkipWhitespace();

    /**
     * @brief Updates the position (line and column numbers) based on the given range.
     * @param start The starting index of the range.
     * @param end The ending index of the range.
     */
    void UpdatePosition(size_t start, size_t end);
};
