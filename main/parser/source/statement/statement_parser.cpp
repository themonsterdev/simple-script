/**
 * @file statement_parser.cpp
 * @brief Implementation of the FStatementParser class.
 */

#include "statement/statement_parser.hpp"	            // Include the statement parser header file
#include "expression/expression_parser.hpp"             // Include the expression parser header file

#include "statement/rule/statement_rule_factory.hpp"    // include the statement  factory header file
#include "exception/syntax_exception.hpp"               // Include the syntax exception header file
#include "lexer.hpp"		                            // Include the lexer header file

FStatementParser::FStatementParser(FLexer& lexer, FExpressionParser& expressionParser)
    : m_lexer(lexer)
    , m_expressionParser(expressionParser)
    , m_rules(FStatementRuleFactory::CreateRules())
{}

StatementPtr FStatementParser::ParseStatement()
{
    // Peek at the next token without consuming it
    const auto& token = m_lexer.PeekNextToken();

    // Return null if the next token indicates the end of the input
    if (token.type != eTokenType::End)
    {
        for (const auto& rule : m_rules)
        {
            if (rule->Match(m_lexer))
            {
                return rule->Parse(m_lexer, *this, m_expressionParser);
            }
        }

        // Peek at the next token without consuming it
        const auto& token = m_lexer.PeekNextToken();

        // If none of the above conditions are met, throw an error
        throw FSyntaxException("Unexpected token: " + token.lexeme);
    }

    return nullptr;
}
