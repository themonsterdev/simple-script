/**
 * @file expression_parser.cpp
 * @brief Implementation of the FExpressionParser class.
 */

#include "expression/expression_parser.hpp" // Include the expression parser header file
#include "exception/syntax_exception.hpp"   // Include the syntax exception header file
#include "lexer.hpp"                        // Include the tokenizer header file

// Expressions
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/operator/additive/subtract_expression.hpp"

#include "expression/operator/multiplicative/division_expression.hpp"
#include "expression/operator/multiplicative/modulo_expression.hpp"
#include "expression/operator/multiplicative/multiply_expression.hpp"

#include "expression/operator/equality/equal_to_expression.hpp"
#include "expression/operator/equality/not_equal_expression.hpp"

#include "expression/operator/comparison/greater_than_expression.hpp"
#include "expression/operator/comparison/greater_than_or_equal_to_expression.hpp"
#include "expression/operator/comparison/less_than_expression.hpp"
#include "expression/operator/comparison/less_than_or_equal_to_expression.hpp"

#include "expression/operator/ternary/ternary_expression.hpp"

#include "expression/literal/boolean_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"

#include "expression/string_operator_expression.hpp"
#include "expression/identifier_expression.hpp"

FExpressionParser::FExpressionParser(FLexer& lexer)
    : m_lexer(lexer)
{}

