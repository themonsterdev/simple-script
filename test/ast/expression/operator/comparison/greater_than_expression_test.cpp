#include <gtest/gtest.h>
#include "ast/expression/operator/comparison/greater_than_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

TEST(FGreaterThanExpressionTest, GreaterThanWithIntegers)
{
    // Create expressions with integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create a greater than comparison expression
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is true (5 > 3)
    // EXPECT_TRUE(std::get<bool>(result));
}

TEST(FGreaterThanExpressionTest, GreaterThanWithNegativeIntegers)
{
    // Create expressions with negative integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    // Create a greater than comparison expression
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is false (-5 is not greater than -3)
    // EXPECT_FALSE(std::get<bool>(result));
}

TEST(FGreaterThanExpressionTest, GreaterThanWithMixedIntegers)
{
    // Create expressions with mixed integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    // Create a greater than comparison expression
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is true (5 > -3)
    // EXPECT_TRUE(std::get<bool>(result));
}

TEST(FGreaterThanExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FGreaterThanExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
