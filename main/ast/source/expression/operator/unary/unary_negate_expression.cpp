/**
 * @file unary_negate_expression.cpp
 * @brief Implementation of the unary negate expression class.
 */

// Include the header file for the FUnaryNegateExpression class
#include "expression/operator/unary/unary_negate_expression.hpp"
#include <stdexcept>

FUnaryNegateExpression::FUnaryNegateExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

Value FUnaryNegateExpression::Evaluate(const FContext& context) const
{
    // Evaluate the inner expression
    Value innerValue = m_expression->Evaluate(context);

    // Check if the value is an integer
    if (!std::holds_alternative<int>(innerValue))
    {
        throw std::runtime_error("Operand of unary negate must be integer");
    }

    // Negate the integer value
    int result = -std::get<int>(innerValue);

    return result;
}
