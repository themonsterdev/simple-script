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

private:

    /**
     * @brief Parse a ternary expression.
     *
     * @param condition The condition of the ternary expression.
     * @return ExpressionPtr A pointer to the parsed expression object.
     */
    ExpressionPtr ParseTernaryExpression();

    ExpressionPtr ParseLogicalOrExpression();
    ExpressionPtr ParseLogicalAndExpression();

    ExpressionPtr ParseBitwiseOrExpression();
    ExpressionPtr ParseBitwiseXorExpression();
    ExpressionPtr ParseBitwiseAndExpression();

    ExpressionPtr ParseEqualityExpression();
    ExpressionPtr ParseComparisonExpression();
    ExpressionPtr ParseShiftExpression();
    ExpressionPtr ParseAdditiveExpression();
    ExpressionPtr ParseMultiplicativeExpression();
    ExpressionPtr ParseUnaryExpression();
    ExpressionPtr ParseAccessExpression();

    ExpressionPtr ParsePrimaryExpression();
};
