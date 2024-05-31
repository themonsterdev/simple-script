#include <gtest/gtest.h>

#include "lexer.hpp"

#include "expression/expression_parser.hpp"
#include "expression/operator/ternary/ternary_expression.hpp"
#include "expression/operator/comparison/greater_than_expression.hpp"
#include "expression/literal/boolean_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/identifier_expression.hpp"

TEST(FParserTernaryExpressionTest, ParseSimpleTernaryExpression)
{
    std::string input("x > 5 ? true : false");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto ternaryExpression = dynamic_cast<FTernaryExpression*>(expression.get());
    ASSERT_NE(ternaryExpression, nullptr);

    const auto& conditionExpression = ternaryExpression->GetCondition();
    ASSERT_NE(conditionExpression, nullptr);

    auto greaterExpression = dynamic_cast<FGreaterThanExpression*>(conditionExpression.get());
    ASSERT_NE(greaterExpression, nullptr);

    ASSERT_NE(greaterExpression->GetLeft(), nullptr);
    auto idExpression = dynamic_cast<FIdentifierExpression*>(greaterExpression->GetLeft().get());
    ASSERT_NE(idExpression, nullptr);
    ASSERT_EQ(idExpression->GetName(), "x");

    ASSERT_NE(greaterExpression->GetRight(), nullptr);
    auto numberExpression = dynamic_cast<FNumberExpression*>(greaterExpression->GetRight().get());
    ASSERT_NE(numberExpression, nullptr);

    ASSERT_NE(ternaryExpression->GetTrue(), nullptr);
    auto trueExpression = dynamic_cast<FBooleanExpression*>(ternaryExpression->GetTrue().get());
    ASSERT_NE(trueExpression, nullptr);
    EXPECT_TRUE(trueExpression->GetValue());

    ASSERT_NE(ternaryExpression->GetFalse(), nullptr);
    auto falseExpression = dynamic_cast<FBooleanExpression*>(ternaryExpression->GetFalse().get());
    ASSERT_NE(falseExpression, nullptr);
    EXPECT_FALSE(falseExpression->GetValue());
}

TEST(FParserTernaryExpressionTest, ParseTernaryExpressionWithIdentifiers)
{
    std::string input("condition ? value_if_true : value_if_false");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto ternaryExpression = dynamic_cast<FTernaryExpression*>(expression.get());
    ASSERT_NE(ternaryExpression, nullptr);

    const auto& conditionExpression = ternaryExpression->GetCondition();
    ASSERT_NE(conditionExpression, nullptr);

    auto idExpression = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
    ASSERT_NE(idExpression, nullptr);
    ASSERT_EQ(idExpression->GetName(), "condition");

    ASSERT_NE(ternaryExpression->GetTrue(), nullptr);
    auto trueExpression = dynamic_cast<FIdentifierExpression*>(ternaryExpression->GetTrue().get());
    ASSERT_NE(trueExpression, nullptr);
    ASSERT_EQ(trueExpression->GetName(), "value_if_true");

    ASSERT_NE(ternaryExpression->GetFalse(), nullptr);
    auto falseExpression = dynamic_cast<FIdentifierExpression*>(ternaryExpression->GetFalse().get());
    ASSERT_NE(falseExpression, nullptr);
    ASSERT_EQ(falseExpression->GetName(), "value_if_false");
}

TEST(FParserTernaryExpressionTest, ParseTernaryExpressionWithSpaces)
{
    std::string input(" condition ? value_if_true : value_if_false ");
    FLexer lexer(input);
    FExpressionParser parser(lexer);

    auto expression = parser.ParseExpression();
    ASSERT_NE(expression, nullptr);

    auto ternaryExpression = dynamic_cast<FTernaryExpression*>(expression.get());
    ASSERT_NE(ternaryExpression, nullptr);

    const auto& conditionExpression = ternaryExpression->GetCondition();
    ASSERT_NE(conditionExpression, nullptr);

    auto idExpression = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
    ASSERT_NE(idExpression, nullptr);
    ASSERT_EQ(idExpression->GetName(), "condition");

    ASSERT_NE(ternaryExpression->GetTrue(), nullptr);
    auto trueExpression = dynamic_cast<FIdentifierExpression*>(ternaryExpression->GetTrue().get());
    ASSERT_NE(trueExpression, nullptr);
    ASSERT_EQ(trueExpression->GetName(), "value_if_true");

    ASSERT_NE(ternaryExpression->GetFalse(), nullptr);
    auto falseExpression = dynamic_cast<FIdentifierExpression*>(ternaryExpression->GetFalse().get());
    ASSERT_NE(falseExpression, nullptr);
    ASSERT_EQ(falseExpression->GetName(), "value_if_false");
}
