#pragma once

#include "ast/syntax_node.hpp"

/**
 * @brief Represents a string operator node in the abstract syntax tree.
 *
 * This class inherits from the ASyntaxNode class and represents a node that
 * performs string operations, such as concatenation or repetition.
 */
class FStringOperatorNode final : public ASyntaxNode
{
    // The string operator.
    std::string m_operator;

public:

    /**
     * @brief Constructs a string operator node with the specified operator, left operand, and right operand.
     * @param op The string operator.
     * @param left The left operand.
     * @param right The right operand.
     */
	FStringOperatorNode(const std::string& op, ASyntaxNode* left, ASyntaxNode* right);

    /**
     * @brief Gets the type of the syntax node.
     * @return The type of the syntax node.
     */
    virtual eSyntaxNodeType GetType() const;

    /**
     * @brief Evaluates the string operation represented by this node.
     * @param context The context in which the evaluation occurs.
     * @return The value resulting from the evaluation of the string operation.
     */
	virtual Value Evaluate(const FContext& context) const override;

    /**
     * @brief Returns the string operator.
     * @return The string operator.
     */
    std::string GetOperator() const;
};
