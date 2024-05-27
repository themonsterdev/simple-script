#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"
#include "ast/expression/string_operator_node.hpp"

class FStringOperatorNodeTest : public ::testing::Test
{
protected:

    FContext context;

    // Setup method to initialize the test fixture
    void SetUp() override
    {

    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {

    }
};

// Test the creation of a string operator node with valid string concatenation
TEST_F(FStringOperatorNodeTest, ConstructorValidConcatenation)
{
    ExpressionPtr left = std::make_unique<FStringNode>("Hello, ");
    ExpressionPtr right = std::make_unique<FStringNode>("World!");
    FStringOperatorNode stringOp("+", std::move(left), std::move(right));

    ASSERT_NE(stringOp.GetLeft(), nullptr);
    ASSERT_NE(stringOp.GetRight(), nullptr);
}

// Test the creation of a string operator node with valid string repetition
TEST_F(FStringOperatorNodeTest, ConstructorValidRepetition)
{
    ExpressionPtr left = std::make_unique<FNumberNode>(3);
    ExpressionPtr right = std::make_unique<FStringNode>("Repeat");
    FStringOperatorNode stringOp("*", std::move(left), std::move(right));

    ASSERT_NE(stringOp.GetLeft(), nullptr);
    ASSERT_NE(stringOp.GetRight(), nullptr);
}

// Test the evaluation of a string concatenation operation
TEST_F(FStringOperatorNodeTest, EvaluateConcatenation)
{
    ExpressionPtr left = std::make_unique<FStringNode>("Hello, ");
    ExpressionPtr right = std::make_unique<FStringNode>("World!");
    FStringOperatorNode stringOp("+", std::move(left), std::move(right));

    Value result = stringOp.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "Hello, World!");
}

// Test the evaluation of a string repetition operation
TEST_F(FStringOperatorNodeTest, EvaluateRepetition)
{
    ExpressionPtr left = std::make_unique<FNumberNode>(3);
    ExpressionPtr right = std::make_unique<FStringNode>("Repeat");
    FStringOperatorNode stringOp("*", std::move(left), std::move(right));

    Value result = stringOp.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "RepeatRepeatRepeat");
}

// Test the evaluation with an unsupported operator
TEST_F(FStringOperatorNodeTest, EvaluateUnsupportedOperator)
{
    ExpressionPtr left = std::make_unique<FStringNode>("Hello");
    ExpressionPtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("-", std::move(left), std::move(right));

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for concatenation
TEST_F(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForConcatenation)
{
    ExpressionPtr left = std::make_unique<FNumberNode>(42);
    ExpressionPtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("+", std::move(left), std::move(right));

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for repetition
TEST_F(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForRepetition)
{
    ExpressionPtr left = std::make_unique<FStringNode>("Hello");
    ExpressionPtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("*", std::move(left), std::move(right));

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the creation of a string operator node with null children
TEST_F(FStringOperatorNodeTest, ConstructorNullChildren)
{
    ExpressionPtr left = nullptr;
    ExpressionPtr right = nullptr;

    ASSERT_THROW(FStringOperatorNode stringOp("+", std::move(left), std::move(right)), std::runtime_error);
}
