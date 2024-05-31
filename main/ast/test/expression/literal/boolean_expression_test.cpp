#include <gtest/gtest.h>
#include "expression/literal/boolean_expression.hpp"

TEST(BooleanExpressionTest, GetValue)
{
    FBooleanExpression trueExpr(true);
    EXPECT_TRUE(trueExpr.GetValue());

    FBooleanExpression falseExpr(false);
    EXPECT_FALSE(falseExpr.GetValue());
}

TEST(BooleanExpressionTest, SetValue)
{
    FBooleanExpression expr(true);
    EXPECT_TRUE(expr.GetValue());

    expr.SetValue(false);
    EXPECT_FALSE(expr.GetValue());

    expr.SetValue(true);
    EXPECT_TRUE(expr.GetValue());
}

TEST(BooleanExpressionTest, Evaluate)
{
    FContext context;

    FBooleanExpression trueExpr(true);
    Value result = trueExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));

    FBooleanExpression falseExpr(false);
    result = falseExpr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}
