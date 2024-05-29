/**
 * @file greater_than_expression.cpp
 * @brief Implementation of the greater-than expression class constructor and member functions.
 */

// Include header file for this implementation
#include "expression/operator/comparison/greater_than_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FGreaterThanExpression::FGreaterThanExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FGreaterThanExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Greater than comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
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
        throw std::runtime_error("Invalid operand types for greater than operation");
    }

    // Return result of greater-than comparison
	return leftInt > rightInt;
}
