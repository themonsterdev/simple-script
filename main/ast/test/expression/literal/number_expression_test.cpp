#include <gtest/gtest.h>
#include "expression/literal/number_expression.hpp"

TEST(NumberExpressionTest, GetValue)
{
    FNumberExpression expr(42);
    EXPECT_EQ(expr.GetValue(), 42);
}

TEST(NumberExpressionTest, SetValue)
{
    FNumberExpression expr(42);
    EXPECT_EQ(expr.GetValue(), 42);

    expr.SetValue(10);
    EXPECT_EQ(expr.GetValue(), 10);
}

TEST(NumberExpressionTest, Evaluate)
{
    FContext context;

    FNumberExpression expr(42);
    Value result = expr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 42);
}
