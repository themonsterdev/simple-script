#pragma once

#include "ast/syntax_node.hpp"

class FNumberNode final : public ASyntaxNode
{
	int m_value;

public:

	FNumberNode(int value);
	eSyntaxNodeType GetType() const override;

	int GetValue() const;
	void SetValue(int value);

	virtual Value Evaluate(const FContext& context) const override;
};
