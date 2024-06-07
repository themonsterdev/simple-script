/**
 * @file equal_to_expression.cpp
 * @brief Implementation of the FEqualToExpression class.
 */

// Include header file for this implementation
#include "expression/operator/equality/equal_to_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "number_value.hpp"
#include "boolean_value.hpp"

FEqualToExpression::FEqualToExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FEqualToExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Equal comparison must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    // Extract integer values from the variants
    int leftInt = 0;
    int rightInt = 0;

    // Check if both operands are integers
    if (leftValue->IsNumber() && rightValue->IsNumber())
    {
        const auto& leftVal = std::dynamic_pointer_cast<FNumberValue>(leftValue);
        const auto& rightVal = std::dynamic_pointer_cast<FNumberValue>(rightValue);

        // Extract integer values from the variants
        leftInt = leftVal->GetValue();
        rightInt = rightVal->GetValue();
    }
    else
    {
        // Throw exception for invalid operand types
        throw std::runtime_error("Invalid operand types for equal operation");
    }

    // Return result of equal-to comparison
    return std::make_shared<FBooleanValue>(leftInt == rightInt);
}
