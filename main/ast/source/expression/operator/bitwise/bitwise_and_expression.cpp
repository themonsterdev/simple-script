/**
 * @file bitwise_and_expression.cpp
 * @brief Implementation of the FBitwiseAndExpression class.
 */

// Include header file for the FBitwiseAndExpression class
#include "expression/operator/bitwise/bitwise_and_expression.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context.hpp"

#include "number_value.hpp"

FBitwiseAndExpression::FBitwiseAndExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FBitwiseAndExpression::Evaluate(const FContext& context) const
{
    // Check if both left and right operands are not null
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Both operands must be provided for bitwise AND expression");
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
        throw std::runtime_error("Both operands of bitwise AND expression must be integers");
    }

    // Perform the bitwise AND operation and return the result
    return std::make_shared<FNumberValue>(leftInt & rightInt);
}
