#pragma once

#include "expression/operator/arithmetic/subtract_expression.hpp"
#include <stdexcept>

FSubtractExpression::FSubtractExpression(ExpressionPtr left, ExpressionPtr right)
	: AComputeExpression(std::move(left), std::move(right))
{}

Value FSubtractExpression::Evaluate(const FContext& context) const
{
    if (!m_left || !m_right)
    {
        throw std::runtime_error("Subtract operator must have exactly two operands");
    }

    Value leftValue  = m_left->Evaluate(context);
    Value rightValue = m_right->Evaluate(context);

    // Extract int values from the variants
    int leftInt, rightInt;

    // Check if both operands are integers
    if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
    {
        // Extract integer values from the variants
        leftInt  = std::get<int>(leftValue);
        rightInt = std::get<int>(rightValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid operand types for subtract operation");
    }

	return leftInt - rightInt;
}
