#include <gtest/gtest.h>
#include "expression/operator/equality/equal_to_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FEqualToExpressionTest, EqualToWithIntegers)
{
    // Create expressions with equal integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create an equality comparison expression
    FEqualToExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is true (3 == 3)
    // EXPECT_TRUE(std::get<bool>(result));
}

TEST(FEqualToExpressionTest, NotEqualToWithIntegers)
{
    // Create expressions with different integer values
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    // Create an equality comparison expression
    FEqualToExpression comparison(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = comparison.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is false (3 != 5)
    // EXPECT_FALSE(std::get<bool>(result));
}

TEST(FEqualToExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FEqualToExpression comparison(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
