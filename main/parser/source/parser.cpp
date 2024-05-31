/**
 * @file parser.cpp
 * @brief Implementation of the FParser class.
 */

#include "parser.hpp" // Include the parser header file
#include "lexer.hpp"  // Include the lexer header file

FParser::FParser(FLexer& lexer)
	: m_lexer(lexer)
	, m_expressionParser(lexer)
	, m_statementParser(lexer, m_expressionParser)
{}

StatementList FParser::Parse()
{
    // Create a list to store parsed statements
    StatementList statements;

    // Continue parsing until there are no more tokens
    while (m_lexer.HasNextToken())
    {
        // Peek at the next token without consuming it
        const auto& token = m_lexer.PeekNextToken();

        // Check if the token type is not Whitespace or Comment
        if (token.type == eTokenType::Whitespace || token.type == eTokenType::Comment)
        {
            m_lexer.GetNextToken();
            continue;
        }

        // Parse the next statement
        auto statement = ParseNextStatement();

        // If a valid statement is parsed, add it to the list of statements
        if (statement)
        {
            statements.push_back(std::move(statement));
        }
        else // If ParseNextStatement returns null, it's the end of the file
        {
            break;
        }
    }

    // Return the list of parsed statements
    return statements;
}

StatementPtr FParser::ParseNextStatement()
{
    // Peek at the next token without consuming it
    const auto& token = m_lexer.PeekNextToken();

    // Return null if the next token indicates the end of the input
    if (token.type != eTokenType::End)
    {
        return m_statementParser.ParseStatement();
    }

    // Parse and return the next statement
    return nullptr;
}
