#include <gtest/gtest.h>
#include "ast/expression/operator/logical/logical_and_expression.hpp"
#include "ast/expression/literal/boolean_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

TEST(FLogicalAndExpressionTest, LogicalAndWithBothTrue)
{
    // Create expressions with true boolean values
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(true);

    // Create a logical AND expression
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    // Create an execution context
    FContext context;

    // Evaluate the expression
    ValuePtr result = logicAnd.Evaluate(context);

    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());

    // Verify that the result is true (true && true)
    EXPECT_EQ(result->ToString(), "true");
}

TEST(FLogicalAndExpressionTest, LogicalAndWithOneFalse)
{
    // Create expressions with one true and one false boolean value
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(false);

    // Create a logical AND expression
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    // Create an execution context
    FContext context;

    // Evaluate the expression
    ValuePtr result = logicAnd.Evaluate(context);

    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());

    // Verify that the result is false (true && false)
    EXPECT_EQ(result->ToString(), "false");
}

TEST(FLogicalAndExpressionTest, LogicalAndWithBothFalse)
{
    // Create expressions with false boolean values
    ExpressionPtr left = std::make_unique<FBooleanExpression>(false);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(false);

    // Create a logical AND expression
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    // Create an execution context
    FContext context;

    // Evaluate the expression
    ValuePtr result = logicAnd.Evaluate(context);

    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());

    // Verify that the result is false (false && false)
    EXPECT_EQ(result->ToString(), "false");
}

TEST(FLogicalAndExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    FLogicalAndExpression logicAnd(std::move(left), nullptr);

    // Create an execution context
    FContext context;

    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(logicAnd.Evaluate(context), std::runtime_error);
}
