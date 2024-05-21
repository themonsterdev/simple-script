#pragma once

#include "ast/syntax_node.hpp"

class PrintStatementNode final : public ASyntaxNode
{
	ASyntaxNode* m_expression;

public:

	PrintStatementNode(ASyntaxNode* expression);
	eSyntaxNodeType GetType() const override;

	ASyntaxNode* GetExpression() const;
};
