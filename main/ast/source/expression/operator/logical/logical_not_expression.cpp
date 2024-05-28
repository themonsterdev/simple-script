#pragma once

#include "expression/operator/logical/logical_not_expression.hpp"
#include <stdexcept>

FLogicalNotExpression::FLogicalNotExpression(ExpressionPtr expression)
	: m_expression(std::move(expression))
{}

Value FLogicalNotExpression::Evaluate(const FContext& context) const
{
    if (!m_expression)
    {
        throw std::runtime_error("Logical not comparison must have exactly one expression");
    }

    Value expressionValue = m_expression->Evaluate(context);

    // Extract int value from the variants
    int expressionInt = 0;

    // Check if both operands are integers
    if (std::holds_alternative<int>(expressionValue))
    {
        // Extract integer value from the variants
        expressionInt = std::get<int>(expressionValue);
    }
    else // Throw exception for invalid operand types
    {
        throw std::runtime_error("Invalid expression types for logical not operation");
    }

	return !expressionInt;
}

const ExpressionPtr& FLogicalNotExpression::GetExpression() const
{
    return m_expression;
}
