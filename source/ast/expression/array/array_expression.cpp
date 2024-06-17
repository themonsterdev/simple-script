/**
 * @file array_expression.cpp
 * @brief Implementation of the array expression class.
 */

// Include the header file for the FArrayExpression class
#include "ast/expression/array/array_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

#include "value/array_value.hpp"

#include <stdexcept>

FArrayExpression::FArrayExpression(ExpressionList expressions)
    : m_expressions(std::move(expressions))
{}

ValuePtr FArrayExpression::Evaluate(const FContext& context) const
{
    ArrayElementVector elements;
    for (const auto& expression : m_expressions)
    {
        const auto& element = expression->Evaluate(context);
        elements.push_back(element);
    }

    return std::make_shared<FArrayValue>(elements);
}

const ExpressionList& FArrayExpression::GetExpressions() const
{
    return m_expressions;
}
