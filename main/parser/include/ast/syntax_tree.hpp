#pragma once

#include <memory>

#include "syntax_node.hpp"

class FSyntaxTree final
{
	std::unique_ptr<ASyntaxNode> m_root;

public:

	FSyntaxTree(std::unique_ptr<ASyntaxNode> root);
	const ASyntaxNode* GetRoot() const;
};
