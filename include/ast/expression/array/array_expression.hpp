/**
 * @file array_expression.hpp
 * @brief Declaration of the array expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FArrayExpression final : public IExpression
{
    ExpressionList m_expressions;

public:

    FArrayExpression(ExpressionList expressions);

    ValuePtr Evaluate(const FContext& context) const override;

    const ExpressionList& GetExpressions() const;
};
