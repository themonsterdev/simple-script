/**
 * @file comma_expression.cpp
 * @brief Implementation of the comma expression class.
 */

 // Include the header file for the FCommaExpression class
#include "ast/expression/operator/comma_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

FCommaExpression::FCommaExpression(ExpressionList expressions)
    : m_expressions(std::move(expressions))
{}

ValuePtr FCommaExpression::Evaluate(const FContext& context) const
{
    ValuePtr result;

    for (const auto& expression : m_expressions)
    {
        result = expression->Evaluate(context);
    }

    return result;
}

const ExpressionList& FCommaExpression::GetExpressions() const
{
    return m_expressions;
}
