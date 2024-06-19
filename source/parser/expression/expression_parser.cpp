/**
 * @file expression_parser.cpp
 * @brief Implementation of the FExpressionParser class.
 */

#include "parser/expression/expression_parser.hpp"
#include "parser/exception/syntax_exception.hpp"
#include "lexer/lexer.hpp"

// Expressions
#include "ast/expression/access/access_expression.hpp"
#include "ast/expression/access/access_method_expression.hpp"

#include "ast/expression/addressof/address_of_expression.hpp"
#include "ast/expression/array/array_expression.hpp"

#include "ast/expression/assignment/assignment_expression.hpp"
#include "ast/expression/assignment/compound_assignment_expression.hpp"

#include "ast/expression/cast/cast_expression.hpp"
#include "ast/expression/dereference/dereference_expression.hpp"

#include "ast/expression/exception/throw_expression.hpp"

#include "ast/expression/memory/delete_expression.hpp"
#include "ast/expression/memory/new_expression.hpp"

#include "ast/expression/operator/additive/addition_expression.hpp"
#include "ast/expression/operator/additive/subtraction_expression.hpp"

#include "ast/expression/operator/multiplicative/division_expression.hpp"
#include "ast/expression/operator/multiplicative/modulo_expression.hpp"
#include "ast/expression/operator/multiplicative/multiply_expression.hpp"

#include "ast/expression/operator/shift/shift_left_expression.hpp"
#include "ast/expression/operator/shift/shift_right_expression.hpp"

#include "ast/expression/operator/equality/equal_to_expression.hpp"
#include "ast/expression/operator/equality/not_equal_expression.hpp"

#include "ast/expression/operator/comparison/greater_than_expression.hpp"
#include "ast/expression/operator/comparison/greater_than_or_equal_expression.hpp"
#include "ast/expression/operator/comparison/less_than_expression.hpp"
#include "ast/expression/operator/comparison/less_than_or_equal_expression.hpp"
#include "ast/expression/operator/comparison/three_way_expression.hpp"

#include "ast/expression/operator/bitwise/bitwise_and_expression.hpp"
#include "ast/expression/operator/bitwise/bitwise_or_expression.hpp"
#include "ast/expression/operator/bitwise/bitwise_xor_expression.hpp"

#include "ast/expression/operator/logical/logical_and_expression.hpp"
#include "ast/expression/operator/logical/logical_or_expression.hpp"

#include "ast/expression/operator/ternary/ternary_expression.hpp"

#include "ast/expression/operator/unary/unary_negate_expression.hpp"
#include "ast/expression/operator/unary/unary_not_expression.hpp"

#include "ast/expression/operator/comma_expression.hpp"

#include "ast/expression/postfix/postfix_expression.hpp"
#include "ast/expression/prefix/prefix_expression.hpp"

#include "ast/expression/scope/scope_expression.hpp"
#include "ast/expression/sizeof/sizeof_expression.hpp"
#include "ast/expression/subscript/subscript_expression.hpp"

#include "ast/expression/invokable/call_expression.hpp"

#include "ast/expression/literal/boolean_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"
#include "ast/expression/literal/string_expression.hpp"
#include "ast/expression/literal/string_format_expression.hpp"

#include "ast/expression/identifier_expression.hpp"

#include <iostream>

FExpressionParser::FExpressionParser(FLexer& lexer)
    : m_lexer(lexer)
{}

ExpressionPtr FExpressionParser::ParseExpression()
{
    return ParseCommaExpression();
}

ExpressionPtr FExpressionParser::ParseCommaExpression()
{
    ExpressionPtr left = ParseAssignmentExpression();

    if (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","))
    {
        ExpressionList expressions;
        expressions.push_back(std::move(left));

        ExpressionPtr right = ParseAssignmentExpression();
        expressions.push_back(std::move(right));

        while (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","))
        {
            right = ParseAssignmentExpression();
            expressions.push_back(std::move(right));
        }

        return std::make_unique<FCommaExpression>(std::move(expressions));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseAssignmentExpression()
{
    ExpressionPtr left = ParseThrowOperatorExpression();

    const auto& token = m_lexer.PeekNextToken();

    if (token.IsSameType(eTokenType::Operator))
    {
        const auto& lexeme = token.GetLexeme();

        if (lexeme == "="   ||
            lexeme == "+="  || lexeme == "-="  ||
            lexeme == "*="  || lexeme == "/="  || lexeme == "%=" ||
            lexeme == "<<=" || lexeme == ">>=" ||
            lexeme == "&="  || lexeme == "^="  || lexeme == "|=")
        {
            m_lexer.GetNextToken();
            ExpressionPtr right = ParseExpression();

            if (lexeme == "=")
            {
                left = std::make_unique<FAssignmentExpression>(std::move(left), std::move(right));
            }
            else
            {
                left = std::make_unique<FCompoundAssignmentExpression>(lexeme, std::move(left), std::move(right));
            }
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseThrowOperatorExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Keyword, "throw"))
    {
        ExpressionPtr left = ParseTernaryConditionalExpression();

        return std::make_unique<FThrowExpression>(std::move(left));
    }

    return ParseTernaryConditionalExpression();
}

