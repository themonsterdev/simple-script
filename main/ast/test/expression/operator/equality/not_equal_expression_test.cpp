#include <gtest/gtest.h>
#include "expression/operator/equality/not_equal_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FNotEqualExpressionTest, NotEqualToWithEqualIntegers)
{
    // Create expressions with equal integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create an inequality comparison expression
    FNotEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (3 != 3)
    EXPECT_FALSE(std::get<bool>(result));
}

TEST(FNotEqualExpressionTest, NotEqualToWithDifferentIntegers)
{
    // Create expressions with different integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create an inequality comparison expression
    FNotEqualExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (3 != 5)
    EXPECT_TRUE(std::get<bool>(result));
}

TEST(FNotEqualExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FNotEqualExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
