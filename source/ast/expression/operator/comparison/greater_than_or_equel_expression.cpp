/**
 * @file greater_than_or_equal_expression.cpp
 * @brief Implementation of the FGreaterThanOrEqualExpression class.
 */

// Include header file for the FGreaterThanOrEqualExpression class
#include "ast/expression/operator/comparison/greater_than_or_equal_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"
#include "value/boolean_value.hpp"

FGreaterThanOrEqualExpression::FGreaterThanOrEqualExpression(ExpressionPtr left, ExpressionPtr right)
// Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FGreaterThanOrEqualExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Greater than or equal comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    // Extract integer values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (leftValue->IsNumber() && rightValue->IsNumber())
    {
        const auto& leftVal = std::dynamic_pointer_cast<FNumberValue>(leftValue);
        const auto& rightVal = std::dynamic_pointer_cast<FNumberValue>(rightValue);

        // Extract integer values from the variants
        leftInt = leftVal->GetValue();
        rightInt = rightVal->GetValue();
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for greater than or equal operation");
    }

    // Return the result of the greater-than-or-equal comparison
    return std::make_shared<FBooleanValue>(leftInt >= rightInt);
}
