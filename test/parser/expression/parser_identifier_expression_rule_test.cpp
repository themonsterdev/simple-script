#include <gtest/gtest.h>
#include "lexer/lexer.hpp"

#include "parser/expression/expression_parser.hpp"
#include "ast/expression/identifier_expression.hpp"

TEST(FParserIdentifierExpressionTest, ParseSimpleIdentifier)
{
    std::string input("variable");
    FLexer lexer(input);

    const auto& token = lexer.PeekNextToken();
    ASSERT_EQ(token.GetType(), eTokenType::Identifier);
    ASSERT_EQ(token.GetLexeme(), "variable");

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
    ASSERT_EQ(token.GetType(), eTokenType::Identifier);
    ASSERT_EQ(token.GetLexeme(), "_varName");

    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto identifierExpression = dynamic_cast<FIdentifierExpression*>(expression.get());
    ASSERT_NE(identifierExpression, nullptr);

    EXPECT_EQ(identifierExpression->GetName(), "_varName");
}
