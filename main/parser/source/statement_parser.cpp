/**
 * @file statement_parser.cpp
 * @brief Implementation of the FStatementParser class.
 */

#include "statement_parser.hpp"	            // Include the statement parser header file
#include "lexer.hpp"		                // Include the lexer header file
#include "exception/syntax_exception.hpp"   // Include the syntax exception header file

 // Statements
#include "statement/assignment_statement.hpp"
#include "statement/print_statement.hpp"
#include "statement/var_declaration_list_statement.hpp"
#include "statement/var_declaration_statement.hpp"

FStatementParser::FStatementParser(FLexer& lexer, FExpressionParser& expressionParser)
    : m_lexer(lexer)
    , m_expressionParser(expressionParser)
{}

StatementPtr FStatementParser::ParseStatement()
{
    // Peek at the next token without consuming it
    const auto& token = m_lexer.PeekNextToken();

    // Check if the token is a keyword
    if (token.type == eTokenType::Keyword)
    {
        // Check the type of keyword
        if (token.lexeme == "var")
        {
            // Parse a variable declaration statement
            return ParseVarDeclarationStatement();
        }
        else if (token.lexeme == "print")
        {
            // Parse a print statement
            return ParsePrintStatement();
        }
    }
    // Check if the token is an identifier
    else if (token.type == eTokenType::Identifier)
    {
        // Parse an assignment statement
        return ParseAssignmentStatement();
    }

    // If none of the above conditions are met, throw an error
    throw FSyntaxException("Unexpected token: " + token.lexeme);
}

StatementPtr FStatementParser::ParseVarDeclarationStatement()
{
    // Get the next token, which should be 'var'
    SToken varToken = m_lexer.GetNextToken();

    // Check if the token is 'var'
    if (varToken.type != eTokenType::Keyword || varToken.lexeme != "var")
    {
        // Throw an error if the token is not 'var'
        throw FSyntaxException("Expected 'var'");
    }

    StatementVector declarations;

    // Get the first token, which should be an identifier
    SToken idToken = m_lexer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::Identifier)
    {
        // Throw an error if the token is not an identifier
        throw FSyntaxException("Expected identifier after 'var'");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Initial declaration with the first identifier
    ExpressionPtr expression = nullptr;

    // Check if the next token is '='
    if (m_lexer.HasNextToken())
    {
        SToken nextToken = m_lexer.PeekNextToken();

        if (nextToken.lexeme == "=")
        {
            m_lexer.GetNextToken(); // consume token '='

            // Parse the expression on the right side of the assignment
            expression = m_expressionParser.ParseExpression();
        }
    }

    // Add the first declaration
    declarations.push_back(std::make_unique<FVarDeclarationStatement>(identifier, std::move(expression)));

    // Parse any additional declarations
    while (m_lexer.HasNextToken())
    {
        // Peek the next token to see if it is a comma
        SToken nextToken = m_lexer.PeekNextToken();

        if (nextToken.lexeme == ",")
        {
            m_lexer.GetNextToken(); // consume token ','

            // Get the next token, which should be an identifier
            SToken idToken = m_lexer.GetNextToken();

            // Check if the token is an identifier
            if (idToken.type != eTokenType::Identifier)
            {
                // Throw an error if the token is not an identifier
                throw FSyntaxException("Expected identifier after ',', received " + idToken.lexeme);
            }

            // Store the identifier
            std::string identifier = idToken.lexeme;

            // Reset expression for the new declaration
            expression = nullptr;

            // Check if the next token is '='
            if (m_lexer.HasNextToken())
            {
                nextToken = m_lexer.PeekNextToken();

                if (nextToken.lexeme == "=")
                {
                    m_lexer.GetNextToken(); // consume token '='

                    // Parse the expression on the right side of the assignment
                    expression = m_expressionParser.ParseExpression();
                }
            }

            // Add the declaration
            declarations.push_back(std::make_unique<FVarDeclarationStatement>(identifier, std::move(expression)));
        }
        else
        {
            // If no comma is found, end parsing
            break;
        }
    }

    // Return a unique pointer to the FVarDeclarationListStatement with the list of declarations
    return std::make_unique<FVarDeclarationListStatement>(std::move(declarations));
}

StatementPtr FStatementParser::ParsePrintStatement()
{
    // Get the next token, which should be 'print'
    SToken printToken = m_lexer.GetNextToken();

    // Check if the token is 'print'
    if (printToken.type != eTokenType::Keyword)
    {
        // Throw an error if the token is not 'print'
        throw FSyntaxException("Expected 'print'");
    }

    // Parse the expression to be printed
    auto expression = m_expressionParser.ParseExpression();

    // Return a unique pointer to the FPrintStatement with the expression
    return std::make_unique<FPrintStatement>(std::move(expression));
}

StatementPtr FStatementParser::ParseAssignmentStatement()
{
    // Get the next token, which should be an identifier
    SToken idToken = m_lexer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::Identifier)
    {
        // Throw an error if the token is not an identifier
        throw FSyntaxException("Expected identifier in assignment statement");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Get the next token, which should be '='
    SToken equalToken = m_lexer.GetNextToken();

    // Check if the token is '='
    if (equalToken.lexeme != "=")
    {
        // Throw an error if the token is not '='
        throw FSyntaxException("Expected '=' in assignment statement");
    }

    // Parse the expression on the right side of the assignment
    auto value = m_expressionParser.ParseExpression();

    // Return a unique pointer to the FAssignmentStatement with the identifier and expression
    return std::make_unique<FAssignmentStatement>(identifier, std::move(value));
}
