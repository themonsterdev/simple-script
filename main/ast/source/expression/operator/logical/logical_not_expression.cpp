/**
 * @file logical_not_expression.cpp
 * @brief Implementation of the logical NOT expression class constructor and member functions.
 */

// Include header file for this implementation
#include "expression/operator/logical/logical_not_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

FLogicalNotExpression::FLogicalNotExpression(ExpressionPtr expression)
    // Initialize member variable with provided expression
    : m_expression(std::move(expression))
{}

Value FLogicalNotExpression::Evaluate(const FContext& context) const
{
    // Check if the expression is valid
    if (!m_expression)
    {
        // Throw error if expression is missing
        throw std::runtime_error("Logical not comparison must have exactly one expression");
    }

    // Evaluate the expression
    Value expressionValue = m_expression->Evaluate(context);

    // Extract int value from the variants
    int expressionInt = 0;

    // Check if both operands are integers
    if (std::holds_alternative<int>(expressionValue))
    {
        // Extract integer value from the variant
        expressionInt = std::get<int>(expressionValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid expression types for logical not operation");
    }

	return !expressionInt;
}

const ExpressionPtr& FLogicalNotExpression::GetExpression() const
{
    // Return the expression associated with this logical NOT expression
    return m_expression;
}
