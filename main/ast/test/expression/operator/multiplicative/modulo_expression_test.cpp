#include <gtest/gtest.h>
#include "expression/operator/multiplicative/modulo_expression.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

TEST(FModuloExpressionTest, ModuloWithIntegers)
{
    // Create number expressions for modulo operation
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    // Create a modulo expression
    FModuloExpression modulo(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = modulo.Evaluate(context);
    // Verify that the result is an integer value
    EXPECT_TRUE(result->IsNumber());
    // Verify that the result is 0 (6 % 3)
    // EXPECT_EQ(std::get<int>(result), 0);
}

TEST(FModuloExpressionTest, ModuloByZero)
{
    // Create a number expression with modulo by zero
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(0);
    // Create a modulo expression
    FModuloExpression modulo(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(modulo.Evaluate(context), std::runtime_error);
}

TEST(FModuloExpressionTest, MissingOperands)
{
    // Create a modulo expression with one operand missing
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FModuloExpression modulo(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(modulo.Evaluate(context), std::runtime_error);
}
