/**
 * @file expression_parser.hpp
 * @brief Declaration of the FExpressionParser class.
 */

// Ensure this file is included only once
#pragma once

 // Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

// Forward declaration of FLexer class
class FLexer;

/**
 * @brief Parser class for expressions.
 *
 * This class parses expressions from a lexer and constructs expression objects.
 */
class FExpressionParser final
{
    // Reference to the lexer object
    FLexer& m_lexer;

public:

    /**
     * @brief Construct a new FExpressionParser object.
     *
     * @param lexer Reference to the lexer object.
     */
	explicit FExpressionParser(FLexer& lexer);

    /**
     * @brief Parse an expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseExpression();

    /**
     * @brief Parse a term in an expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseTerm();

    const FLexer& GetLexer() const;

private:

    /**
     * @brief Parse an arithmetic operator expression.
     *
     * @param left The left operand of the expression.
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseArithmeticOperatorExpression(ExpressionPtr left);

    /**
     * @brief Parse a string operator expression.
     *
     * @param left The left operand of the expression.
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseStringOperatorExpression(ExpressionPtr left);

    /**
     * @brief Parse a ternary expression.
     *
     * @param condition The condition of the ternary expression.
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseTernaryExpression(ExpressionPtr condition);

    /**
     * @brief Parse an identifier expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseIdentifier();

    /**
     * @brief Parse a boolean expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseBoolean();

    /**
     * @brief Parse a number expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseNumber();

    /**
     * @brief Parse a string expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseString();

    /**
     * @brief Parse a factor in an expression.
     *
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseFactor();
};
