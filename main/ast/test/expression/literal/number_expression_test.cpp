#include <gtest/gtest.h>
#include "expression/literal/number_expression.hpp"
#include "number_value.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test for the GetValue method of FNumberExpression
TEST(FNumberExpressionTest, GetValue)
{
    // Create a number expression with the value 42
    FNumberExpression expr(42);
    // Ensure that the GetValue method returns 42
    EXPECT_EQ(expr.GetValue(), 42);
}

// Test for the SetValue method of FNumberExpression
TEST(FNumberExpressionTest, SetValue)
{
    // Create a number expression with the initial value 42
    FNumberExpression expr(42);
    // Ensure that the GetValue method returns 42
    EXPECT_EQ(expr.GetValue(), 42);

    // Set the value of the expression to 10
    expr.SetValue(10);

    // Ensure that the GetValue method now returns 10
    EXPECT_EQ(expr.GetValue(), 10);
}

// Test for the Evaluate method of FNumberExpression
TEST(FNumberExpressionTest, Evaluate)
{
    // Create a context
    FContext context;

    // Create a number expression with the value 42
    FNumberExpression expr(42);

    // Evaluate the expression in the context
    ValuePtr result = expr.Evaluate(context);

    // Ensure that the result is an integer value and it's 42
    ASSERT_TRUE(result->IsNumber());
    EXPECT_EQ(result->ToString(), "42");
}
