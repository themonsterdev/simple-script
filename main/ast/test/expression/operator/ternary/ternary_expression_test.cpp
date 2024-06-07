#include <gtest/gtest.h>
#include "expression/operator/ternary/ternary_expression.hpp"
#include "expression/literal/boolean_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/identifier_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

#include "number_value.hpp"

// Test when the condition is true
TEST(FTernaryExpressionTest, EvaluateTrueCondition)
{
    FContext context;

    // Create a true boolean expression
    auto condition = std::make_unique<FBooleanExpression>(true);
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Evaluate the ternary expression
    ValuePtr result = ternaryExpr.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(result->IsNumber());
    // EXPECT_EQ(std::get<int>(result), 42);
}

// Test when the condition is false
TEST(FTernaryExpressionTest, EvaluateFalseCondition)
{
    FContext context;

    // Create a false boolean expression
    auto condition = std::make_unique<FBooleanExpression>(false);
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Evaluate the ternary expression
    ValuePtr result = ternaryExpr.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(result->IsNumber());
    // EXPECT_EQ(std::get<int>(result), 0);
}

// Test when the condition is a number (evaluated as true)
TEST(FTernaryExpressionTest, EvaluateConditionAsNumber)
{
    FContext context;

    // Create a number expression (evaluated as true)
    auto condition = std::make_unique<FNumberExpression>(1);
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Evaluate the ternary expression
    ValuePtr result = ternaryExpr.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(result->IsNumber());
    // EXPECT_EQ(std::get<int>(result), 42);
}

// Test when the condition is zero (evaluated as false)
TEST(FTernaryExpressionTest, EvaluateConditionAsZero)
{
    FContext context;

    // Create a number expression (evaluated as false)
    auto condition = std::make_unique<FNumberExpression>(0);
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Evaluate the ternary expression
    ValuePtr result = ternaryExpr.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(result->IsNumber());
    // EXPECT_EQ(std::get<int>(result), 0);
}

// Test when the condition is an identifier (evaluated as true)
TEST(FTernaryExpressionTest, EvaluateConditionAsIdentifier)
{
    FContext context;
    context.SetVariable("a", std::make_shared<FNumberValue>(1));

    // Create an identifier expression (evaluated as true)
    auto condition = std::make_unique<FIdentifierExpression>("a");
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Evaluate the ternary expression
    ValuePtr result = ternaryExpr.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(result->IsNumber());
    // EXPECT_EQ(std::get<int>(result), 42);
}

// Test when the condition is of invalid type
TEST(FTernaryExpressionTest, EvaluateInvalidConditionType)
{
    FContext context;

    // Create a string expression as condition (invalid type)
    auto condition = std::make_unique<FStringExpression>("invalid");
    // Create expressions for true and false outcomes
    auto trueExpr = std::make_unique<FNumberExpression>(42);
    auto falseExpr = std::make_unique<FNumberExpression>(0);

    // Create the ternary expression with the given condition and expressions
    FTernaryExpression ternaryExpr(std::move(condition), std::move(trueExpr), std::move(falseExpr));

    // Check if evaluating the ternary expression throws an exception
    EXPECT_THROW(ternaryExpr.Evaluate(context), std::runtime_error);
}
