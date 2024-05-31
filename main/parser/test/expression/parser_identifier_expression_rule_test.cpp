#include <gtest/gtest.h>
#include "lexer.hpp"

#include "expression/expression_parser.hpp"
#include "expression/identifier_expression.hpp"

TEST(FParserIdentifierExpressionTest, ParseSimpleIdentifier)
{
    std::string input("variable");
    FLexer lexer(input);

    const auto& token = lexer.PeekNextToken();
    ASSERT_EQ(token.type, eTokenType::Identifier);
    ASSERT_EQ(token.lexeme, "variable");

    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto identifierExpression = dynamic_cast<FIdentifierExpression*>(expression.get());
    ASSERT_NE(identifierExpression, nullptr);

    EXPECT_EQ(identifierExpression->GetName(), "variable");
}

TEST(FParserIdentifierExpressionTest, ParseIdentifierWithUnderscores)
{
    std::string input("_varName");
    FLexer lexer(input);

    const auto& token = lexer.PeekNextToken();
    ASSERT_EQ(token.type, eTokenType::Identifier);
    ASSERT_EQ(token.lexeme, "_varName");

    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto identifierExpression = dynamic_cast<FIdentifierExpression*>(expression.get());
    ASSERT_NE(identifierExpression, nullptr);

    EXPECT_EQ(identifierExpression->GetName(), "_varName");
}
