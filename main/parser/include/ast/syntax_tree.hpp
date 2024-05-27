#pragma once

#include "syntax_node.hpp" // Include the header file for the base class ASyntaxNode

/**
 * @brief Represents a syntax tree for a script.
 *
 * This class holds a pointer to the root node of the syntax tree.
 * The root node represents the entire script.
 */
class FSyntaxTree final
{
	// Pointer to the root node of the syntax tree
	ASyntaxNodePtr m_root;

public:

	/**
	 * @brief Constructs a syntax tree with the given root node.
	 * @param root A unique pointer to the root node of the syntax tree.
	 */
	FSyntaxTree(ASyntaxNodePtr root);

	/**
	 * @brief Gets a pointer to the root node of the syntax tree.
	 * @return A constant pointer to the root node.
	 */
	const ASyntaxNode* GetRoot() const;
};
