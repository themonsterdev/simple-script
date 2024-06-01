#include <gtest/gtest.h>
#include "expression/operator/unary/unary_negate_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Test when negating a positive integer
TEST(FUnaryNegateExpressionTest, NegatePositiveInteger)
{
    // Create a positive integer expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(5);
    // Create the unary negate expression with the positive integer expression
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    // Evaluate the unary negate expression
    Value result = unaryNegate.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), -5);
}

// Test when negating a negative integer
TEST(FUnaryNegateExpressionTest, NegateNegativeInteger)
{
    // Create a negative integer expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(-3);
    // Create the unary negate expression with the negative integer expression
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    // Evaluate the unary negate expression
    Value result = unaryNegate.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 3);
}

// Test when negating zero
TEST(FUnaryNegateExpressionTest, NegateZero)
{
    // Create a zero expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(0);
    // Create the unary negate expression with the zero expression
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    // Evaluate the unary negate expression
    Value result = unaryNegate.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 0);
}
