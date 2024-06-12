/**
 * @file modulo_expression.cpp
 * @brief Implementation of the modulo expression class constructor and member functions.
 */

// Include header file for this implementation
#include "ast/expression/operator/multiplicative/modulo_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"

FModuloExpression::FModuloExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FModuloExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Modulo operator must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
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
        throw std::runtime_error("Invalid operand types for modulo operation");
    }

    // Validate operands before performing operations
    if (rightInt == 0) // Check if divisor is zero
    {
        // Throw error if modulo by zero is attempted
        throw std::runtime_error("Modulo by zero error");
    }

    // Return result of modulo operation
    return std::make_shared<FNumberValue>(leftInt % rightInt);
}
