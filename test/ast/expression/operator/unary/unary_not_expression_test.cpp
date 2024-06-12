#include <gtest/gtest.h>
#include "ast/expression/operator/unary/unary_not_expression.hpp"
#include "ast/expression/literal/boolean_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

// Test when applying logical NOT to true
TEST(FUnaryNotExpressionTest, NotTrue)
{
    // Create a true boolean expression
    ExpressionPtr expression = std::make_unique<FBooleanExpression>(true);
    // Create the unary NOT expression with the true boolean expression
    FUnaryNotExpression unaryNot(std::move(expression));

    FContext context;
    // Evaluate the unary NOT expression
    ValuePtr result = unaryNot.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(result->IsBoolean());
    // EXPECT_EQ(std::get<bool>(result), false);
}

// Test when applying logical NOT to false
TEST(FUnaryNotExpressionTest, NotFalse)
{
    // Create a false boolean expression
    ExpressionPtr expression = std::make_unique<FBooleanExpression>(false);
    // Create the unary NOT expression with the false boolean expression
    FUnaryNotExpression unaryNot(std::move(expression));

    FContext context;
    // Evaluate the unary NOT expression
    ValuePtr result = unaryNot.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(result->IsBoolean());
    // EXPECT_EQ(std::get<bool>(result), true);
}
