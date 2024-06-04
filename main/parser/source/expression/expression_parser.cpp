/**
 * @file expression_parser.cpp
 * @brief Implementation of the FExpressionParser class.
 */

#include "expression/expression_parser.hpp" // Include the expression parser header file
#include "exception/syntax_exception.hpp"   // Include the syntax exception header file
#include "lexer.hpp"                        // Include the tokenizer header file

// Expressions
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/operator/additive/subtraction_expression.hpp"

#include "expression/operator/multiplicative/division_expression.hpp"
#include "expression/operator/multiplicative/modulo_expression.hpp"
#include "expression/operator/multiplicative/multiply_expression.hpp"

#include "expression/operator/shift/shift_left_expression.hpp"
#include "expression/operator/shift/shift_right_expression.hpp"

#include "expression/operator/equality/equal_to_expression.hpp"
#include "expression/operator/equality/not_equal_expression.hpp"

#include "expression/operator/comparison/greater_than_expression.hpp"
#include "expression/operator/comparison/greater_than_or_equal_expression.hpp"
#include "expression/operator/comparison/less_than_expression.hpp"
#include "expression/operator/comparison/less_than_or_equal_expression.hpp"

#include "expression/operator/bitwise/bitwise_and_expression.hpp"
#include "expression/operator/bitwise/bitwise_or_expression.hpp"
#include "expression/operator/bitwise/bitwise_xor_expression.hpp"

#include "expression/operator/logical/logical_and_expression.hpp"
#include "expression/operator/logical/logical_or_expression.hpp"

#include "expression/operator/ternary/ternary_expression.hpp"

#include "expression/operator/unary/unary_negate_expression.hpp"
#include "expression/operator/unary/unary_not_expression.hpp"

#include "expression/invokable/call_expression.hpp"

#include "expression/literal/boolean_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/literal/string_format_expression.hpp"

#include "expression/string_operator_expression.hpp"
#include "expression/identifier_expression.hpp"

FExpressionParser::FExpressionParser(FLexer& lexer)
    : m_lexer(lexer)
{}

ExpressionPtr FExpressionParser::ParseExpression()
{
    return ParseTernaryExpression();
}

ExpressionPtr FExpressionParser::ParseTernaryExpression()
{
    ExpressionPtr condition = ParseLogicalOrExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "?")
    {
        // Consume the ternary operator token '?'
        m_lexer.GetNextToken();

        ExpressionPtr trueExpr = ParseExpression();

        if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ":")) // delimiter
        {
            throw FSyntaxException("Expected ':' in ternary expression after '?'");
        }

        ExpressionPtr falseExpr = ParseExpression();

        condition = std::make_unique<FTernaryExpression>(std::move(condition), std::move(trueExpr), std::move(falseExpr));
    }

    return condition;
}

ExpressionPtr FExpressionParser::ParseLogicalOrExpression()
{
    ExpressionPtr left = ParseLogicalAndExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "||")
    {
        m_lexer.GetNextToken();
        ExpressionPtr right = ParseLogicalAndExpression();
        left = std::make_unique<FLogicalOrExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseLogicalAndExpression()
{
    ExpressionPtr left = ParseBitwiseOrExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "&&")
    {
        m_lexer.GetNextToken();
        ExpressionPtr right = ParseBitwiseOrExpression();
        left = std::make_unique<FLogicalAndExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseOrExpression()
{
    ExpressionPtr left = ParseBitwiseXorExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "|")
    {
        m_lexer.GetNextToken();
        ExpressionPtr right = ParseBitwiseXorExpression();
        left = std::make_unique<FBitwiseOrExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseXorExpression()
{
    ExpressionPtr left = ParseBitwiseAndExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "^")
    {
        m_lexer.GetNextToken();
        ExpressionPtr right = ParseBitwiseAndExpression();
        left = std::make_unique<FBitwiseXorExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseAndExpression()
{
    ExpressionPtr left = ParseEqualityExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "&")
    {
        m_lexer.GetNextToken();
        ExpressionPtr right = ParseEqualityExpression();
        left = std::make_unique<FBitwiseAndExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseEqualityExpression()
{
    ExpressionPtr left = ParseComparisonExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "==")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseComparisonExpression();
            left = std::make_unique<FEqualToExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == "!=")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseComparisonExpression();
            left = std::make_unique<FNotEqualExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseComparisonExpression()
{
    ExpressionPtr left = ParseShiftExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "<")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseShiftExpression();
            left = std::make_unique<FLessThanExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == "<=")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseShiftExpression();
            left = std::make_unique<FLessThanOrEqualExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == ">")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseShiftExpression();
            left = std::make_unique<FGreaterThanExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == ">=")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseShiftExpression();
            left = std::make_unique<FGreaterThanOrEqualExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseShiftExpression()
{
    ExpressionPtr left = ParseAdditiveExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "<<")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseAdditiveExpression();
            left = std::make_unique<FShiftLeftExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == ">>")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseAdditiveExpression();
            left = std::make_unique<FShiftRightExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

