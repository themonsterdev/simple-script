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

#include "number_value.hpp"
#include "boolean_value.hpp"

FLogicalOrExpression::FLogicalOrExpression(ExpressionPtr left, ExpressionPtr right)
    // Initialize base class with provided expressions
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FLogicalOrExpression::Evaluate(const FContext& context) const
{
    // Check if both operands are valid
    if (!m_left || !m_right)
    {
        // Throw error if operands are missing
        throw std::runtime_error("Logical OR must have exactly two operands");
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
    else if (leftValue->IsBoolean() || rightValue->IsBoolean())
    {
        const auto& leftVal = std::dynamic_pointer_cast<FBooleanValue>(leftValue);
        const auto& rightVal = std::dynamic_pointer_cast<FBooleanValue>(rightValue);

        // Extract integer values from the variants
        bool leftInt = leftVal->GetValue();
        bool rightInt = rightVal->GetValue();

        // Return result of logical AND operation
        return std::make_shared<FBooleanValue>(leftInt || rightInt);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for logical OR operation");
    }
}
