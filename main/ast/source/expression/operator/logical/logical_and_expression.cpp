/**
 * @file logical_and_expression.cpp
 * @brief Implementation of the FLogicalAndExpression class.
 */

// Include header file for this implementation
#include "expression/operator/logical/logical_and_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FLogicalAndExpression::FLogicalAndExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FLogicalAndExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Logical AND must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        int leftInt = std::get<int>(leftValue);
        int rightInt = std::get<int>(rightValue);

        // Return result of logical AND operation
        return leftInt && rightInt;
    }
    else if (std::holds_alternative<bool>(leftValue) && std::holds_alternative<bool>(rightValue))
    {
        // Extract integer values from the variants
        bool leftInt = std::get<bool>(leftValue);
        bool rightInt = std::get<bool>(rightValue);

        // Return result of logical AND operation
        return leftInt && rightInt;
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for logical AND operation");
    }
}