// 	<=>

ExpressionPtr FExpressionParser::ParseAdditiveExpression()
{
    ExpressionPtr left = ParseMultiplicativeExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "+")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseMultiplicativeExpression();
            left = std::make_unique<FAdditionExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == "-")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseMultiplicativeExpression();
            left = std::make_unique<FSubtractionExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseMultiplicativeExpression()
{
    ExpressionPtr left = ParseUnaryExpression();

    while (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "*")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseUnaryExpression();
            left = std::make_unique<FMultiplicationExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == "/")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseUnaryExpression();
            left = std::make_unique<FDivisionExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.PeekNextToken().lexeme == "%")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseUnaryExpression();
            left = std::make_unique<FModuloExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseUnaryExpression()
{
    if (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator)
    {
        if (m_lexer.PeekNextToken().lexeme == "+")
        {
            m_lexer.GetNextToken();
            return ParseUnaryExpression();
        }
        else if (m_lexer.PeekNextToken().lexeme == "-")
        {
            m_lexer.GetNextToken();
            ExpressionPtr expr = ParseUnaryExpression();
            return std::make_unique<FUnaryNegateExpression>(std::move(expr));
        }
        else if (m_lexer.PeekNextToken().lexeme == "!")
        {
            m_lexer.GetNextToken();
            ExpressionPtr expr = ParseUnaryExpression();
            return std::make_unique<FUnaryNotExpression>(std::move(expr));
        }
        // else if (m_lexer.PeekNextToken().lexeme == "~")
        // {
        //     m_lexer.GetNextToken();
        //     ExpressionPtr expr = ParseUnaryExpression();
        //     return std::make_unique<FBinaryNotExpression>(std::move(expr));
        // }
    }
    return ParsePostfixExpression();
}

ExpressionPtr FExpressionParser::ParsePostfixExpression()
{
    ExpressionPtr left = ParseAccessExpression();

    // while (m_lexer.HasNextToken())
    // {
    //     if (m_lexer.PeekNextToken().type == eTokenType::Operator)
    //     {
    //         // Postfix increment or decrement
    //         if (m_lexer.PeekNextToken().lexeme == "++" || m_lexer.PeekNextToken().lexeme == "--")
    //         {
    //             m_lexer.GetNextToken(); // Consume the operator token
    //             left = std::make_unique<FPostfixIncrementDecrementExpression>(std::move(left), m_lexer.GetCurrentToken().lexeme);
    //         }
    //         else
    //         {
    //             // No more postfix expressions
    //             break;
    //         }
    //     }
    //     else
    //     {
    //         // No more postfix expressions
    //         break;
    //     }
    // }

    return left;
}

ExpressionPtr FExpressionParser::ParseAccessExpression()
{
    // Implementation for member access
    ExpressionPtr expr = ParseSubscriptExpression();
    // while (m_lexer.HasNextToken())
    // {
    //     if (m_lexer.PeekNextToken().type == eTokenType::Operator && (m_lexer.PeekNextToken().lexeme == "." || m_lexer.PeekNextToken().lexeme == "->"))
    //     {
    //         std::string op = m_lexer.GetNextToken().lexeme; // Consume '.' or '->'
    //         std::string memberName = m_lexer.GetNextToken().lexeme; // Consume member name
    //         expr = std::make_unique<FAccessExpression>(std::move(expr), op, memberName);
    //     }
    //     else
    //     {
    //         break;
    //     }
    // }
    return expr;
}

