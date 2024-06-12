/**
 * @file assignment_expression.hpp
 * @brief Declaration of the assignment expression class.
 */

 // Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

class FAssignmentExpression final : public IExpression
{
    ExpressionPtr m_left;
    ExpressionPtr m_right;

public:

    FAssignmentExpression(
        ExpressionPtr left,
        ExpressionPtr right
    );

    ValuePtr Evaluate(const FContext& context) const override;
};
