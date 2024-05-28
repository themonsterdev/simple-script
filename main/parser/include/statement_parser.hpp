/**
 * @file statement_parser.hpp
 * @brief Declaration of the FStatementParser class.
 */

#pragma once

 // Include the interface for language statements
#include "statement/interface/statement.hpp"

// Include the interface for expressions
#include "expression/interface/expression.hpp"

// Include the expression parser header file
#include "expression_parser.hpp"

// Forward declaration of FTokenizer class
class FTokenizer;

class FStatementParser
{
    FTokenizer& m_tokenizer;
    FExpressionParser& m_expressionParser;

public:

    explicit FStatementParser(FTokenizer& m_tokenizer, FExpressionParser& m_expressionParser);
    StatementPtr ParseStatement();

private:

    StatementPtr ParseAssignmentStatement();
    StatementPtr ParseVarDeclarationStatement();
    StatementPtr ParsePrintStatement();
};

using StatementParserPtr = std::unique_ptr<FStatementParser>;
