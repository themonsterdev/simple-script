#pragma once

#include <vector>
#include <string>

enum class eSyntaxNodeType
{
	None,
	VariableDeclaration,
	PrintStatement,
	AssignmentStatement,
	ArithmeticExpression,
	ComparisonExpression,
	Identifier,
	Number,
};

class ASyntaxNode
{
	std::vector<ASyntaxNode*> m_children;
	std::string m_value;

public:

	virtual ~ASyntaxNode() = default;

	void AddChild(ASyntaxNode* child);
	const std::vector<ASyntaxNode*>& GetChildren() const;

	virtual eSyntaxNodeType GetType() const;
};
