#pragma once

#include <string>
#include "ast/syntax_node.hpp"

class AssignmentNode final : public ASyntaxNode
{
	std::string m_identifier;
	ASyntaxNode* m_expression;

public:

	AssignmentNode(const std::string& identifier, ASyntaxNode* expression);
	eSyntaxNodeType GetType() const override;

	std::string GetIdentifier() const;
	ASyntaxNode* GetExpression() const;
};