ExpressionPtr FExpressionParser::ParseExpression()
{
    // Peek at the next token to determine its type
    const auto& token = m_lexer.PeekNextToken();

    // Parse the left term of the expression
    ExpressionPtr left = ParseTerm();

    // Check if there is a ternary expression to parse
    left = ParseTernaryExpression(std::move(left));

    if (token.type == eTokenType::Boolean)
    {
        
    }
    else if (token.type == eTokenType::Float)
    {

    }
    else if (token.type == eTokenType::Identifier)
    {
        // If the left term is an identifier, parse identifier operator expression
        left = ParseIdentifierOperatorExpression(std::move(left));
    }
    else if (token.type == eTokenType::Number)
    {
        // Peek at the next token to determine its type
        const auto& operatorToken = m_lexer.PeekNextToken();

        if (operatorToken.type == eTokenType::Operator)
        {
            // Peek at the next token to determine its type
            const auto& nextToken = m_lexer.PeekNextToken(1);

            if (nextToken.type == eTokenType::String)
            {
                // If the left term is a string, parse string operator expression
                left = ParseStringOperatorExpression(std::move(left));
            }
            else
            {
                // If the left term is a number, parse arithmetic operator expression
                left = ParseArithmeticOperatorExpression(std::move(left));
            }
        }
    }
    else if (token.type == eTokenType::String)
    {
        // If the left term is a string, parse string operator expression
        left = ParseStringOperatorExpression(std::move(left));
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FExpressionParser::ParseArithmeticOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_lexer.HasNextToken())
    {
        // Peek the next token
        const auto& token = m_lexer.PeekNextToken();

        // Check if the token is an operator and if it's addition or subtraction
        if (token.type == eTokenType::Operator && (token.lexeme == "+" || token.lexeme == "-"))
        {
            // Consume the operator token
            m_lexer.GetNextToken();

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

ExpressionPtr FExpressionParser::ParseComparisonOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_lexer.HasNextToken())
    {
        // Peek the next token
        const auto& token = m_lexer.PeekNextToken();

        if (token.type == eTokenType::Operator && token.lexeme == "=")
        {
            // Consume the token '='
            m_lexer.GetNextToken();

            if (!m_lexer.TryConsumeToken(eTokenType::Operator, "="))
            {
                throw FSyntaxException("Excepted '=='");
            }

            // Parse the right term
            ExpressionPtr right = ParseTerm();

            left = std::make_unique<FEqualToExpression>(std::move(left), std::move(right));
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
    while (m_lexer.HasNextToken())
    {
        // Peek the next token
        const auto& token = m_lexer.PeekNextToken();

        if (token.type == eTokenType::Operator)
        {
            if (token.lexeme == "+")
            {
                // Consume the operator token
                m_lexer.GetNextToken();

                // Parse the right string
                ExpressionPtr right = ParseString();

                // Create a string operator node for concatenation
                left = std::make_unique<FStringOperatorExpression>("+", std::move(left), std::move(right));
            }
            else if (token.lexeme == "*")
            {
                // Consume the operator token
                m_lexer.GetNextToken();

                // Parse the right string
                ExpressionPtr right = ParseString();

                // Create a string operator node for concatenation
                left = std::make_unique<FStringOperatorExpression>("*", std::move(left), std::move(right));
            }
            else
            {
                // If the token is not a concatenation operator, break the loop
                break;
            }
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

ExpressionPtr FExpressionParser::ParseIdentifierOperatorExpression(ExpressionPtr left)
{
    // Continue parsing while there are tokens available
    while (m_lexer.HasNextToken())
    {
        // Peek the next token
        const auto& token = m_lexer.PeekNextToken();

        if (token.type == eTokenType::Operator)
        {
            if (token.lexeme == "+" || token.lexeme == "-")
            {
                // Consume the operator token
                m_lexer.GetNextToken();

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
                break;
            }
        }
        else
        {
            // If the token is not an operator applicable to identifiers, break the loop
            break;
        }
    }

    // Return the parsed expression
    return left;
}

ExpressionPtr FExpressionParser::ParseTernaryExpression(ExpressionPtr condition)
{
    // Peek at the next token to check for the ternary operator '?'
    auto nextToken = m_lexer.PeekNextToken();

    // Ensure the condition expression is followed by the ternary operator '?'
    if (nextToken.type != eTokenType::Punctuation || nextToken.lexeme != "?")
    {
        // If not, return the condition expression as is
        return condition;
    }

    // Consume the ternary operator token '?'
    m_lexer.GetNextToken();

    // Parse the true expression (the expression after the '?')
    ExpressionPtr trueExpr = ParseExpression();

    // Get the next token which should be the ':' separating true and false expressions
    nextToken = m_lexer.GetNextToken();

    // Consume the colon token ':'
    if (nextToken.type != eTokenType::Punctuation || nextToken.lexeme != ":")
    {
        // If the token is not a colon, throw a syntax exception
        throw FSyntaxException("Expected ':' in ternary expression after '?'");
    }

    // Parse the false expression (the expression after the ':')
    ExpressionPtr falseExpr = ParseExpression();

    // Recursively check if the true expression or false expression is another ternary expression
    trueExpr = ParseTernaryExpression(std::move(trueExpr));
    falseExpr = ParseTernaryExpression(std::move(falseExpr));

    // Create and return the ternary expression object
    return std::make_unique<FTernaryExpression>(
        std::move(condition),
        std::move(trueExpr),
        std::move(falseExpr)
    );
}

ExpressionPtr FExpressionParser::ParseTerm()
{
    // Parse the initial factor and store it as the left operand
    ExpressionPtr left = ParseFactor();

    // Continue parsing while there are more tokens available
    while (m_lexer.HasNextToken())
    {
        // If the left operand is not a number, stop parsing further
        if (!dynamic_cast<FNumberExpression*>(left.get())
            && !dynamic_cast<FIdentifierExpression*>(left.get()))
        {
            break;
        }

        // Peek at the next token to determine the operator
        const SToken& token = m_lexer.PeekNextToken();

        // Peek at the next token to determine the operator
        const SToken& nextToken = m_lexer.PeekNextToken(1);

        if (nextToken.type == eTokenType::String)
            break;

        // Check if the token is an operator and if it is one of '*', '/', or '%'
        if (token.type == eTokenType::Operator && (token.lexeme == "*" || token.lexeme == "/" || token.lexeme == "%"))
        {
            // Consume the operator token
            m_lexer.GetNextToken();

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

                left = ParseComparisonOperatorExpression(std::move(left));
            }
        }
        else if (token.type == eTokenType::Operator && (token.lexeme == "<" || token.lexeme == ">"))
        {
            // Consume the operator token
            m_lexer.GetNextToken();

            // Parse the next factor and store it as the right operand
            ExpressionPtr right = ParseFactor();

            if (token.lexeme == "<")
            {
                left = std::make_unique<FLessThanExpression>(std::move(left), std::move(right));
            }
            else if (token.lexeme == ">")
            {
                left = std::make_unique<FGreaterThanExpression>(std::move(left), std::move(right));
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
    const auto& token = m_lexer.PeekNextToken();

    // Check if the token is a boolean and parse it if true
    if (token.type == eTokenType::Boolean)
    {
        return ParseBoolean();
    }
    // Check if the token is a number and parse it if true
    else if (token.type == eTokenType::Number)
    {
        return ParseNumber();
    }
    // Check if the token is a string and parse it if true
    else if (token.type == eTokenType::String)
    {
        return ParseString();
    }
    // Check if the token is an identifier and parse it if true
    else if (token.type == eTokenType::Identifier)
    {
        return ParseIdentifier();
    }
    else if (token.lexeme == "(")
    {
        // Consume the '(' token
        m_lexer.GetNextToken();

        // Parse the expression inside the parentheses
        ExpressionPtr expr = ParseExpression();

        // Ensure the next token is ')'
        if (m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
        {
            throw FSyntaxException("Expected ')' after expression");
        }

        return expr;
    }

    // If the token is none of the expected types, throw an error
    throw FSyntaxException("Unexpected token in factor: " + token.lexeme);
}

ExpressionPtr FExpressionParser::ParseIdentifier()
{
    // Get the next token
    SToken token = m_lexer.GetNextToken();

    // Check if the token is an identifier
    if (token.type != eTokenType::Identifier)
    {
        // Throw an error if it's not an identifier
        throw FSyntaxException("Expected 'identifier'");
    }

    // Create an identifier node with the token's lexeme as the identifier name
    return std::make_unique<FIdentifierExpression>(token.lexeme);
}

ExpressionPtr FExpressionParser::ParseBoolean()
{
    // Get at the next token to determine its type
    const auto& token = m_lexer.GetNextToken();

    // Check if the token is a boolean
    if (token.type == eTokenType::Boolean)
    {
        // Convert the token's lexeme to a boolean value
        bool value = (token.lexeme == "true");

        // Create a boolean expression with the boolean value
        return std::make_unique<FBooleanExpression>(value);
    }

    // If the token is not a boolean, throw a syntax exception
    throw FSyntaxException("Expected boolean");
}

ExpressionPtr FExpressionParser::ParseNumber()
{
    // Get the next token
    SToken token = m_lexer.GetNextToken();

    // Check if the token is a number
    if (token.type != eTokenType::Number)
    {
        // Throw an error if it's not a number
        throw FSyntaxException("Expected 'number'");
    }

    // Convert the token's lexeme to an integer and create a number node with that value
    int value = std::stoi(token.lexeme);
    return std::make_unique<FNumberExpression>(value);
}

ExpressionPtr FExpressionParser::ParseString()
{
    // Get the next token
    SToken token = m_lexer.GetNextToken();

    // Check if the token is a string
    if (token.type != eTokenType::String)
    {
        // Throw an error if it's not a string
        throw FSyntaxException("Expected 'string'");
    }

    // Create a string node with the token's lexeme as its value
    return std::make_unique<FStringExpression>(token.lexeme);
}
