#pragma once

#include "statement/interface/statement_rule.hpp"

/**
 * @brief Represents a rule for parsing interface declaration statements.
 */
class FInterfaceDeclarationRule final : public IStatementRule
{
public:

    /**
     * @brief Checks if the next token in the lexer matches the pattern for a interface declaration.
     * @param lexer The lexer to inspect.
     * @return True if the next token matches the interface declaration pattern, false otherwise.
     */
    bool Match(FLexer& lexer) const override;

    /**
     * @brief Parses a interface declaration statement from the lexer.
     * @param lexer The lexer to parse from.
     * @param statementParser The statement parser to use for nested statements.
     * @param expressionParser The expression parser to use for nested expressions.
     * @return A pointer to the parsed interface declaration statement.
     */
    StatementPtr Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const override;
};
