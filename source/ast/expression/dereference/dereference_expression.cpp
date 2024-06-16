/**
 * @file dereference_expression.cpp
 * @brief Implementation of the dereference expression class.
 */

// Include the header file for the FDereferenceExpression class
#include "ast/expression/dereference/dereference_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FDereferenceExpression::FDereferenceExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FDereferenceExpression::Evaluate(const FContext& context) const
{
    return {};
}
