/**
 * @file parser.cpp
 * @brief Implementation of the FParser class.
 */

#include "parser.hpp"   // Include the parser header file
#include "lexer.hpp"    // Include the lexer header file

// For std::runtime_error
#include <stdexcept>

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

        // Check if the token indicates the end of the input
        if (token.type == eTokenType::End)
        {
            break;
        }

        // Parse the next statement
        auto statement = m_statementParser.ParseStatement();

        // If a valid statement is parsed, add it to the list of statements
        if (statement)
        {
            statements.push_back(std::move(statement));
        }
    }

    // Return the list of parsed statements
    return statements;
}
