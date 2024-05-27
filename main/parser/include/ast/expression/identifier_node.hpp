#pragma once

#include "ast/syntax_node.hpp"

class FIdentifierNode final : public ASyntaxNode
{
	std::string m_name;

public:

	FIdentifierNode(const std::string& name);
	eSyntaxNodeType GetType() const override;

	const std::string& GetName() const;
	void SetName(const std::string& name);

	virtual Value Evaluate(const FContext& context) const override;
};
