/**
 * @file parser.cpp
 * @brief Implementation of the FParser class.
 */

#include "parser.hpp"       // Include the parser header file
#include "tokenizer.hpp"    // Include the tokenizer header file

// Expression nodes
#include "ast/expression/arithmetic_operator_node.hpp"
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"
#include "ast/expression/string_operator_node.hpp"

// Statement nodes
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/print_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// For std::runtime_error
#include <stdexcept>

FParser::FParser(FTokenizer& tokenizer)
	: m_tokenizer(tokenizer)
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
        auto statement = ParseStatement();

        // If a valid statement is parsed, add it to the list of statements
        if (statement)
        {
            statements.push_back(std::move(statement));
        }
    }

    // Return the list of parsed statements
    return statements;
}

StatementPtr FParser::ParseStatement()
{
    // Peek at the next token without consuming it
    SToken token = m_tokenizer.PeekNextToken();

    // Check if the token is a keyword
    if (token.type == eTokenType::KEYWORD)
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
    else if (token.type == eTokenType::IDENTIFIER)
    {
        // Parse an assignment statement
        return ParseAssignmentStatement();
    }

    // If none of the above conditions are met, throw an error
    throw std::runtime_error("Unexpected token: " + token.lexeme);
}

StatementPtr FParser::ParseAssignmentStatement()
{
    // Get the next token, which should be an identifier
    SToken idToken = m_tokenizer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::IDENTIFIER)
    {
        // Throw an error if the token is not an identifier
        throw std::runtime_error("Expected identifier in assignment statement");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Get the next token, which should be '='
    SToken equalToken = m_tokenizer.GetNextToken();

    // Check if the token is '='
    if (equalToken.lexeme != "=")
    {
        // Throw an error if the token is not '='
        throw std::runtime_error("Expected '=' in assignment statement");
    }

    // Parse the expression on the right side of the assignment
    auto value = ParseExpression();

    // Return a unique pointer to the AssignmentNode with the identifier and expression
    return std::make_unique<FAssignmentNode>(identifier, std::move(value));
}

StatementPtr FParser::ParseVarDeclarationStatement()
{
    // Get the next token, which should be 'var'
    SToken varToken = m_tokenizer.GetNextToken();

    // Check if the token is 'var'
    if (varToken.type != eTokenType::KEYWORD)
    {
        // Throw an error if the token is not 'var'
        throw std::runtime_error("Expected 'var'");
    }

    // Get the next token, which should be an identifier
    SToken idToken = m_tokenizer.GetNextToken();

    // Check if the token is an identifier
    if (idToken.type != eTokenType::IDENTIFIER)
    {
        // Throw an error if the token is not an identifier
        throw std::runtime_error("Expected identifier after 'var'");
    }

    // Store the identifier
    std::string identifier = idToken.lexeme;

    // Get the next token, which should be '='
    SToken equalToken = m_tokenizer.GetNextToken();

    // Check if the token is '='
    if (equalToken.lexeme != "=")
    {
        // Throw an error if the token is not '='
        throw std::runtime_error("Expected '=' after identifier in var declaration");
    }

    // Parse the expression on the right side of the assignment
    auto value = ParseExpression();

    // Return a unique pointer to the VarDeclarationNode with the identifier and expression
    return std::make_unique<FVarDeclarationNode>(identifier, std::move(value));
}

StatementPtr FParser::ParsePrintStatement()
{
    // Get the next token, which should be 'print'
    SToken printToken = m_tokenizer.GetNextToken();

    // Check if the token is 'print'
    if (printToken.type != eTokenType::KEYWORD)
    {
        // Throw an error if the token is not 'print'
        throw std::runtime_error("Expected 'print'");
    }

    // Parse the expression to be printed
    auto expression = ParseExpression();

    // Return a unique pointer to the PrintNode with the expression
    return std::make_unique<FPrintNode>(std::move(expression));
}

