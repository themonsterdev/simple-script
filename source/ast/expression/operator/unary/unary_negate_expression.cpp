/**
 * @file unary_negate_expression.cpp
 * @brief Implementation of the unary negate expression class.
 */

// Include the header file for the FUnaryNegateExpression class
#include "ast/expression/operator/unary/unary_negate_expression.hpp"
#include <stdexcept>

// Include declarations for context objects
#include "context/context.hpp"

#include "value/number_value.hpp"

FUnaryNegateExpression::FUnaryNegateExpression(ExpressionPtr expression)
    : m_expression(std::move(expression))
{}

ValuePtr FUnaryNegateExpression::Evaluate(const FContext& context) const
{
    // Evaluate the inner expression
    ValuePtr innerValue = m_expression->Evaluate(context);

    // Check if the value is an integer
    if (!innerValue->IsNumber())
    {
        throw std::runtime_error("Operand of unary negate must be integer");
    }

    // Negate the integer value
    const auto& value = std::dynamic_pointer_cast<FNumberValue>(innerValue);

    return std::make_shared<FNumberValue>(-value->GetValue());
}
