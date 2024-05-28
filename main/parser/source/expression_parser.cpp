/**
 * @file expression_parser.cpp
 * @brief Implementation of the FExpressionParser class.
 */

#include "expression_parser.hpp" // Include the expression parser header file
#include "tokenizer.hpp"         // Include the tokenizer header file
#include "parser.hpp"            // Include the parser header file
#include <stdexcept>             // For std::runtime_error

 // Expressions
#include "expression/operator/arithmetic/addition_expression.hpp"
#include "expression/operator/arithmetic/division_expression.hpp"
#include "expression/operator/arithmetic/modulo_expression.hpp"
#include "expression/operator/arithmetic/multiply_expression.hpp"
#include "expression/operator/arithmetic/subtract_expression.hpp"
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/string_operator_expression.hpp"

FExpressionParser::FExpressionParser(FTokenizer& tokenizer)
    : m_tokenizer(tokenizer)
{}

ExpressionPtr FExpressionParser::ParseExpression()
{
    // Parse the left term of the expression
    ExpressionPtr left = ParseTerm();

    // Check the type of the left term
    if (dynamic_cast<FNumberExpression*>(left.get()))
    {
        // If the left term is a number, parse arithmetic operator expression
        return ParseArithmeticOperatorExpression(std::move(left));
    }
    else if (dynamic_cast<FStringExpression*>(left.get()))
    {
        // If the left term is a string, parse string operator expression
        return ParseStringOperatorExpression(std::move(left));
    }
    else if (dynamic_cast<FIdentifierExpression*>(left.get()))
    {
        // If the left term is an identifier, parse identifier operator expression
        // Uncomment the line below when implementing identifier operator expressions
        // return ParseIdentifierOperatorExpression(std::move(left));
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FExpressionParser::ParseArithmeticOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_tokenizer.HasNextToken())
    {
        // Peek the next token
        const auto& token = m_tokenizer.PeekNextToken();

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
                left = std::make_unique<FAdditionExpression>(std::move(left), std::move(right));
            }
            else if (token.lexeme == "-")
            {
                left = std::make_unique<FSubtractExpression>(std::move(left), std::move(right));
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

ExpressionPtr FExpressionParser::ParseStringOperatorExpression(ExpressionPtr left)
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
            left = std::make_unique<FStringOperatorExpression>("+", std::move(left), std::move(right));
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

ExpressionPtr FExpressionParser::ParseIdentifier()
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
    return std::make_unique<FIdentifierExpression>(token.lexeme);
}

ExpressionPtr FExpressionParser::ParseNumber()
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
    return std::make_unique<FNumberExpression>(value);
}

ExpressionPtr FExpressionParser::ParseString()
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
    return std::make_unique<FStringExpression>(token.lexeme);
}

ExpressionPtr FExpressionParser::ParseTerm()
{
    // Parse the initial factor and store it as the left operand
    ExpressionPtr left = ParseFactor();

    // Continue parsing while there are more tokens available
    while (m_tokenizer.HasNextToken())
    {
        // If the left operand is not a number, stop parsing further
        if (!dynamic_cast<FNumberExpression*>(left.get()))
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
                left = std::make_unique<FMultiplyExpression>(std::move(left), std::move(right));
            }
            else if (token.lexeme == "/")
            {
                left = std::make_unique<FDivisionExpression>(std::move(left), std::move(right));
            }
            else if (token.lexeme == "%")
            {
                left = std::make_unique<FModuloExpression>(std::move(left), std::move(right));
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

ExpressionPtr FExpressionParser::ParseFactor()
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
