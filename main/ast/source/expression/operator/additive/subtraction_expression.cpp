/**
 * @file subtraction_expression.cpp
 * @brief Implementation of the FSubtractionExpression class.
 */

// Include header file for the FSubtractionExpression class
#include "expression/operator/additive/subtraction_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

FSubtractionExpression::FSubtractionExpression(ExpressionPtr left, ExpressionPtr right)
// Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FSubtractionExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Subtraction operator must have exactly two operands");
    }

    // Evaluate the left and right operands
    Value leftValue = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract integer values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for subtraction operation");
    }

    // Return the result of the subtraction operation
    return leftInt - rightInt;
}
