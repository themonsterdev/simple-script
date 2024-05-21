#pragma once

#include "ast/syntax_node.hpp"

class NumberNode final : public ASyntaxNode
{
	int m_value;

public:

	NumberNode(int value);
	eSyntaxNodeType GetType() const override;

	int GetValue() const;
	void SetValue(int value);
};
