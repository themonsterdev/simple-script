/**
 * @file parser.cpp
 * @brief Implementation of the FParser class.
 */

#include "parser.hpp"    // Include the parser header file
#include "tokenizer.hpp" // Include the tokenizer header file

// For std::runtime_error
#include <stdexcept>

FParser::FParser(FTokenizer& tokenizer)
	: m_tokenizer(tokenizer)
	, m_expressionParser(tokenizer)
	, m_statementParser(tokenizer, m_expressionParser)
{}

StatementList FParser::Parse()
{
    // Create a list to store parsed statements
    StatementList statements;

    // Continue parsing until there are no more tokens
    while (m_tokenizer.HasNextToken())
    {
        // Peek at the next token without consuming it
        const auto& token = m_tokenizer.PeekNextToken();

        // Check if the token indicates the end of the input
        if (token.type == eTokenType::END)
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