ExpressionPtr FExpressionParser::ParseTernaryConditionalExpression()
{
    ExpressionPtr left = ParseLogicalOrExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "?"))
    {
        ExpressionPtr trueExpr = ParseExpression();

        if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ":"))
        {
            throw FSyntaxException("Expected ':' in ternary expression after '?'");
        }

        ExpressionPtr falseExpr = ParseExpression();

        left = std::make_unique<FTernaryExpression>(std::move(left), std::move(trueExpr), std::move(falseExpr));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseLogicalOrExpression()
{
    ExpressionPtr left = ParseLogicalAndExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "||"))
    {
        ExpressionPtr right = ParseLogicalAndExpression();
        left = std::make_unique<FLogicalOrExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseLogicalAndExpression()
{
    ExpressionPtr left = ParseBitwiseOrExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "&&"))
    {
        ExpressionPtr right = ParseBitwiseOrExpression();
        left = std::make_unique<FLogicalAndExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseOrExpression()
{
    ExpressionPtr left = ParseBitwiseXorExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "|"))
    {
        ExpressionPtr right = ParseBitwiseXorExpression();
        left = std::make_unique<FBitwiseOrExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseXorExpression()
{
    ExpressionPtr left = ParseBitwiseAndExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "^"))
    {
        ExpressionPtr right = ParseBitwiseAndExpression();
        left = std::make_unique<FBitwiseXorExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseBitwiseAndExpression()
{
    ExpressionPtr left = ParseEqualityExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "&"))
    {
        ExpressionPtr right = ParseEqualityExpression();
        left = std::make_unique<FBitwiseAndExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseEqualityExpression()
{
    ExpressionPtr left = ParseComparisonExpression();

    while (m_lexer.HasNextToken())
    {
        if (m_lexer.TryConsumeToken(eTokenType::Operator, "=="))
        {
            ExpressionPtr right = ParseComparisonExpression();
            left = std::make_unique<FEqualToExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "!="))
        {
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
    ExpressionPtr left = ParseThreeWayExpression();

    while (m_lexer.HasNextToken())
    {
        if (m_lexer.TryConsumeToken(eTokenType::Operator, "<"))
        {
            ExpressionPtr right = ParseThreeWayExpression();
            left = std::make_unique<FLessThanExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "<="))
        {
            ExpressionPtr right = ParseThreeWayExpression();
            left = std::make_unique<FLessThanOrEqualExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, ">"))
        {
            ExpressionPtr right = ParseThreeWayExpression();
            left = std::make_unique<FGreaterThanExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, ">="))
        {
            ExpressionPtr right = ParseThreeWayExpression();
            left = std::make_unique<FGreaterThanOrEqualExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseThreeWayExpression()
{
    ExpressionPtr left = ParseShiftExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Operator, "<=>"))
    {
        ExpressionPtr right = ParseShiftExpression();
    
        left = std::make_unique<FThreeWayExpression>(std::move(left), std::move(right));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseShiftExpression()
{
    ExpressionPtr left = ParseAdditiveExpression();

    while (m_lexer.HasNextToken())
    {
        if (m_lexer.TryConsumeToken(eTokenType::Operator, "<<"))
        {
            ExpressionPtr right = ParseAdditiveExpression();
            left = std::make_unique<FShiftLeftExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, ">>"))
        {
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

ExpressionPtr FExpressionParser::ParseAdditiveExpression()
{
    ExpressionPtr left = ParseMultiplicativeExpression();

    while (m_lexer.HasNextToken())
    {
        if (m_lexer.TryConsumeToken(eTokenType::Operator, "+"))
        {
            ExpressionPtr right = ParseMultiplicativeExpression();
            left = std::make_unique<FAdditionExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "-"))
        {
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
    ExpressionPtr left = ParseDeleteExpression();

    while (m_lexer.HasNextToken())
    {
        if (m_lexer.TryConsumeToken(eTokenType::Operator, "*"))
        {
            ExpressionPtr right = ParseDeleteExpression();
            left = std::make_unique<FMultiplicationExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "/"))
        {
            ExpressionPtr right = ParseDeleteExpression();
            left = std::make_unique<FDivisionExpression>(std::move(left), std::move(right));
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "%"))
        {
            ExpressionPtr right = ParseDeleteExpression();
            left = std::make_unique<FModuloExpression>(std::move(left), std::move(right));
        }
        else
        {
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseDeleteExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Keyword, "delete"))
    {
        ExpressionPtr left = ParseNewExpression();
        return std::make_unique<FDeleteExpression>(std::move(left));
    }
    return ParseNewExpression();
}

ExpressionPtr FExpressionParser::ParseNewExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Keyword, "new"))
    {
        ExpressionPtr left = ParseSizeofExpression();

        return std::make_unique<FNewExpression>(std::move(left));
    }
    return ParseSizeofExpression();
}

