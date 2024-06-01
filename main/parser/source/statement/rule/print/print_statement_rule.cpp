#include "statement/rule/print/print_statement_rule.hpp"
#include "expression/expression_parser.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include "exception/syntax_exception.hpp"
#include "statement/print/print_statement.hpp"

bool FPrintStatementRule::Match(FLexer& lexer) const
{
    const auto& token = lexer.PeekNextToken();
    return token.type == eTokenType::Keyword && token.lexeme == "print";
}

StatementPtr FPrintStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
    // Get the next token, which should be 'print'
    SToken printToken = lexer.GetNextToken();

    // Check if the token is 'print'
    if (printToken.type != eTokenType::Keyword)
    {
        // Throw an error if the token is not 'print'
        throw FSyntaxException("Expected 'print'");
    }

    // Parse the expression to be printed
    auto expression = expressionParser.ParseExpression();

    // Return a unique pointer to the FPrintStatement with the expression
    return std::make_unique<FPrintStatement>(std::move(expression));
}
