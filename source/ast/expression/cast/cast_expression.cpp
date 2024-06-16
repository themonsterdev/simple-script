/**
 * @file cast_expression.cpp
 * @brief Implementation of the cast expression class.
 */

// Include the header file for the FCastExpression class
#include "ast/expression/cast/cast_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FCastExpression::FCastExpression(TypePtr targetType, ExpressionPtr expression)
    : m_targetType(targetType)
    , m_expression(std::move(expression))
{}

ValuePtr FCastExpression::Evaluate(const FContext& context) const
{
    return {};
}