ExpressionPtr FExpressionParser::ParseSizeofExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Keyword, "sizeof"))
    {
        ExpressionPtr left = ParseAddressOfExpression();

        return std::make_unique<FSizeofExpression>(std::move(left));
    }

    return ParseAddressOfExpression();
}

ExpressionPtr FExpressionParser::ParseAddressOfExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Operator, "&"))
    {
        ExpressionPtr operand = ParseDereferenceExpression();

        return std::make_unique<FAddressOfExpression>(std::move(operand));
    }

    return ParseDereferenceExpression();
}

ExpressionPtr FExpressionParser::ParseDereferenceExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Operator, "*"))
    {
        ExpressionPtr operand = ParseCastExpression();

        return std::make_unique<FDereferenceExpression>(std::move(operand));
    }

    return ParseCastExpression();
}

ExpressionPtr FExpressionParser::ParseCastExpression()
{
    // if (m_lexer.TryConsumeToken(eTokenType::Operator, "("))
    // {
    //     // Assuming ParseType() is a function that parses a type
    //     auto type = ParseType();
    //     if (!type)
    //     {
    //         throw std::runtime_error("Expected type for cast expression");
    //     }
    // 
    //     if (!m_lexer.TryConsumeToken(eTokenType::Operator, ")"))
    //     {
    //         throw std::runtime_error("Expected closing parenthesis for cast expression");
    //     }
    // 
    //     ExpressionPtr operand = ParseUnaryExpression();
    //     return std::make_unique<FCastExpression>(std::move(type), std::move(operand));
    // }
    return ParseUnaryExpression();
}

ExpressionPtr FExpressionParser::ParseUnaryExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Operator, "+"))
    {

    }
    else if (m_lexer.TryConsumeToken(eTokenType::Operator, "-"))
    {
        ExpressionPtr expr = ParseUnaryExpression();

        return std::make_unique<FUnaryNegateExpression>(std::move(expr));
    }
    else if (m_lexer.TryConsumeToken(eTokenType::Operator, "!"))
    {
        ExpressionPtr expr = ParseUnaryExpression();
        return std::make_unique<FUnaryNotExpression>(std::move(expr));
    }
    // else if (m_lexer.TryConsumeToken(eTokenType::Operator, "~"))
    // {
    //     ExpressionPtr expr = ParseUnaryExpression();
    //     return std::make_unique<FBinaryNotExpression>(std::move(expr));
    // }

    return ParsePostfixExpression();
}

