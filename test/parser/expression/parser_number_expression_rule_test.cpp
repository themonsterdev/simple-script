#include <gtest/gtest.h>
#include "lexer/lexer.hpp"

#include "parser/expression/expression_parser.hpp"
#include "ast/expression/literal/number_expression.hpp"

TEST(FParserNumberExpressionTest, ParseInteger)
{
    std::string input("123");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto numberExpression = dynamic_cast<FNumberExpression*>(expression.get());
    ASSERT_NE(numberExpression, nullptr);

    EXPECT_EQ(numberExpression->GetValue(), 123);
}

TEST(FParserNumberExpressionTest, ParseMultipleNumbers)
{
    std::string input("1 2 3");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression1 = parser.ParseExpression();
    ASSERT_NE(expression1, nullptr);
    auto numberExpression1 = dynamic_cast<FNumberExpression*>(expression1.get());
    ASSERT_NE(numberExpression1, nullptr);
    EXPECT_EQ(numberExpression1->GetValue(), 1);

    auto expression2 = parser.ParseExpression();
    ASSERT_NE(expression2, nullptr);
    auto numberExpression2 = dynamic_cast<FNumberExpression*>(expression2.get());
    ASSERT_NE(numberExpression2, nullptr);
    EXPECT_EQ(numberExpression2->GetValue(), 2);

    auto expression3 = parser.ParseExpression();
    ASSERT_NE(expression3, nullptr);
    auto numberExpression3 = dynamic_cast<FNumberExpression*>(expression3.get());
    ASSERT_NE(numberExpression3, nullptr);
    EXPECT_EQ(numberExpression3->GetValue(), 3);
}
