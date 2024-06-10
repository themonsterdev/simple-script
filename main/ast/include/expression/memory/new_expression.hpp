/**
 * @file new_expression.hpp
 * @brief Declaration of the new expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

class FNewExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    explicit FNewExpression(ExpressionPtr expression);

    ValuePtr Evaluate(const FContext& context) const override;

    const ExpressionPtr& GetExpression() const;
};
