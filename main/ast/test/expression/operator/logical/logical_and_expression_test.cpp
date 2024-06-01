#include <gtest/gtest.h>
#include "expression/operator/logical/logical_and_expression.hpp"
#include "expression/literal/boolean_expression.hpp"

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
    Value result = logicAnd.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is true (true && true)
    EXPECT_TRUE(std::get<bool>(result));
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
    Value result = logicAnd.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (true && false)
    EXPECT_FALSE(std::get<bool>(result));
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
    Value result = logicAnd.Evaluate(context);
    // Verify that the result is a boolean value
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    // Verify that the result is false (false && false)
    EXPECT_FALSE(std::get<bool>(result));
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
