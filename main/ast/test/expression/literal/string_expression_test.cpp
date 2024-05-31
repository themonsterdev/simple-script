#include <gtest/gtest.h>
#include "expression/literal/string_expression.hpp"

TEST(StringExpressionTest, GetValue)
{
    FStringExpression expr("Hello, world!");
    EXPECT_EQ(expr.GetValue(), "Hello, world!");
}

TEST(StringExpressionTest, SetValue)
{
    FStringExpression expr("Hello, world!");
    EXPECT_EQ(expr.GetValue(), "Hello, world!");

    expr.SetValue("Goodbye, world!");
    EXPECT_EQ(expr.GetValue(), "Goodbye, world!");
}

TEST(StringExpressionTest, Evaluate)
{
    FContext context;
    FStringExpression expr("Hello, world!");
    Value result = expr.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "Hello, world!");
}
