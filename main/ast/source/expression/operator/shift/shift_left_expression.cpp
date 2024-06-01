/**
 * @file shift_left_expression.cpp
 * @brief Implementation of the FShiftLeftExpression class.
 */

// Include base class header
#include "expression/operator/shift/shift_left_expression.hpp"
#include <stdexcept>

FShiftLeftExpression::FShiftLeftExpression(ExpressionPtr left, ExpressionPtr right)
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FShiftLeftExpression::Evaluate(const FContext& context) const
{
    // Check if left or right expressions are null pointers
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Shift left operator must have both left and right operands");
    }

    // Evaluate left and right expressions
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Check if both values are integers
    if (!std::holds_alternative<int>(leftValue) || !std::holds_alternative<int>(rightValue))
    {
        throw std::runtime_error("Shift left operator must have integer operands");
    }

    // Left shift the left integer by the number of bits specified by the right integer
    int result = std::get<int>(leftValue) << std::get<int>(rightValue);

    return Value(result);
}
