/**
 * @file assignment_expression.hpp
 * @brief Declaration of the assignment expression class.
 */

 // Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FThrowExpression final : public IExpression
{
    ExpressionPtr m_expression;

public:

    FThrowExpression(ExpressionPtr expression);

    ValuePtr Evaluate(const FContext& context) const override;
};
