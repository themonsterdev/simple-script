#include <gtest/gtest.h>
#include "expression/operator/bitwise/bitwise_xor_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Test for bitwise XOR operation with integers
TEST(FBitwiseXorExpressionTest, BitwiseXorWithIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FBitwiseXorExpression bitwiseXor(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(bitwiseXor.Evaluate(context), Value(6));
}

// Test for bitwise XOR operation with negative integers
TEST(FBitwiseXorExpressionTest, BitwiseXorWithNegativeIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FBitwiseXorExpression bitwiseXor(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(bitwiseXor.Evaluate(context), Value(6));
}

// Test for bitwise XOR operation with mixed integers
TEST(FBitwiseXorExpressionTest, BitwiseXorWithMixedIntegers)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FBitwiseXorExpression bitwiseXor(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(bitwiseXor.Evaluate(context), Value(5 ^ -3));
}

// Test for bitwise XOR operation with missing operands
TEST(FBitwiseXorExpressionTest, MissingOperands)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FBitwiseXorExpression bitwiseXor(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(bitwiseXor.Evaluate(context), std::runtime_error);
}
