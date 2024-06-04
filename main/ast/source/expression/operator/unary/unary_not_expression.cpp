/**
 * @file unary_not_expression.cpp
 * @brief Implementation of the unary not expression class.
 */

// Include the header file for the FUnaryNotExpression class
#include "expression/operator/unary/unary_not_expression.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

FUnaryNotExpression::FUnaryNotExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

Value FUnaryNotExpression::Evaluate(const FContext& context) const
{
    // Evaluate the inner expression
    Value innerValue = m_expression->Evaluate(context);

    // Check if the value is a boolean
    if (!std::holds_alternative<bool>(innerValue)) {
        throw std::runtime_error("Operand of unary negate must be boolean");
    }

    // Negate the boolean value
    bool result = !std::get<bool>(innerValue);

    return result;
}
