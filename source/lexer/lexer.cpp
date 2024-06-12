/**
 * @file lexer.cpp
 * @brief Implementation of the FLexer class.
 */

// Include necessary headers
#include "lexer/lexer.hpp"                       // For FLexer
#include "lexer/lexer_factory.hpp"               // For FLexerFactory
#include "lexer/exception/lexical_exception.hpp" // For FLexicalException

FLexer::FLexer(const std::string& source)
	: m_rules(FLexerFactory::CreateRules()) // Initialize lexical rules using the factory
	, m_source(source)                      // Initialize source code
	, m_index(0)                            // Initialize index to start of source code
	, m_line(1)                             // Initialize line number
	, m_column(1)                           // Initialize column number
	, m_begin(0)                            // Initialize begin index
{}

bool FLexer::HasNextToken() const
{
    // Return true if the current index is less than the length of the source code
    return m_index < m_source.length();
}

FToken FLexer::PeekNextToken(size_t n)
{
    // Store the current index position
    size_t currentOffset = m_index;

    // Get the next token using GetNextToken with the provided offset
    const auto& nextToken = GetNextToken(n);

    // Restore the index position
    m_index = currentOffset;

    // Return the next token without advancing the lexer's position
    return nextToken;
}

FToken FLexer::GetNextToken(size_t n)
{
    // Advance the index by n characters
    size_t i = 0;
    while (i < n && HasNextToken())
    {
        // Skip whitespace characters
        SkipWhitespace();

        m_index++;
        i++;
    }

    // Skip whitespace characters
    SkipWhitespace();

    // Return End token if no more tokens are found
    if (!HasNextToken())
    {
        return { eTokenType::End, "", m_line, m_column };
    }

    // Initialize token with current line and column numbers
    FToken token;
    token.SetLine(m_line);
    token.SetColumn(m_column);

    // Try to match tokens with lexical rules
    for (const auto& rule : m_rules)
    {
        size_t tempIndex = m_index;
        if (rule->Match(m_source, tempIndex, token))
        {
            // Update lexer's position and return the matched token
            UpdatePosition(m_index, tempIndex);
            m_index = tempIndex;

            if (token.IsSameType(eTokenType::Comment))
            {
                return GetNextToken(n);
            }
            return token;
        }
    }

    // If no match is found, throw an exception
    std::string lexeme(1, m_source[m_index]);
    throw FLexicalException("Unknown token: " + lexeme);
}

void FLexer::BeginNextToken()
{
    m_begin = m_index;
}

void FLexer::EndNextToken()
{
    m_index = m_begin;
}

bool FLexer::TryConsumeToken(eTokenType expectedType, const std::string& expectedLexeme)
{
    // Check if there is a next token available
    if (!HasNextToken())
    {
        return false;
    }

    // Get the next token
    const auto& token = PeekNextToken();

    // Checks if the type and lexeme of the token match those expected
    if (token.IsSameTypeAndLexeme(expectedType, expectedLexeme))
    {
        // Consume the token if the match is successful
        GetNextToken();
        return true;
    }

    // Return false if the token does not match
    return false;
}

bool FLexer::MatchToken(eTokenType expectedType, const std::string& expectedLexeme)
{
    // Check if there is a next token available
    if (!HasNextToken())
    {
        return false;
    }

    // Get the next token
    const auto& token = PeekNextToken();

    // Checks if the type and lexeme of the token match those expected
    return token.IsSameTypeAndLexeme(expectedType, expectedLexeme);
}

void FLexer::SkipWhitespace()
{
    // Continue skipping whitespace characters while there are more tokens and the current character is whitespace
    while (HasNextToken() && std::isspace(m_source[m_index]))
    {
        // Update lexer's position
        UpdatePosition(m_index, m_index + 1);

        // Move to the next character
        m_index++;
    }
}

void FLexer::UpdatePosition(size_t start, size_t end)
{
    // Iterate over the characters in the given range
    for (size_t i = start; i < end; ++i)
    {
        // If the current character is a newline character, increment
        // the line number and reset the column number
        if (m_source[i] == '\n')
        {
            // Increment the line number
            m_line++;

            // Reset the column number to 1
            m_column = 1;
        }
        else
        {
            // Increment the column number for non-newline characters
            m_column++;
        }
    }
}