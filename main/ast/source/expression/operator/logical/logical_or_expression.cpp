/**
 * @file logical_or_expression.cpp
 * @brief Implementation of the FLogicalOrExpression class.
 */

// Include header file for this implementation
#include "expression/operator/logical/logical_or_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

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
        throw std::runtime_error("Logical OR must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        int leftInt = std::get<int>(leftValue);
        int rightInt = std::get<int>(rightValue);

        // Return result of logical OR operation
        return leftInt || rightInt;
    }
    else if (std::holds_alternative<bool>(leftValue) && std::holds_alternative<bool>(rightValue))
    {
        // Extract integer values from the variants
        bool leftInt = std::get<bool>(leftValue);
        bool rightInt = std::get<bool>(rightValue);

        // Return result of logical OR operation
        return leftInt || rightInt;
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for logical OR operation");
    }
}
