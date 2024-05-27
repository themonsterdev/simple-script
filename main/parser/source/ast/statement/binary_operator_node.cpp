#include "ast/statement/binary_operator_node.hpp"

ABinaryOperatorNode::ABinaryOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right)
	: m_operator(op)
{
	if (!left || !right)
	{
		throw std::invalid_argument("Operands cannot be null");
	}

	AddChild(left);
	AddChild(right);
}

eSyntaxNodeType ABinaryOperatorNode::GetType() const
{
	// Return the type of this node as BinaryOperator
	return eSyntaxNodeType::BinaryOperator;
}

std::string ABinaryOperatorNode::GetOperator() const
{
	// Return the binary operator
	return m_operator;
}

const ASyntaxNode* ABinaryOperatorNode::GetLeft() const
{
	// Return the left operand
	return m_children.size() > 0 ? m_children[0] : nullptr;
}

const ASyntaxNode* ABinaryOperatorNode::GetRight() const
{
	// Return the right operand
	return m_children.size() > 1 ? m_children[1] : nullptr;
}
