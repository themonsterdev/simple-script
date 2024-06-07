#include <gtest/gtest.h>
#include "expression/operator/bitwise/bitwise_or_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test for bitwise OR operation with integers
// TEST(FBitwiseOrExpressionTest, BitwiseOrWithIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(3);
//     FBitwiseOrExpression bitwiseOr(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseOr.Evaluate(context), Value(7));
// }

// Test for bitwise OR operation with negative integers
// TEST(FBitwiseOrExpressionTest, BitwiseOrWithNegativeIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
//     FBitwiseOrExpression bitwiseOr(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseOr.Evaluate(context), Value(-1));
// }

// Test for bitwise OR operation with mixed integers
// TEST(FBitwiseOrExpressionTest, BitwiseOrWithMixedIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
//     FBitwiseOrExpression bitwiseOr(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseOr.Evaluate(context), Value(5 | -3));
// }

// Test for bitwise OR operation with missing operands
TEST(FBitwiseOrExpressionTest, MissingOperands)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FBitwiseOrExpression bitwiseOr(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(bitwiseOr.Evaluate(context), std::runtime_error);
}
