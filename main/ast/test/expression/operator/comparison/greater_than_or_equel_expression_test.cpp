#include <gtest/gtest.h>
#include "expression/operator/comparison/greater_than_or_equal_expression.hpp"
#include "expression/literal/number_expression.hpp"

TEST(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithIntegers)
{
    // Create expressions with integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create a greater than or equal comparison expression
    FGreaterThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (5 >= 3)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithNegativeIntegers)
{
    // Create expressions with negative integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    // Create a greater than or equal comparison expression
    FGreaterThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (-5 is not greater than or equal to -3)
    EXPECT_FALSE(std::get<bool>(result));
}

TEST(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithMixedIntegers)
{
    // Create expressions with mixed integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    // Create a greater than or equal comparison expression
    FGreaterThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (5 >= -3)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(GreaterThanOrEqualToExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FGreaterThanOrEqualExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
