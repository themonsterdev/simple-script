/**
 * @file equal_to_expression.cpp
 * @brief Implementation of the equal-to expression class constructor and member functions.
 */

// Include header file for this implementation
#include "expression/operator/equality/equal_to_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FEqualToExpression::FEqualToExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FEqualToExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Equal comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
    int leftInt = 0, rightInt = 0;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt  = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for equal operation");
    }

    // Return result of equal-to comparison
	return leftInt == rightInt;
}
