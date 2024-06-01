#include <gtest/gtest.h>
#include "expression/literal/boolean_expression.hpp"

// Test for the GetValue method of FBooleanExpression
TEST(FBooleanExpressionTest, GetValue)
{
    // Create a boolean expression with the value true
    FBooleanExpression trueExpr(true);
    // Ensure that the GetValue method returns true
    EXPECT_TRUE(trueExpr.GetValue());

    // Create a boolean expression with the value false
    FBooleanExpression falseExpr(false);
    // Ensure that the GetValue method returns false
    EXPECT_FALSE(falseExpr.GetValue());
}

// Test for the SetValue method of FBooleanExpression
TEST(FBooleanExpressionTest, SetValue)
{
    // Create a boolean expression with the initial value true
    FBooleanExpression expr(true);
    // Ensure that the GetValue method returns true
    EXPECT_TRUE(expr.GetValue());

    // Set the value of the expression to false
    expr.SetValue(false);
    // Ensure that the GetValue method now returns false
    EXPECT_FALSE(expr.GetValue());

    // Set the value of the expression back to true
    expr.SetValue(true);
    // Ensure that the GetValue method now returns true
    EXPECT_TRUE(expr.GetValue());
}

// Test for the Evaluate method of FBooleanExpression
TEST(FBooleanExpressionTest, Evaluate)
{
    // Create a context
    FContext context;

    // Create a boolean expression with the value true
    FBooleanExpression trueExpr(true);
    // Evaluate the expression in the context
    Value result = trueExpr.Evaluate(context);
    // Ensure that the result is a boolean value and it's true
    ASSERT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));

    // Create a boolean expression with the value false
    FBooleanExpression falseExpr(false);
    // Evaluate the expression in the context
    result = falseExpr.Evaluate(context);
    // Ensure that the result is a boolean value and it's false
    ASSERT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}
