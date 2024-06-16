/**
 * @file scope_expression.cpp
 * @brief Implementation of the scope expression class.
 */

// Include the header file for the FScopeExpression class
#include "ast/expression/scope/scope_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FScopeExpression::FScopeExpression(ExpressionPtr left, std::string right)
    : m_left(std::move(left))
    , m_right(std::move(right))
{}

ValuePtr FScopeExpression::Evaluate(const FContext& context) const
{
    return {};
}
