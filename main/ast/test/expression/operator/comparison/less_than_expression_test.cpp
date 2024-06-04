#include <gtest/gtest.h>
#include "expression/operator/comparison/less_than_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FLessThanExpressionTest, LessThanWithIntegers)
{
    // Create expressions with integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create a less than comparison expression
    FLessThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (3 < 5)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLessThanExpressionTest, LessThanWithNegativeIntegers)
{
    // Create expressions with negative integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-5);
    // Create a less than comparison expression
    FLessThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (-3 is not less than -5)
    EXPECT_FALSE(std::get<bool>(result));
}

TEST(FLessThanExpressionTest, LessThanWithMixedIntegers)
{
    // Create expressions with mixed integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create a less than comparison expression
    FLessThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (-3 < 5)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLessThanExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FLessThanExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
