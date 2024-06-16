/**
 * @file statement_parser.cpp
 * @brief Implementation of the FStatementParser class.
 */

#include "parser/statement/statement_parser.hpp"	            // Include the statement parser header file
#include "parser/expression/expression_parser.hpp"             // Include the expression parser header file

#include "parser/statement/rule/statement_rule_factory.hpp"    // include the statement  factory header file
#include "parser/exception/syntax_exception.hpp"               // Include the syntax exception header file
#include "lexer/lexer.hpp"		                            // Include the lexer header file
#include <format>

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
    if (!token.IsSameType(eTokenType::End))
    {
        for (const auto& rule : m_rules)
        {
            if (rule->Match(m_lexer))
            {
                return rule->Parse(m_lexer, *this, m_expressionParser);
            }
        }

        // If none of the above conditions are met, throw an error
        std::string message = std::format(
            "Unexpected statement token: '{}'",
            token.ToString()
        );
        throw FSyntaxException(message);
    }

    return nullptr;
}