ExpressionPtr FParser::ParseExpression()
{
    // Parse the left term of the expression
    ExpressionPtr left = ParseTerm();

    // Check the type of the left term
    if (dynamic_cast<FNumberNode*>(left.get()))
    {
        // If the left term is a number, parse arithmetic operator expression
        return ParseArithmeticOperatorExpression(std::move(left));
    }
    else if (dynamic_cast<FStringNode*>(left.get()))
    {
        // If the left term is a string, parse string operator expression
        return ParseStringOperatorExpression(std::move(left));
    }
    else if (dynamic_cast<FIdentifierNode*>(left.get()))
    {
        // If the left term is an identifier, parse identifier operator expression
        // Uncomment the line below when implementing identifier operator expressions
        // return ParseIdentifierOperatorExpression(std::move(left));
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FParser::ParseArithmeticOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_tokenizer.HasNextToken())
    {
        // Peek the next token
        const SToken& token = m_tokenizer.PeekNextToken();

        // Check if the token is an operator and if it's addition or subtraction
        if (token.type == eTokenType::OPERATOR && (token.lexeme == "+" || token.lexeme == "-"))
        {
            // Consume the operator token
            m_tokenizer.GetNextToken();

            // Parse the right term
            ExpressionPtr right = ParseTerm();

            // Create an arithmetic operator node based on the operator token
            if (token.lexeme == "+")
            {
                left = std::make_unique<FArithmeticOperatorNode>("+", std::move(left), std::move(right));
            }
            else if (token.lexeme == "-")
            {
                left = std::make_unique<FArithmeticOperatorNode>("-", std::move(left), std::move(right));
            }
        }
        else
        {
            // If the token is not an operator, break the loop
            break;
        }
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FParser::ParseStringOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_tokenizer.HasNextToken())
    {
        // Peek the next token
        const SToken& token = m_tokenizer.PeekNextToken();

        // Check if the token is an operator and if it's a concatenation operator
        if (token.type == eTokenType::OPERATOR && token.lexeme == "+")
        {
            // Consume the operator token
            m_tokenizer.GetNextToken();

            // Parse the right term
            ExpressionPtr right = ParseTerm();

            // Create a string operator node for concatenation
            left = std::make_unique<FStringOperatorNode>("+", std::move(left), std::move(right));
        }
        else
        {
            // If the token is not a concatenation operator, break the loop
            break;
        }
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FParser::ParseIdentifier()
{
    // Get the next token
    SToken token = m_tokenizer.GetNextToken();

    // Check if the token is an identifier
    if (token.type != eTokenType::IDENTIFIER)
    {
        // Throw an error if it's not an identifier
        throw std::runtime_error("Expected 'identifier'");
    }

    // Create an identifier node with the token's lexeme as the identifier name
    return std::make_unique<FIdentifierNode>(token.lexeme);
}

ExpressionPtr FParser::ParseNumber()
{
    // Get the next token
    SToken token = m_tokenizer.GetNextToken();

    // Check if the token is a number
    if (token.type != eTokenType::NUMBER)
    {
        // Throw an error if it's not a number
        throw std::runtime_error("Expected 'number'");
    }

    // Convert the token's lexeme to an integer and create a number node with that value
    int value = std::stoi(token.lexeme);
    return std::make_unique<FNumberNode>(value);
}

ExpressionPtr FParser::ParseString()
{
    // Get the next token
    SToken token = m_tokenizer.GetNextToken();

    // Check if the token is a string
    if (token.type != eTokenType::STRING)
    {
        // Throw an error if it's not a string
        throw std::runtime_error("Expected 'string'");
    }

    // Create a string node with the token's lexeme as its value
    return std::make_unique<FStringNode>(token.lexeme);
}

ExpressionPtr FParser::ParseTerm()
{
    // Parse the initial factor and store it as the left operand
    ExpressionPtr left = ParseFactor();

    // Continue parsing while there are more tokens available
    while (m_tokenizer.HasNextToken())
    {
        // If the left operand is not a number, stop parsing further
        if (!dynamic_cast<FNumberNode*>(left.get()))
        {
            break;
        }

        // Peek at the next token to determine the operator
        const SToken& token = m_tokenizer.PeekNextToken();

        // Check if the token is an operator and if it is one of '*', '/', or '%'
        if (token.type == eTokenType::OPERATOR && (token.lexeme == "*" || token.lexeme == "/" || token.lexeme == "%"))
        {
            // Consume the operator token
            m_tokenizer.GetNextToken();

            // Parse the next factor and store it as the right operand
            ExpressionPtr right = ParseFactor();

            // Create an arithmetic operator node based on the operator and update the left operand
            if (token.lexeme == "*")
            {
                left = std::make_unique<FArithmeticOperatorNode>("*", std::move(left), std::move(right));
            }
            else if (token.lexeme == "/")
            {
                left = std::make_unique<FArithmeticOperatorNode>("/", std::move(left), std::move(right));
            }
            else if (token.lexeme == "%")
            {
                left = std::make_unique<FArithmeticOperatorNode>("%", std::move(left), std::move(right));
            }
        }
        else
        {
            // If the token is not an operator or not one of '*', '/', or '%', stop parsing
            break;
        }
    }

    // Return the parsed term
    return left;
}

ExpressionPtr FParser::ParseFactor()
{
    // Peek at the next token to determine its type
    const SToken& token = m_tokenizer.PeekNextToken();

    // Check if the token is a number and parse it if true
    if (token.type == eTokenType::NUMBER)
    {
        return ParseNumber();
    }
    // Check if the token is a string and parse it if true
    else if (token.type == eTokenType::STRING)
    {
        return ParseString();
    }
    // Check if the token is an identifier and parse it if true
    else if (token.type == eTokenType::IDENTIFIER)
    {
        return ParseIdentifier();
    }

    // If the token is none of the expected types, throw an error
    throw std::runtime_error("Unexpected token in factor: " + token.lexeme);
}
