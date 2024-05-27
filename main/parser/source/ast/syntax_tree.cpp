#include "ast/syntax_tree.hpp"

FSyntaxTree::FSyntaxTree(ASyntaxNodePtr root)
	// Moves the ownership of the root node into the syntax tree.
	: m_root(std::move(root))
{}

const ASyntaxNode* FSyntaxTree::GetRoot() const
{
	// Retrieves a pointer to the root node.
	return m_root.get();
}
