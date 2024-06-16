/**
 * @file subscript_expression.cpp
 * @brief Implementation of the subscript expression class.
 */

// Include the header file for the FSubscriptExpression class
#include "ast/expression/subscript/subscript_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FSubscriptExpression::FSubscriptExpression(ExpressionPtr array, ExpressionPtr index)
    : m_array(std::move(array))
    , m_index(std::move(index))
{}

ValuePtr FSubscriptExpression::Evaluate(const FContext& context) const
{
    return {};
}
