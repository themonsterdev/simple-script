#include "parser/statement/rule/switch/switch_statement_rule.hpp"
#include "ast/statement/switch/switch_statement.hpp"
#include "ast/statement/block/block_statement.hpp"

#include "parser/exception/syntax_exception.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"
#include "parser/parser.hpp"

static StatementPtr ParseCaseStatements(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser)
{
    StatementList statements;

    while (lexer.HasNextToken())
    {
        const auto& token = lexer.PeekNextToken();

        if (token.IsSameTypeAndLexeme(eTokenType::Keyword, "case"))
        {
            // If another 'case' is encountered, stop parsing case statements
            break;
        }

        if (token.IsSameTypeAndLexeme(eTokenType::Keyword, "default"))
        {
            // If another 'default' is encountered, stop parsing case statements
            break;
        }

        if (token.IsSameTypeAndLexeme(eTokenType::Keyword, "end"))
        {
            // If another 'end' is encountered, stop parsing case statements
            break;
        }

        // Parse the next statement in the case
        auto statement = statementParser.ParseStatement();

        if (statement)
        {
            statements.push_back(std::move(statement));
        }
        else
        {
            // If parsing fails, throw an error or handle it accordingly
            break;
        }
    }

    return std::make_unique<FBlockStatement>(std::move(statements));
}

bool FSwitchStatementRule::Match(FLexer& lexer) const
{
    return lexer.TryConsumeToken(eTokenType::Keyword, "switch");
}

StatementPtr FSwitchStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Parse the condition expression to be switched
    auto condition = expressionParser.ParseExpression();

    // The list of case statements associated with this switch statement
    CaseStatementVector cases = {};

    // The default case statement associated with this switch statement
    DefaultStatementPtr defaultCase = nullptr;

    // Parse case statements
    while (lexer.TryConsumeToken(eTokenType::Keyword, "case"))
    {
        // The expression representing the case condition
        auto condition = expressionParser.ParseExpression();

        // Parse the ':' token
        lexer.TryConsumeToken(eTokenType::Delimiter, ":");

        // The body of statements associated with this case
        auto body = ParseCaseStatements(lexer, statementParser, expressionParser);

        // Add this case to the list of cases
        cases.emplace_back(std::make_unique<FCaseStatement>(std::move(condition), std::move(body)));
    }

    // Parse the default case statement, if present
    while (lexer.TryConsumeToken(eTokenType::Keyword, "default"))
    {
        // Parse the ':' token
        lexer.TryConsumeToken(eTokenType::Delimiter, ":");

        // Parse the statements for the default case
        auto body = ParseCaseStatements(lexer, statementParser, expressionParser);

        // Set the default case statement
        defaultCase = std::make_unique<FDefaultStatement>(std::move(body));
    }

    // Parse the end of the switch
    if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
    {
        throw FSyntaxException("Expected 'end' at the end of switch statement");
    }

    // Return a unique pointer to the FPrintStatement with the expression
    return std::make_unique<FSwitchStatement>(
        std::move(condition),
        std::move(cases),
        std::move(defaultCase)
    );
}
