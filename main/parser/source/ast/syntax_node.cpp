#include "ast/syntax_node.hpp" // Include the header file of the ASyntaxNode class

void ASyntaxNode::AddChild(ASyntaxNode* child)
{
	// Check if the provided child pointer is null
	if (!child)
	{
		// Throw an exception if the child pointer is null
		throw std::runtime_error("Cannot add a null child to ASyntaxNode");
	}

	// Add the provided child pointer to the vector of children
	m_children.push_back(child);
}

const ASyntaxNode* ASyntaxNode::GetChild(const int i) const
{
	return m_children[i];
}

const ASyntaxNodePtrVector& ASyntaxNode::GetChildren() const
{
	// Return a reference to the vector of children
	return m_children;
}

eSyntaxNodeType ASyntaxNode::GetType() const
{
	// Return the type of the syntax node, which is None by default
	return eSyntaxNodeType::None;
}

Value ASyntaxNode::Evaluate(const FContext& context) const
{
	// Iterate through all the children of the node
	for (const auto& child : m_children)
	{
		// Evaluate each child with the given context
		child->Evaluate(context);
	}

	// Return an empty value after evaluation
	return {};
}
