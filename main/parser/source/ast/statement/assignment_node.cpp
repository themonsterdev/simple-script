#include "ast/statement/assignment_node.hpp"

FAssignmentNode::FAssignmentNode(const std::string& identifier, ASyntaxNode* expression)
	: m_identifier(identifier)  // Initialize m_identifier with the given identifier
	, m_expression(expression)  // Initialize m_expression with the given expression
{
    if (!m_expression)
    {
        throw std::runtime_error("Assignment expression is null");
    }
}

eSyntaxNodeType FAssignmentNode::GetType() const
{
    // Return the type of this node as AssignmentStatement
	return eSyntaxNodeType::AssignmentStatement;
}

std::string FAssignmentNode::GetIdentifier() const
{
    // Return the identifier (variable name) for this assignment
	return m_identifier;
}

ASyntaxNode* FAssignmentNode::GetExpression() const
{
    // Return the expression associated with this assignment
	return m_expression;
}

Value FAssignmentNode::Evaluate(const FContext& context) const
{
    // Check if the assignment expression is valid
    if (!m_expression)
    {
        throw std::runtime_error("Assignment expression is null");
    }

    // Assign the evaluated expression value to the variable in the context
    context.AssignVariable(m_identifier, m_expression->Evaluate(context));

    // Return an empty Value as assignments do not produce a value
    return {};
}
