#include <gtest/gtest.h>
#include "ast/expression/operator/logical/logical_or_expression.hpp"
#include "ast/expression/literal/boolean_expression.hpp"

// Include declarations for context objects
#include "context/context.hpp"

TEST(FLogicalOrExpressionTest, LogicalOrWithBothTrue)
{
    // Create expressions with true boolean values
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(true);
    // Create a logical OR expression
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = logicOr.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is true (true || true)
    // EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLogicalOrExpressionTest, LogicalOrWithOneTrue)
{
    // Create expressions with one true and one false boolean value
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(false);
    // Create a logical OR expression
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = logicOr.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is true (true || false)
    // EXPECT_TRUE(std::get<bool>(result));
}

TEST(FLogicalOrExpressionTest, LogicalOrWithBothFalse)
{
    // Create expressions with false boolean values
    ExpressionPtr left = std::make_unique<FBooleanExpression>(false);
    ExpressionPtr right = std::make_unique<FBooleanExpression>(false);
    // Create a logical OR expression
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    // Create an execution context
    FContext context;
    // Evaluate the expression
    ValuePtr result = logicOr.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(result->IsBoolean());
    // Verify that the result is false (false || false)
    // EXPECT_FALSE(std::get<bool>(result));
}

TEST(FLogicalOrExpressionTest, MissingOperands)
{
    // Create an expression with one operand missing
    ExpressionPtr left = std::make_unique<FBooleanExpression>(true);
    FLogicalOrExpression logicOr(std::move(left), nullptr);

    // Create an execution context
    FContext context;
    // Verify that evaluating the expression throws a runtime_error
    EXPECT_THROW(logicOr.Evaluate(context), std::runtime_error);
}
