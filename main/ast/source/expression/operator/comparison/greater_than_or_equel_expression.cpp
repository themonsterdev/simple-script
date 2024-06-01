/**
 * @file greater_than_or_equal_expression.cpp
 * @brief Implementation of the FGreaterThanOrEqualExpression class.
 */

// Include header file for the FGreaterThanOrEqualExpression class
#include "expression/operator/comparison/greater_than_or_equal_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

FGreaterThanOrEqualExpression::FGreaterThanOrEqualExpression(ExpressionPtr left, ExpressionPtr right)
// Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FGreaterThanOrEqualExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Greater than or equal comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract integer values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt  = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for greater than or equal operation");
    }

    // Return the result of the greater-than-or-equal comparison
    return leftInt >= rightInt;
}
