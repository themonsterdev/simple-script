/**
 * @file assignment_expression.hpp
 * @brief Declaration of the assignment expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

class FCommaExpression final : public IExpression
{
    ExpressionList m_expressions;

public:

    FCommaExpression(ExpressionList expressions);

    virtual ValuePtr Evaluate(const FContext& context) const override;
};
