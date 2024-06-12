/**
 * @file shift_left_expression.cpp
 * @brief Implementation of the FShiftLeftExpression class.
 */

// Include base class header
#include "ast/expression/operator/shift/shift_left_expression.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"

FShiftLeftExpression::FShiftLeftExpression(ExpressionPtr left, ExpressionPtr right)
    : AComputeExpression(std::move(left), std::move(right))
{}

ValuePtr FShiftLeftExpression::Evaluate(const FContext& context) const
{
    // Check if left or right expressions are null pointers
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Shift left operator must have both left and right operands");
    }

    // Evaluate left and right expressions
    ValuePtr leftValue  = m_left->Evaluate(context);
    ValuePtr rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
    int leftInt, rightInt;

    // Check if both values are integers
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
        throw std::runtime_error("Shift left operator must have integer operands");
    }

    return std::make_shared<FNumberValue>(leftInt << rightInt);
}
