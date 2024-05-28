#pragma once

#include "expression/interface/expression.hpp"

class AComputeExpression : public IExpression
{
protected:

	ExpressionPtr m_left;   // The left operand.
	ExpressionPtr m_right;  // The right operand.

public:

	AComputeExpression(ExpressionPtr left, ExpressionPtr right);

    const ExpressionPtr& GetLeft() const;
    const ExpressionPtr& GetRight() const;
};
