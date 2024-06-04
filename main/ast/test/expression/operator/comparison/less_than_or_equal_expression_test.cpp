#include <gtest/gtest.h>
#include "expression/operator/comparison/less_than_or_equal_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FLessThanOrEqualToExpressionTest, LessThanOrEqualToWithIntegers)
{
    // Create expressions with integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create a less than or equal to comparison expression
    FLessThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (3 <= 5)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLessThanOrEqualToExpressionTest, LessThanOrEqualToWithNegativeIntegers)
{
    // Create expressions with negative integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-5);
    // Create a less than or equal to comparison expression
    FLessThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (-3 is not less than or equal to -5)
    EXPECT_FALSE(std::get<bool>(result));
}

TEST(FLessThanOrEqualToExpressionTest, LessThanOrEqualToWithMixedIntegers)
{
    // Create expressions with mixed integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create a less than or equal to comparison expression
    FLessThanOrEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (-3 <= 5)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLessThanOrEqualToExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FLessThanOrEqualExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
