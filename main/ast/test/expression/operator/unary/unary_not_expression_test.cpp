#include <gtest/gtest.h>
#include "expression/operator/unary/unary_not_expression.hpp"
#include "expression/literal/boolean_expression.hpp"

// Test when applying logical NOT to true
TEST(FUnaryNotExpressionTest, NotTrue)
{
    // Create a true boolean expression
    ExpressionPtr expression = std::make_unique<FBooleanExpression>(true);
    // Create the unary NOT expression with the true boolean expression
    FUnaryNotExpression unaryNot(std::move(expression));

    FContext context;
    // Evaluate the unary NOT expression
    Value result = unaryNot.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_EQ(std::get<bool>(result), false);
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
    Value result = unaryNot.Evaluate(context);
    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_EQ(std::get<bool>(result), true);
}
