/**
 * @file bitwise_or_expression.cpp
 * @brief Implementation of the FBitwiseOrExpression class.
 */

// Include header file for the FBitwiseOrExpression class
#include "ast/expression/operator/bitwise/bitwise_or_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"
#include "value/number_value.hpp"

#include <stdexcept>

FBitwiseOrExpression::FBitwiseOrExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FBitwiseOrExpression::Evaluate(const FContext& context) const
{
    // Check if both left and right operands are not null
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Both operands must be provided for bitwise OR expression");
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
        throw std::runtime_error("Both operands of bitwise OR expression must be integers");
    }

    // Perform the bitwise OR operation and return the result
    return std::make_shared<FNumberValue>(leftInt | rightInt);
}
