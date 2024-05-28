#pragma once

#include "expression/abstract/compute_expression.hpp"

AComputeExpression::AComputeExpression(ExpressionPtr left, ExpressionPtr right)
	: m_left(std::move(left))
	, m_right(std::move(right))
{}

const ExpressionPtr& AComputeExpression::GetLeft() const
{
	return m_left;
}

const ExpressionPtr& AComputeExpression::GetRight() const
{
	return m_right;
}
