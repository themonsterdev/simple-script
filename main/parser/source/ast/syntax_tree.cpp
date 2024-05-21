#include "ast/syntax_tree.hpp"

FSyntaxTree::FSyntaxTree(std::unique_ptr<ASyntaxNode> root)
	: m_root(std::move(root))
{}

const ASyntaxNode* FSyntaxTree::GetRoot() const
{
	return m_root.get();
}
