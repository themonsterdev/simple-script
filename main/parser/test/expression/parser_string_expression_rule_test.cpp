#include <gtest/gtest.h>

#include "lexer.hpp"

#include "expression/expression_parser.hpp"
#include "expression/literal/string_expression.hpp"

TEST(FParserStringExpressionTest, ParseSimpleString)
{
    std::string input("\"hello\"");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto stringExpression = dynamic_cast<FStringExpression*>(expression.get());
    ASSERT_NE(stringExpression, nullptr);

    EXPECT_EQ(stringExpression->GetValue(), "hello");
}

TEST(FParserStringExpressionTest, ParseStringWithSpaces)
{
    std::string input("\"hello world\"");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto stringExpression = dynamic_cast<FStringExpression*>(expression.get());
    ASSERT_NE(stringExpression, nullptr);

    EXPECT_EQ(stringExpression->GetValue(), "hello world");
}

TEST(FParserStringExpressionTest, ParseStringWithEscapes)
{
    std::string input("\"hello \\\"world\\\"\"");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto stringExpression = dynamic_cast<FStringExpression*>(expression.get());
    ASSERT_NE(stringExpression, nullptr);

    EXPECT_EQ(stringExpression->GetValue(), "hello \\\"world\\\"");
}

TEST(FParserStringExpressionTest, ParseMultipleStrings)
{
    std::string input("\"hello\" \"world\"");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression1 = parser.ParseExpression();
    ASSERT_NE(expression1, nullptr);
    auto stringExpression1 = dynamic_cast<FStringExpression*>(expression1.get());
    ASSERT_NE(stringExpression1, nullptr);
    EXPECT_EQ(stringExpression1->GetValue(), "hello");

    auto expression2 = parser.ParseExpression();
    ASSERT_NE(expression2, nullptr);
    auto stringExpression2 = dynamic_cast<FStringExpression*>(expression2.get());
    ASSERT_NE(stringExpression2, nullptr);
    EXPECT_EQ(stringExpression2->GetValue(), "world");
}
