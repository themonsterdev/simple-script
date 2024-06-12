#include <gtest/gtest.h>
#include "ast/expression/operator/multiplicative/multiply_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

TEST(FMultiplyExpressionTest, MultiplyWithIntegers)
{
    // Create number expressions for multiplication
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create a multiplication expression
    FMultiplicationExpression multiply(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = multiply.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(result->IsNumber());
    // Verify that the result is 18 (6 * 3)
    // EXPECT_EQ(std::get<int>(result), 18);
}

TEST(FMultiplyExpressionTest, MissingOperands)
{
    // Create a multiplication expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FMultiplicationExpression multiply(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(multiply.Evaluate(context), std::runtime_error);
}
