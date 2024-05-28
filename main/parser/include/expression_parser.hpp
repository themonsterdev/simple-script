/**
 * @file expression_parser.hpp
 * @brief Declaration of the FExpressionParser class.
 */

#pragma once

 // Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

// Forward declaration of FTokenizer class
class FTokenizer;

class FExpressionParser final
{
    FTokenizer& m_tokenizer;

public:

	explicit FExpressionParser(FTokenizer& tokenizer);
    ExpressionPtr ParseExpression();

private:

    ExpressionPtr ParseArithmeticOperatorExpression(ExpressionPtr left);
    ExpressionPtr ParseStringOperatorExpression(ExpressionPtr left);
    ExpressionPtr ParseIdentifier();
    ExpressionPtr ParseNumber();
    ExpressionPtr ParseString();
    ExpressionPtr ParseTerm();
    ExpressionPtr ParseFactor();
};

using ExpressionParserPtr = std::unique_ptr<FExpressionParser>;
