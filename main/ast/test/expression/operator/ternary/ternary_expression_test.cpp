#include <gtest/gtest.h>
#include <memory>

#include "context.hpp"
#include "expression/operator/ternary/ternary_expression.hpp"
#include "expression/literal/boolean_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/identifier_expression.hpp"

TEST(FTernaryExpressionTest, EvaluateTrueCondition)
{
    FContext context;

    auto condition = std::make_unique<FBooleanExpression>(true);
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    Value result = ternaryExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 42);
}

TEST(FTernaryExpressionTest, EvaluateFalseCondition)
{
    FContext context;

    auto condition = std::make_unique<FBooleanExpression>(false);
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    Value result = ternaryExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 0);
}

TEST(FTernaryExpressionTest, EvaluateConditionAsNumber)
{
    FContext context;

    auto condition = std::make_unique<FNumberExpression>(1);
    auto trueExpr  = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    Value result = ternaryExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 42);
}

TEST(FTernaryExpressionTest, EvaluateConditionAsZero)
{
    FContext context;

    auto condition = std::make_unique<FNumberExpression>(0);
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    Value result = ternaryExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 0);
}

TEST(FTernaryExpressionTest, EvaluateConditionAsIdentifier)
{
    FContext context;
    context.SetVariable("a", 1);

    auto condition = std::make_unique<FIdentifierExpression>("a");
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    Value result = ternaryExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 42);
}

TEST(FTernaryExpressionTest, EvaluateInvalidConditionType)
{
    FContext context;

    auto condition = std::make_unique<FStringExpression>("invalid");
    auto trueExpr  = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    EXPECT_THROW(ternaryExpr.Evaluate(context), std::runtime_error);
}
