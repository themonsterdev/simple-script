/**
 * @file subtraction_expression.cpp
 * @brief Implementation of the FSubtractionExpression class.
 */

// Include header file for the FSubtractionExpression class
#include "expression/operator/additive/subtraction_expression.hpp"

// Include necessary standard library headers
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "number_value.hpp"

FSubtractionExpression::FSubtractionExpression(ExpressionPtr left, ExpressionPtr right)
// Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FSubtractionExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Subtraction operator must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue = m_left->Evaluate(context);
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
        throw std::runtime_error("Invalid operand types for subtraction operation");
    }

    // Return the result of the subtraction operation
    return std::make_shared<FNumberValue>(leftInt - rightInt);
}
