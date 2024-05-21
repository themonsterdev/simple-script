#pragma once

#include <string>
#include "ast/syntax_node.hpp"

class BinaryOperatorNode final : public ASyntaxNode
{
	std::string m_op;
	ASyntaxNode* m_left;
	ASyntaxNode* m_right;

public:

	BinaryOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right);
	eSyntaxNodeType GetType() const override;

	std::string GetOp() const;
	ASyntaxNode* GetLeft() const;
	ASyntaxNode* GetRight() const;
};