ExpressionPtr FExpressionParser::ParsePostfixExpression()
{
    ExpressionPtr left = ParseAccessExpression();

    while (m_lexer.HasNextToken())
    {
        const auto& token = m_lexer.PeekNextToken();

        if (token.IsSameType(eTokenType::Operator))
        {
            // Postfix increment or decrement
            if (token.IsSameLexeme("++") || token.IsSameLexeme("--"))
            {
                const auto& op = token.GetLexeme();
                m_lexer.GetNextToken(); // Consume the operator token

                left = std::make_unique<FPostfixExpression>(std::move(left), op);
            }
            else
            {
                // No more postfix expressions
                break;
            }
        }
        else
        {
            // No more postfix expressions
            break;
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseAccessExpression()
{
    ExpressionPtr left = ParseSubscriptExpression();

    while (m_lexer.HasNextToken())
    {
        std::string op = "";

        if (m_lexer.TryConsumeToken(eTokenType::Operator, "."))
        {
            op = ".";
        }
        else if (m_lexer.TryConsumeToken(eTokenType::Operator, "->"))
        {
            op = "->";
        }
        else
        {
            break;
        }

        // Consume member name
        const auto& memberToken = m_lexer.GetNextToken();
        if (!memberToken.IsSameType(eTokenType::Identifier))
        {
            throw FSyntaxException("Expected 'identifier' after '" + op + "' operator");
        }
        std::string memberName = memberToken.GetLexeme();

        // Check if it's a function call
        if (m_lexer.TryConsumeToken(eTokenType::Delimiter, "("))
        {
            // Parse function arguments
            ExpressionList arguments;
            if (!m_lexer.MatchToken(eTokenType::Delimiter, ")"))
            {
                do
                {
                    arguments.push_back(ParseAssignmentExpression());
                } while (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","));
            }

            if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
            {
                throw FSyntaxException("Expected ')' after function arguments");
            }

            // Create access method expression
            left = std::make_unique<FAccessMethodExpression>(std::move(left), op, memberName);

            if (auto accessMethod = dynamic_cast<FAccessMethodExpression*>(left.get()))
            {
                accessMethod->SetArguments(std::move(arguments));
            }
        }
        else
        {
            // Create access expression
            left = std::make_unique<FAccessExpression>(std::move(left), op, memberName);
        }
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseSubscriptExpression()
{
    ExpressionPtr left = ParseFunctionCallExpression();

    if (m_lexer.TryConsumeToken(eTokenType::Delimiter, "["))
    {
        ExpressionPtr index = ParseExpression();

        if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, "]"))
        {
            throw FSyntaxException("Expected ']' after subscript expression");
        }
        return std::make_unique<FSubscriptExpression>(std::move(left), std::move(index));
    }

    return left;
}

ExpressionPtr FExpressionParser::ParseFunctionCallExpression()
{
    ExpressionPtr left = ParsePrefixAndPostfixExpression();

    while (m_lexer.TryConsumeToken(eTokenType::Delimiter, "("))
    {
        std::vector<ExpressionPtr> arguments;
        const auto& token = m_lexer.PeekNextToken();

        if (!token.IsSameTypeAndLexeme(eTokenType::Delimiter, ")"))
        {
            do
            {
                arguments.push_back(ParseAssignmentExpression());
            } while (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","));
        }

        if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
        {
            throw FSyntaxException("Expected ')' after arguments in function call");
        }

        left = std::make_unique<FCallExpression>(std::move(left), std::move(arguments));
    }
    return left;
}

ExpressionPtr FExpressionParser::ParsePrefixAndPostfixExpression()
{
    if (m_lexer.TryConsumeToken(eTokenType::Operator, "++"))
    {
        std::string op = "++";

        ExpressionPtr left = ParseScopeResolutionExpression();
        
        return std::make_unique<FPrefixExpression>(std::move(left), op);
    }

    if (m_lexer.TryConsumeToken(eTokenType::Operator, "--"))
    {
        std::string op = "--";

        ExpressionPtr left = ParseScopeResolutionExpression();
        
        return std::make_unique<FPrefixExpression>(std::move(left), op);
    }

    return ParseScopeResolutionExpression();
}

ExpressionPtr FExpressionParser::ParseScopeResolutionExpression()
{
    ExpressionPtr left = ParsePrimaryExpression();

    // if (m_lexer.TryConsumeToken(eTokenType::Operator, "::"))
    // {
    //     ExpressionPtr right = ParseScopeResolutionExpression();
    // 
    //     return std::make_unique<FScopeExpression>(std::move(left), std::move(right));
    // }
    
    return left;
}

ExpressionPtr FExpressionParser::ParsePrimaryExpression()
{
    if (!m_lexer.HasNextToken())
    {
        throw FSyntaxException("Unexpected end of expression");
    }

    const auto& token = m_lexer.GetNextToken();

    switch (token.GetType())
    {
    case eTokenType::Number:
        return std::make_unique<FNumberExpression>(std::stoi(token.GetLexeme()));
    case eTokenType::Boolean:
        return std::make_unique<FBooleanExpression>(token.GetLexeme() == "true");
    case eTokenType::String:
        return std::make_unique<FStringExpression>(token.GetLexeme());
    case eTokenType::StringFormatLiteral:
        return std::make_unique<FStringFormatExpression>(token.GetLexeme());
    case eTokenType::Identifier:
    case eTokenType::Keyword:
        return std::make_unique<FIdentifierExpression>(token.GetLexeme());
    case eTokenType::Delimiter:
    {
        if (token.IsSameLexeme("("))
        {
            ExpressionPtr expr = ParseExpression();
            if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, ")"))
            {
                throw FSyntaxException("Expected ')' after expression");
            }
            return expr;
        }
        else if (token.IsSameLexeme("["))
        {
            ExpressionList elements;

            if (!m_lexer.MatchToken(eTokenType::Delimiter, "]"))
            {
                do
                {
                    elements.push_back(ParsePrimaryExpression());
                } while (m_lexer.TryConsumeToken(eTokenType::Delimiter, ","));
            }

            if (!m_lexer.TryConsumeToken(eTokenType::Delimiter, "]"))
            {
                throw FSyntaxException("Expected ']' after array elements");
            }

            return std::make_unique<FArrayExpression>(std::move(elements));
        }
        break;
    }
    default:
        throw FSyntaxException("Unexpected expression token: " + token.ToString());
    }

    return nullptr;
}
