#include <gtest/gtest.h>
#include "expression/operator/shift/shift_left_expression.hpp"
#include "expression/literal/number_expression.hpp"

TEST(FShiftLeftExpressionTest, ShiftLeftWithIntegers)
{
    // Create number expressions for left shift operation
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(2);
    // Create a shift left expression
    FShiftLeftExpression shiftLeft(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = shiftLeft.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(std::holds_alternative<int>(result));
    // Verify that the result is 24 (6 << 2)
    EXPECT_EQ(std::get<int>(result), 24);
}

TEST(FShiftLeftExpressionTest, ShiftLeftWithNegativeIntegers)
{
    // Create number expressions for left shift operation
    ExpressionPtr left = std::make_unique<FNumberExpression>(-6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(2);
    // Create a shift left expression
    FShiftLeftExpression shiftLeft(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = shiftLeft.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(std::holds_alternative<int>(result));
    // Verify that the result is -24 (-6 << 2)
    EXPECT_EQ(std::get<int>(result), -24);
}

TEST(FShiftLeftExpressionTest, MissingOperands)
{
    // Create a shift left expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FShiftLeftExpression shiftLeft(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(shiftLeft.Evaluate(context), std::runtime_error);
}
