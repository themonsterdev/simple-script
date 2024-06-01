/**
 * @file not_equal_expression.cpp
 * @brief Implementation of the FNotEqualExpression class.
 */

// Include header file for this implementation
#include "expression/operator/equality/not_equal_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FNotEqualExpression::FNotEqualExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FNotEqualExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Not equal comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Check if both operands are integers
    if (!std::holds_alternative<int>(leftValue) || !std::holds_alternative<int>(rightValue))
    {
        // Throw exception for invalid operand types
        throw std::runtime_error("Invalid operand types for not equal operation");
    }

    // Extract integer values from the variants
    int leftInt  = std::get<int>(leftValue);
    int rightInt = std::get<int>(rightValue);

    // Return result of not-equal-to comparison
    return leftInt != rightInt;
}
