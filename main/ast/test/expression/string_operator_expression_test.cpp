#include <gtest/gtest.h>
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/string_operator_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test the creation of a string operator node with valid string concatenation
TEST(FStringOperatorNodeTest, ConstructorValidConcatenation)
{
    ExpressionPtr left = std::make_unique<FStringExpression>("Hello, ");
    ExpressionPtr right = std::make_unique<FStringExpression>("World!");
    FStringOperatorExpression stringOp("+", std::move(left), std::move(right));

    // Check if both children are not null after construction
    ASSERT_NE(stringOp.GetLeft(), nullptr);
    ASSERT_NE(stringOp.GetRight(), nullptr);
}

// Test the creation of a string operator node with valid string repetition
TEST(FStringOperatorNodeTest, ConstructorValidRepetition)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FStringExpression>("Repeat");
    FStringOperatorExpression stringOp("*", std::move(left), std::move(right));

    // Check if both children are not null after construction
    ASSERT_NE(stringOp.GetLeft(), nullptr);
    ASSERT_NE(stringOp.GetRight(), nullptr);
}

// Test the evaluation of a string concatenation operation
TEST(FStringOperatorNodeTest, EvaluateConcatenation)
{
    ExpressionPtr left = std::make_unique<FStringExpression>("Hello, ");
    ExpressionPtr right = std::make_unique<FStringExpression>("World!");
    FStringOperatorExpression stringOp("+", std::move(left), std::move(right));

    FContext context;
    // Evaluate the string operator
    Value result = stringOp.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "Hello, World!");
}

// Test the evaluation of a string repetition operation
TEST(FStringOperatorNodeTest, EvaluateRepetition)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FStringExpression>("Repeat");
    FStringOperatorExpression stringOp("*", std::move(left), std::move(right));

    FContext context;
    // Evaluate the string operator
    Value result = stringOp.Evaluate(context);
    // Check if the result is as expected
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "RepeatRepeatRepeat");
}

// Test the evaluation with an unsupported operator
TEST(FStringOperatorNodeTest, EvaluateUnsupportedOperator)
{
    ExpressionPtr left = std::make_unique<FStringExpression>("Hello");
    ExpressionPtr right = std::make_unique<FStringExpression>("World");
    FStringOperatorExpression stringOp("-", std::move(left), std::move(right));

    FContext context;
    // Evaluate the string operator, which should throw a runtime_error
    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for concatenation
TEST(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForConcatenation)
{
    ExpressionPtr left = std::make_unique<FNumberExpression>(42);
    ExpressionPtr right = std::make_unique<FStringExpression>("World");
    FStringOperatorExpression stringOp("+", std::move(left), std::move(right));

    FContext context;
    // Evaluate the string operator, which should throw a runtime_error
    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for repetition
TEST(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForRepetition)
{
    ExpressionPtr left = std::make_unique<FStringExpression>("Hello");
    ExpressionPtr right = std::make_unique<FStringExpression>("World");
    FStringOperatorExpression stringOp("*", std::move(left), std::move(right));

    FContext context;
    // Evaluate the string operator, which should throw a runtime_error
    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the creation of a string operator node with null children
TEST(FStringOperatorNodeTest, ConstructorNullChildren)
{
    ExpressionPtr left = nullptr;
    ExpressionPtr right = nullptr;

    // Attempt to create a string operator with null children, which should throw a runtime_error
    ASSERT_THROW(FStringOperatorExpression stringOp("+", std::move(left), std::move(right)), std::runtime_error);
}
