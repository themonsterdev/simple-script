#include <gtest/gtest.h>
#include "expression/operator/multiplicative/division_expression.hpp"
#include "expression/literal/number_expression.hpp"

TEST(FDivisionExpressionTest, DivisionWithIntegers)
{
    // Create number expressions for division
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create a division expression
    FDivisionExpression division(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    Value result = division.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(std::holds_alternative<int>(result));
    // Verify that the result is 2 (6 / 3)
    EXPECT_EQ(std::get<int>(result), 2);
}

TEST(FDivisionExpressionTest, DivisionByZero)
{
    // Create a number expression with division by zero
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(0);
    // Create a division expression
    FDivisionExpression division(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(division.Evaluate(context), std::runtime_error);
}

TEST(FDivisionExpressionTest, MissingOperands)
{
    // Create a division expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FDivisionExpression division(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(division.Evaluate(context), std::runtime_error);
}
