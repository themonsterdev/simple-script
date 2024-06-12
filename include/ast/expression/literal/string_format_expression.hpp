/**
 * @file string_format_expression.hpp
 * @brief Declaration of the string format expression class.
 */

// Ensure this file is included only once
#pragma once

// Include the expression interface
#include "ast/expression/interface/expression.hpp"

/**
 * @brief Represents a string format expression node in the abstract syntax tree.
 *
 * This class inherits from the IExpression interface and represents a node
 * that holds a string format expression in the AST.
 */
class FStringFormatExpression final : public IExpression
{
    // The string value stored in this node
    std::string m_value;

    // Struct to store literal segments and variable expressions
    struct Segment
    {
        std::string value;
        bool isLiteral;
    };

    // Vector to store segments of the string format expression
    std::vector<Segment> m_segments;

public:
    /**
     * @brief Constructs a string format expression node with the specified string value.
     * @param value The string value.
     */
    FStringFormatExpression(const std::string& value);

    /**
     * @brief Gets the string value stored in this node.
     * @return The string value.
     */
    std::string GetValue() const;

    /**
     * @brief Sets the string value stored in this node.
     * @param value The new string value.
     */
    void SetValue(const std::string& value);

    /**
     * @brief Evaluates the string format expression represented by this node.
     * @param context The context in which the evaluation occurs.
     * @return The evaluated string value.
     */
    ValuePtr Evaluate(const FContext& context) const override;

private:
    /**
     * @brief Parses the string format expression and stores its segments.
     */
    void ParseTemplate();
};
