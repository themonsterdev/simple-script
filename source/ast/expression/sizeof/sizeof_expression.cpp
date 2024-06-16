/**
 * @file sizeof_expression.cpp
 * @brief Implementation of the sizeof expression class.
 */

// Include the header file for the FSizeofExpression class
#include "ast/expression/sizeof/sizeof_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FSizeofExpression::FSizeofExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FSizeofExpression::Evaluate(const FContext& context) const
{
    return {};
}
