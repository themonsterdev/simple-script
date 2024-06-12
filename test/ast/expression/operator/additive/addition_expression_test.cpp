#include <gtest/gtest.h>
#include "ast/expression/operator/additive/addition_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Test for addition with integers
TEST(FAdditionExpressionTest, AdditionWithIntegers)
{
    // Create an addition expression with integers
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Create an empty context for evaluation
    FContext context;

    // Check that the evaluation returns the expected sum
    ValuePtr value = addition.Evaluate(context);
    EXPECT_EQ(value->ToString(), "8");
}

// Test for addition with negative integers
TEST(FAdditionExpressionTest, AdditionWithNegativeIntegers)
{
    // Create an addition expression with negative integers
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Create an empty context for evaluation
    FContext context;

    // Check that the evaluation returns the expected sum
    EXPECT_EQ(addition.Evaluate(context)->ToString(), "-8");
}

// Test for addition with mixed integers
TEST(FAdditionExpressionTest, AdditionWithMixedIntegers)
{
    // Create an addition expression with mixed positive and negative integers
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Create an empty context for evaluation
    FContext context;

    // Check that the evaluation returns the expected sum
    EXPECT_EQ(addition.Evaluate(context)->ToString(), "2");
}

// Test for addition with missing operands
TEST(FAdditionExpressionTest, MissingOperands)
{
    // Create an addition expression with a missing operand
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FAdditionExpression addition(std::move(left), nullptr);

    // Create an empty context for evaluation
    FContext context;

    // Check that the evaluation throws an exception
    EXPECT_THROW(addition.Evaluate(context), std::runtime_error);
}
