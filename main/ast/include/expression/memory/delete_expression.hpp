/**
 * @file delete_expression.hpp
 * @brief Declaration of the delete expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

class FDeleteExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    explicit FDeleteExpression(ExpressionPtr expression);

    ValuePtr Evaluate(const FContext& context) const override;

    const ExpressionPtr& GetExpression() const;
};
