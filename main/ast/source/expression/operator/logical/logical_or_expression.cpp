/**
 * @file logical_or_expression.cpp
 * @brief Implementation of the logical OR expression class constructor and member functions.
 */

// Include header file for this implementation
#include "expression/operator/logical/logical_or_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FLogicalOrExpression::FLogicalOrExpression(ExpressionPtr left, ExpressionPtr right)
    // Initialize base class with provided expressions
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FLogicalOrExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Logical or must have exactly two operands");
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
        throw std::runtime_error("Invalid operand types for logical or operation");
    }

    // Return result of logical OR operation
	return leftInt || rightInt;
}
