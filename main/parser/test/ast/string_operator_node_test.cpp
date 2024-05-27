#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

// Statement
#include "ast/statement/string_operator_node.hpp"

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
    ASyntaxNodePtr left = std::make_unique<FStringNode>("Hello, ");
    ASyntaxNodePtr right = std::make_unique<FStringNode>("World!");
    FStringOperatorNode stringOp("+", left.release(), right.release());

    ASSERT_NE(stringOp.GetChild(0), nullptr);
    ASSERT_NE(stringOp.GetChild(1), nullptr);
}

// Test the creation of a string operator node with valid string repetition
TEST_F(FStringOperatorNodeTest, ConstructorValidRepetition)
{
    ASyntaxNodePtr left = std::make_unique<FNumberNode>(3);
    ASyntaxNodePtr right = std::make_unique<FStringNode>("Repeat");
    FStringOperatorNode stringOp("*", left.release(), right.release());

    ASSERT_NE(stringOp.GetChild(0), nullptr);
    ASSERT_NE(stringOp.GetChild(1), nullptr);
}

// Test the evaluation of a string concatenation operation
TEST_F(FStringOperatorNodeTest, EvaluateConcatenation)
{
    ASyntaxNodePtr left = std::make_unique<FStringNode>("Hello, ");
    ASyntaxNodePtr right = std::make_unique<FStringNode>("World!");
    FStringOperatorNode stringOp("+", left.release(), right.release());

    Value result = stringOp.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "Hello, World!");
}

// Test the evaluation of a string repetition operation
TEST_F(FStringOperatorNodeTest, EvaluateRepetition)
{
    ASyntaxNodePtr left = std::make_unique<FNumberNode>(3);
    ASyntaxNodePtr right = std::make_unique<FStringNode>("Repeat");
    FStringOperatorNode stringOp("*", left.release(), right.release());

    Value result = stringOp.Evaluate(context);
    ASSERT_TRUE(std::holds_alternative<std::string>(result));
    EXPECT_EQ(std::get<std::string>(result), "RepeatRepeatRepeat");
}

// Test the evaluation with an unsupported operator
TEST_F(FStringOperatorNodeTest, EvaluateUnsupportedOperator)
{
    ASyntaxNodePtr left = std::make_unique<FStringNode>("Hello");
    ASyntaxNodePtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("-", left.release(), right.release());

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for concatenation
TEST_F(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForConcatenation)
{
    ASyntaxNodePtr left = std::make_unique<FNumberNode>(42);
    ASyntaxNodePtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("+", left.release(), right.release());

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the evaluation with invalid operand types for repetition
TEST_F(FStringOperatorNodeTest, EvaluateInvalidOperandTypesForRepetition)
{
    ASyntaxNodePtr left = std::make_unique<FStringNode>("Hello");
    ASyntaxNodePtr right = std::make_unique<FStringNode>("World");
    FStringOperatorNode stringOp("*", left.release(), right.release());

    ASSERT_THROW(stringOp.Evaluate(context), std::runtime_error);
}

// Test the creation of a string operator node with null children
TEST_F(FStringOperatorNodeTest, ConstructorNullChildren)
{
    ASyntaxNodePtr left = nullptr;
    ASyntaxNodePtr right = nullptr;

    ASSERT_THROW(FStringOperatorNode stringOp("+", left.release(), right.release()), std::runtime_error);
}