ExpressionPtr FExpressionParser::ParseSubscriptExpression()
{
    // Implementation for array operators
    ExpressionPtr expr = ParseCallExpression();

    // if (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Delimiter && m_lexer.PeekNextToken().lexeme == "[")
    // {
    //     m_lexer.GetNextToken(); // Consume '['
    //     ExpressionPtr index = ParseExpression();
    //     if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, "]"))
    //     {
    //         throw FSyntaxException("Expected ']' after subscript expression");
    //     }
    //     return std::make_unique<FSubscriptExpression>(std::move(expr), std::move(index));
    // }
    return expr;
}

ExpressionPtr FExpressionParser::ParseCallExpression()
{
    // Implementation for function calls
    ExpressionPtr expr = ParseCastExpression();

    while (m_lexer.HasNextToken() && m_lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        std::vector<ExpressionPtr> arguments;
        if (m_lexer.PeekNextToken().type != eTokenType::Delimiter || m_lexer.PeekNextToken().lexeme != ")")
        {
            do
            {
                arguments.push_back(ParseExpression());
            } while (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","));
        }
        if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
        {
            throw FSyntaxException("Expected ')' after arguments in function call");
        }

        expr = std::make_unique<FCallExpression>(std::move(expr), std::move(arguments));
    }
    return expr;
}

ExpressionPtr FExpressionParser::ParseCastExpression()
{
    // Implementation for functional casts
    // if (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "type")
    // {
    //     m_lexer.GetNextToken(); // Consume 'type'
    //     if (m_lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    //     {
    //         ExpressionPtr expr = ParseExpression();
    //         if (m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
    //         {
    //             return std::make_unique<FCastExpression>(std::move(expr));
    //         }
    //         else
    //         {
    //             throw FSyntaxException("Expected ')' after functional cast expression");
    //         }
    //     }
    //     else
    //     {
    //         throw FSyntaxException("Expected '(' after 'type' in functional cast expression");
    //     }
    // }
    return ParseSuffixAndPostfixExpression();
}

ExpressionPtr FExpressionParser::ParseSuffixAndPostfixExpression()
{
    // Implementation for suffix and postfix operators
    ExpressionPtr expr = ParseScopeResolutionExpression();
    // if (m_lexer.HasNextToken())
    // {
    //     if (m_lexer.PeekNextToken().type == eTokenType::Operator && (m_lexer.PeekNextToken().lexeme == "++" || m_lexer.PeekNextToken().lexeme == "--"))
    //     {
    //         std::string op = m_lexer.GetNextToken().lexeme; // Consume '++' or '--'
    //         return std::make_unique<FSuffixPostfixExpression>(std::move(expr), op);
    //     }
    // }
    return expr;
}

ExpressionPtr FExpressionParser::ParseScopeResolutionExpression()
{
    // Implementation for scope resolution
    ExpressionPtr expr = ParsePrimaryExpression();
    // if (m_lexer.HasNextToken() && m_lexer.PeekNextToken().type == eTokenType::Operator && m_lexer.PeekNextToken().lexeme == "::")
    // {
    //     m_lexer.GetNextToken(); // Consume '::'
    //     ExpressionPtr right = ParseScopeResolutionExpression();
    //     return std::make_unique<FScopeResolutionExpression>(std::move(expr), std::move(right));
    // }
    return expr;
}

ExpressionPtr FExpressionParser::ParsePrimaryExpression()
{
    SToken token;

    if (m_lexer.HasNextToken())
    {
        token = m_lexer.GetNextToken();

        if (token.type == eTokenType::Number)
        {
            return std::make_unique<FNumberExpression>(std::stoi(token.lexeme));
        }
        else if (token.type == eTokenType::Boolean)
        {
            return std::make_unique<FBooleanExpression>(token.lexeme == "true");
        }
        else if (token.type == eTokenType::String)
        {
            return std::make_unique<FStringExpression>(token.lexeme);
        }
        else if (token.type == eTokenType::StringFormatLiteral)
        {
            return std::make_unique<FStringFormatExpression>(token.lexeme);
        }
        else if (token.type == eTokenType::Identifier || token.type == eTokenType::Keyword)
        {
            return std::make_unique<FIdentifierExpression>(token.lexeme);
        }
        else if (token.type == eTokenType::Delimiter && token.lexeme == "(")
        {
            ExpressionPtr expr = ParseExpression();
            if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
            {
                throw FSyntaxException("Expected ')' after expression");
            }
            return expr;
        }
    }

    throw FSyntaxException("Unexpected end of expression: " + token.lexeme);
}
