/**
 * @file logical_and_expression.cpp
 * @brief Implementation of the FLogicalAndExpression class.
 */

// Include header file for this implementation
#include "ast/expression/operator/logical/logical_and_expression.hpp"

// Include for std::runtime_error
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"
#include "value/boolean_value.hpp"

FLogicalAndExpression::FLogicalAndExpression(ExpressionPtr left, ExpressionPtr right)
    // Call base class constructor to initialize operands
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FLogicalAndExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Logical AND must have exactly two operands");
    }

    // Evaluate the left and right operands
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    if (leftValue->IsNumber() && rightValue->IsNumber())
    {
        const auto& leftVal = std::dynamic_pointer_cast<FNumberValue>(leftValue);
        const auto& rightVal = std::dynamic_pointer_cast<FNumberValue>(rightValue);

        // Extract integer values from the variants
        int leftInt = leftVal->GetValue();
        int rightInt = rightVal->GetValue();

        // Return result of logical AND operation
        return std::make_shared<FBooleanValue>(leftInt && rightInt);
    }
    else if (leftValue->IsBoolean() && rightValue->IsBoolean())
    {
        const auto& leftVal = std::dynamic_pointer_cast<FBooleanValue>(leftValue);
        const auto& rightVal = std::dynamic_pointer_cast<FBooleanValue>(rightValue);

        // Extract integer values from the variants
        bool leftInt = leftVal->GetValue();
        bool rightInt = rightVal->GetValue();

        // Return result of logical AND operation
        return std::make_shared<FBooleanValue>(leftInt && rightInt);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for logical AND operation");
    }
}
