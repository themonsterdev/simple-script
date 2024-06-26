/**
 * @file lexer.hpp
 * @brief Declaration of the FLexer class.
 */

// Ensure this file is included only once
#pragma once

// Include necessary headers
#include "rule/interface/lexical_rule.hpp"  // For ILexicalRule
#include "token.hpp"                        // For FToken

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

    size_t m_lastIndex;
    uint32_t m_lastLine;
    uint32_t m_lastColumn;

public:

    /**
     * @brief Constructs a new FLexer object with the given source code.
     * @param source The source code to tokenize.
     */
    FLexer(const std::string& source);

    /**
     * @brief Checks if there are more tokens to process.
     * @return True if there are more tokens, false otherwise.
     */
    bool HasNextToken() const;

    /**
     * @brief Peeks at the next token without consuming it.
     * @return The next token.
     */
    FToken PeekNextToken();

    /**
     * @brief Gets the next token and advances the lexer's position.
     * @return The next token.
     */
    FToken GetNextToken();

    void BeginNextToken();
    void EndNextToken();

    bool TryConsumeToken(eTokenType expectedType, const std::string& expectedLexeme);
    bool MatchToken(eTokenType expectedType, const std::string& expectedLexeme);

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
