#include <gtest/gtest.h>
#include "expression/operator/additive/subtraction_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test for subtraction with integers
TEST(FSubtractionExpressionTest, SubtractionWithIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FSubtractionExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(2));
}

// Test for subtraction with negative integers
TEST(FSubtractionExpressionTest, SubtractionWithNegativeIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FSubtractionExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(-2));
}

// Test for subtraction with mixed integers
TEST(FSubtractionExpressionTest, SubtractionWithMixedIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FSubtractionExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(8));
}

// Test for subtraction with missing operands
TEST(FSubtractionExpressionTest, MissingOperands)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FSubtractionExpression subtraction(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(subtraction.Evaluate(context), std::runtime_error);
}
