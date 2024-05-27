#include "ast/statement/arithmetic_operator_node.hpp"

FArithmeticOperatorNode::FArithmeticOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right)
    // Initialize the operator
    : m_operator(op)
{
    // Add the left and right children to the node's children vector
    AddChild(left);
    AddChild(right);
}

eSyntaxNodeType FArithmeticOperatorNode::GetType() const
{
    // Return the type of this node as ArithmeticOperator
    return eSyntaxNodeType::ArithmeticOperator;
}

Value FArithmeticOperatorNode::Evaluate(const FContext& context) const
{
    // Check if both left and right child nodes exist
    if (m_children.size() != 2)
    {
        throw std::runtime_error("Arithmetic operator node must have exactly two children");
    }

    const auto leftOperand  = GetChild(0);
    const auto rightOperand = GetChild(1);

    // Check if left and right child nodes exist
    if (leftOperand && rightOperand)
    {
        // Evaluate the child nodes
        Value leftValue  = leftOperand->Evaluate(context);
        Value rightValue = rightOperand->Evaluate(context);

        // Extract int values from the variants
        int leftInt, rightInt;

        // Check if both operands are integers
        if (std::holds_alternative<int>(leftValue) && std::holds_alternative<int>(rightValue))
        {
            // Extract integer values from the variants
            leftInt  = std::get<int>(leftValue);
            rightInt = std::get<int>(rightValue);
        }
        else // Throw exception for invalid operand types
        {
            throw std::runtime_error("Invalid operand types for arithmetic operation");
        }

        // Validate operands before performing operations
        if (m_operator == "/" && rightInt == 0)
        {
            throw std::runtime_error("Division by zero error");
        }
        else if (m_operator == "%" && rightInt == 0)
        {
            throw std::runtime_error("Modulo by zero error");
        }

        // Perform operations based on their precedence
        if (m_operator == "*")
        {
            // Perform multiplication
            return leftInt * rightInt;
        }
        else if (m_operator == "/")
        {
            // Perform division
            return leftInt / rightInt;
        }
        else if (m_operator == "%")
        {
            // Perform modulo operation
            return leftInt % rightInt;
        }
        else if (m_operator == "+")
        {
            // Perform addition
            return leftInt + rightInt;
        }
        else if (m_operator == "-")
        {
            // Perform subtraction
            return leftInt - rightInt;
        }
        // @TODO Add other operations here

        // Throw an exception if the operator is not supported
        throw std::runtime_error("Unsupported arithmetic operator: " + m_operator);
    }
    else // Throw an exception if one of the child nodes is missing
    {
        throw std::runtime_error("Missing child nodes");
    }

    // Default value if child nodes are absent
    return {};
}

std::string FArithmeticOperatorNode::GetOperator() const
{
    // Return the binary operator
    return m_operator;
}
