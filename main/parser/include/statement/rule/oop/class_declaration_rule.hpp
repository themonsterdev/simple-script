#pragma once

#include "statement/interface/statement_rule.hpp"

/**
 * @brief Represents a rule for parsing class declaration statements.
 */
class FClassDeclarationRule final : public IStatementRule
{
public:

    /**
     * @brief Checks if the next token in the lexer matches the pattern for a class declaration.
     * @param lexer The lexer to inspect.
     * @return True if the next token matches the class declaration pattern, false otherwise.
     */
    bool Match(FLexer& lexer) const override;

    /**
     * @brief Parses a class declaration statement from the lexer.
     * @param lexer The lexer to parse from.
     * @param statementParser The statement parser to use for nested statements.
     * @param expressionParser The expression parser to use for nested expressions.
     * @return A pointer to the parsed class declaration statement.
     */
    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
