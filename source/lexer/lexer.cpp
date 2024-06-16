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
	, m_lastIndex(0)                        // Initialize begin index
    , m_lastLine(1)
    , m_lastColumn(1)
{}

bool FLexer::HasNextToken() const
{
    // Return true if the current index is less than the length of the source code
    return m_index < m_source.length();
}

FToken FLexer::PeekNextToken()
{
    // Store the current index position
    size_t lastIndex     = m_index;
    uint32_t lastLine    = m_line;
    uint32_t lastColumn  = m_column;

    // Get the next token using GetNextToken with the provided offset
    const auto& nextToken = GetNextToken();

    // Restore the index position
    m_index  = lastIndex;
    m_line   = lastLine;
    m_column = lastColumn;

    // Return the next token without advancing the lexer's position
    return nextToken;
}

FToken FLexer::GetNextToken()
{
    // Skip whitespace characters
    SkipWhitespace();

    // Initialize token with current line and column numbers
    FToken token = { eTokenType::End, "", m_line, m_column };

    // Return End token if no more tokens are found
    if (!HasNextToken())
    {
        return token;
    }

    // Try to match tokens with lexical rules
    for (const auto& rule : m_rules)
    {
        size_t tempIndex = m_index;

        if (rule->Match(m_source, tempIndex, token))
        {
            // Update lexer's position and return the matched token
            UpdatePosition(m_index, tempIndex);

            if (token.IsSameType(eTokenType::Comment))
            {
                return GetNextToken();
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
    m_lastIndex   = m_index;
    m_lastLine    = m_line;
    m_lastColumn  = m_column;
}

void FLexer::EndNextToken()
{
    m_index   = m_lastIndex;
    m_line    = m_lastLine;
    m_column  = m_lastColumn;
}

bool FLexer::TryConsumeToken(eTokenType expectedType, const std::string& expectedLexeme)
{
    // Checks if the type and lexeme of the token match those expected
    if (MatchToken(expectedType, expectedLexeme))
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
    }
}

void FLexer::UpdatePosition(size_t start, size_t end)
{
    // Iterate over the characters in the given range
    for (size_t i = start; i < end; i++)
    {
        if (m_source[i] == '\t')
        {
            // Assuming a tab width of 4 spaces
            m_column += 4;
        }
        else if (m_source[i] == '\n')
        {
            // Increment the line number and reset the column number
            m_line++;
            m_column = 1;
        }
        else
        {
            // Increment the column number for non-newline and non-tab characters
            m_column++;
        }
    }

    // Update the lexer's index to the end position
    m_index = end;
}
