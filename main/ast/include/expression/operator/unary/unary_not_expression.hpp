/**
 * @file unary_not_expression.hpp
 * @brief Declaration of the unary not expression class.
 */

 // Ensure this file is included only once
#pragma once

// Include the expression interface
#include "expression/interface/expression.hpp"

class FUnaryNotExpression final : public IExpression
{
	ExpressionPtr m_expression;

public:

	FUnaryNotExpression(ExpressionPtr expression);

	virtual Value Evaluate(const FContext& context) const override;
};
