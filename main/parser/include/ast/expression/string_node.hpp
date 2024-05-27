#pragma once

#include "ast/syntax_node.hpp"

class FStringNode final : public ASyntaxNode
{
	std::string m_value;

public:

	FStringNode(const std::string& value);
	eSyntaxNodeType GetType() const override;

	std::string GetValue() const;
	void SetValue(const std::string& value);

	virtual Value Evaluate(const FContext& context) const override;
};
