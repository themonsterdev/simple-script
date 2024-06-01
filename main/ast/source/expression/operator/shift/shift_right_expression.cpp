/**
 * @file shift_right_expression.cpp
 * @brief Implementation of the FShiftRightExpression class.
 */

// Include base class header
#include "expression/operator/shift/shift_right_expression.hpp"
#include <stdexcept>

FShiftRightExpression::FShiftRightExpression(ExpressionPtr left, ExpressionPtr right)
    : AComputeExpression(std::move(left), std::move(right))
{}

Value FShiftRightExpression::Evaluate(const FContext& context) const
{
    // Check if left or right expressions are null pointers
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Shift right operator must have both left and right operands");
    }

    // Evaluate left and right expressions
    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Check if both values are integers
    if (!std::holds_alternative<int>(leftValue) || !std::holds_alternative<int>(rightValue))
    {
        throw std::runtime_error("Shift right operator must have integer operands");
    }

    // Right shift the left integer by the number of bits specified by the right integer
    int result = std::get<int>(leftValue) >> std::get<int>(rightValue);

    return Value(result);
}
