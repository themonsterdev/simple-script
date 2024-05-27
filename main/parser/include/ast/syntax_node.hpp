#pragma once

#include <memory>		// Include necessary declarations for smart pointers
#include <vector>		// Include necessary declarations for vector containers
#include <string>		// Include necessary declarations for string objects
#include <stdexcept>	// Include necessary declarations for exceptions

#include "context.hpp"	// Include declarations for context objects
#include "scope.hpp"	// Include declarations for scope objects

/**
 * @brief Enum representing the types of syntax nodes.
 */
enum class eSyntaxNodeType
{
	None,                   // No specific type.
	VariableDeclaration,    // Variable declaration statement.
	PrintStatement,         // Print statement.
	AssignmentStatement,    // Assignment statement.
	StringOperator,			// String expression.
	BinaryOperator,			// Binary expression.
	ArithmeticOperator,		// Arithmetic expression.
	ComparisonExpression,   // Comparison expression.
	Identifier,             // Identifier expression.
	Number,                 // Number expression.
	String,                 // String expression.
};

// Forward declaration of ASyntaxNode to avoid circular dependency
class ASyntaxNode;

/**
 * @brief Alias for a unique pointer to a syntax node.
 */
using ASyntaxNodePtr = std::unique_ptr<ASyntaxNode>;

/**
 * @brief Alias for std::vector<ASyntaxNode*>.
 */
using ASyntaxNodePtrVector = std::vector<ASyntaxNode*>;

/**
 * @brief Base class for syntax nodes.
 *
 * This class represents a node in the syntax tree of a script.
 */
class ASyntaxNode
{
protected:

	ASyntaxNodePtrVector m_children; // Children nodes of the syntax node.
	std::string m_value;             // Value associated with the syntax node.

public:

	/**
	 * @brief Default destructor.
	 */
	virtual ~ASyntaxNode() = default;

	/**
	 * @brief Adds a child node to the syntax node.
	 * @param child The child node to add.
	 */
	void AddChild(ASyntaxNode* child);

	const ASyntaxNode* GetChild(const int i) const;

	/**
	 * @brief Gets the children nodes of the syntax node.
	 * @return A vector of pointers to the children nodes.
	 */
	const ASyntaxNodePtrVector& GetChildren() const;

	/**
	 * @brief Gets the type of the syntax node.
	 * @return The type of the syntax node.
	 */
	virtual eSyntaxNodeType GetType() const;

	/**
	 * @brief Evaluates the syntax node within the provided context.
	 * @param context The context in which to evaluate the syntax node.
	 * @return The result of the evaluation.
	 */
	virtual Value Evaluate(const FContext& context) const;
};
