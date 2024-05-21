#pragma once

#include <string>
#include "ast/syntax_node.hpp"

class IdentifierNode final : public ASyntaxNode
{
	std::string m_name;

public:

	IdentifierNode(const std::string& name);
	eSyntaxNodeType GetType() const override;

	const std::string& GetName() const;
	void SetName(const std::string& name);
};
