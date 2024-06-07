#include <gtest/gtest.h>
#include "expression/literal/string_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test for the GetValue method of FStringExpression
TEST(FStringExpressionTest, GetValue)
{
    // Create a string expression with the value "Hello, world!"
    FStringExpression expr("Hello, world!");
    // Ensure that the GetValue method returns "Hello, world!"
    EXPECT_EQ(expr.GetValue(), "Hello, world!");
}

// Test for the SetValue method of FStringExpression
TEST(FStringExpressionTest, SetValue)
{
    // Create a string expression with the initial value "Hello, world!"
    FStringExpression expr("Hello, world!");
    // Ensure that the GetValue method returns "Hello, world!"
    EXPECT_EQ(expr.GetValue(), "Hello, world!");

    // Set the value of the expression to "Goodbye, world!"
    expr.SetValue("Goodbye, world!");
    // Ensure that the GetValue method now returns "Goodbye, world!"
    EXPECT_EQ(expr.GetValue(), "Goodbye, world!");
}

// Test for the Evaluate method of FStringExpression
TEST(FStringExpressionTest, Evaluate)
{
    // Create a context
    FContext context;
    // Create a string expression with the value "Hello, world!"
    FStringExpression expr("Hello, world!");
    // Evaluate the expression in the context
    ValuePtr result = expr.Evaluate(context);
    // Ensure that the result is a string value and it's "Hello, world!"
    ASSERT_TRUE(result->IsString());
    EXPECT_EQ(result->ToString(), "Hello, world!");
}
