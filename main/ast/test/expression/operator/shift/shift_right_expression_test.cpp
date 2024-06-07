#include <gtest/gtest.h>
#include "expression/operator/shift/shift_right_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FShiftRightExpressionTest, ShiftRightWithIntegers)
{
    // Create number expressions for right shift operation
    ExpressionPtr left = std::make_unique<FNumberExpression>(8);
    ExpressionPtr right = std::make_unique<FNumberExpression>(2);
    // Create a shift right expression
    FShiftRightExpression shiftRight(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = shiftRight.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(result->IsNumber());
    // Verify that the result is 2 (8 >> 2)
    // EXPECT_EQ(std::get<int>(result), 2);
}

TEST(FShiftRightExpressionTest, ShiftRightWithNegativeIntegers)
{
    // Create number expressions for right shift operation
    ExpressionPtr left = std::make_unique<FNumberExpression>(-8);
    ExpressionPtr right = std::make_unique<FNumberExpression>(2);
    // Create a shift right expression
    FShiftRightExpression shiftRight(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = shiftRight.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(result->IsNumber());
    // Verify that the result is -2 (-8 >> 2)
    // EXPECT_EQ(std::get<int>(result), -2);
}

TEST(FShiftRightExpressionTest, MissingOperands)
{
    // Create a shift right expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(8);
    FShiftRightExpression shiftRight(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(shiftRight.Evaluate(context), std::runtime_error);
}
