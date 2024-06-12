#include <gtest/gtest.h>
#include "ast/expression/operator/bitwise/bitwise_and_expression.hpp"
#include "ast/expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Test for bitwise AND operation with integers
// TEST(FBitwiseAndExpressionTest, BitwiseAndWithIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(3);
//     FBitwiseAndExpression bitwiseAnd(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseAnd.Evaluate(context), Value(1));
// }

// Test for bitwise AND operation with negative integers
// TEST(FBitwiseAndExpressionTest, BitwiseAndWithNegativeIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
//     FBitwiseAndExpression bitwiseAnd(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseAnd.Evaluate(context), Value(-5 & -3));
// }

// Test for bitwise AND operation with mixed integers
// TEST(FBitwiseAndExpressionTest, BitwiseAndWithMixedIntegers)
// {
//     ExpressionPtr left = std::make_unique<FNumberExpression>(5);
//     ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
//     FBitwiseAndExpression bitwiseAnd(std::move(left), std::move(right));
// 
//     FContext context;
//     EXPECT_EQ(bitwiseAnd.Evaluate(context), Value(5));
// }

// Test for bitwise AND operation with missing operands
TEST(FBitwiseAndExpressionTest, MissingOperands)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FBitwiseAndExpression bitwiseAnd(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(bitwiseAnd.Evaluate(context), std::runtime_error);
}
