#include "ast/statement/binary_operator_node.hpp"

BinaryOperatorNode::BinaryOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right)
	: m_op(op)
	, m_left(left)
	, m_right(right)
{}

eSyntaxNodeType BinaryOperatorNode::GetType() const
{
	return eSyntaxNodeType::ArithmeticExpression;
}

std::string BinaryOperatorNode::GetOp() const
{
	return m_op;
}

ASyntaxNode* BinaryOperatorNode::GetLeft() const
{
	return m_left;
}

ASyntaxNode* BinaryOperatorNode::GetRight() const
{
	return m_right;
}
