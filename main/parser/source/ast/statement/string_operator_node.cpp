#include "ast/statement/string_operator_node.hpp"

FStringOperatorNode::FStringOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right)
    // Call the base class constructor to initialize the binary operator node
    : m_operator(op)
{
    // Add the left and right children to the node's children vector
    AddChild(left);
    AddChild(right);
}

eSyntaxNodeType FStringOperatorNode::GetType() const
{
    // Return the type of this node as StringOperator
    return eSyntaxNodeType::StringOperator;
}

Value FStringOperatorNode::Evaluate(const FContext& context) const
{
    // Check if both left and right child nodes exist
    if (m_children.size() != 2)
    {
        throw std::runtime_error("String operator node must have exactly two children");
    }

    const auto leftOperand  = GetChild(0);
    const auto rightOperand = GetChild(1);

    // Check if both left and right child nodes exist
    if (leftOperand && rightOperand)
    {
        // Evaluate the child nodes
        Value leftValue  = leftOperand->Evaluate(context);
        Value rightValue = rightOperand->Evaluate(context);

        // Extract string values from the variants
        std::string leftString;
        std::string rightString;

        // Check if the right operand is a string
        if (std::holds_alternative<std::string>(rightValue))
        {
            rightString = std::get<std::string>(rightValue);
        }
        else // Throw an exception if the right operand is not a string
        {
            throw std::runtime_error("Invalid operand type for string operation");
        }

        // Perform the binary operation based on the operator
        if (m_operator == "+")
        {
            // Concatenate the strings
            if (std::holds_alternative<std::string>(leftValue))
            {
                leftString = std::get<std::string>(leftValue);
                return leftString + rightString;
            }
            else // Throw an exception if the left operand is not a string
            {
                throw std::runtime_error("Invalid operand types for string concatenation");
            }
        }
        else if (m_operator == "*")
        {
            // Perform string repetition
            if (std::holds_alternative<int>(leftValue))
            {
                int repeatCount = std::get<int>(leftValue);
                std::string repeatedString;

                // Repeat the right string 'repeatCount' times
                for (int i = 0; i < repeatCount; ++i)
                {
                    repeatedString += rightString;
                }
                return repeatedString;
            }
            else // Throw an exception if the left operand is not an integer
            {
                throw std::runtime_error("Invalid operand types for string repetition");
            }
        }
        // Add other string operations here

        // Throw an exception if the operator is not supported
        throw std::runtime_error("Unsupported string operator: " + m_operator);
    }
    else // Throw an exception if one of the child nodes is missing
    {
        throw std::runtime_error("Missing child nodes");
    }

    // Default value if child nodes are absent
    return {};
}

std::string FStringOperatorNode::GetOperator() const
{
    // Return the string operator
    return m_operator;
}
