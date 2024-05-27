#include <gtest/gtest.h>

#include "context.hpp"
#include "ast/expression/arithmetic_operator_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

class FArithmeticOperatorNodeTest : public ::testing::Test
{
protected:

    FContext context;

    void SetUp() override
    {
        // Initialization code here
    }

    void TearDown() override
    {
        // Cleanup code here
    }
};

TEST_F(FArithmeticOperatorNodeTest, Addition)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(2);
    ExpressionPtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode addition("+", std::move(leftNode), std::move(rightNode));

    // Act
    Value result = addition.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 5);
}

TEST_F(FArithmeticOperatorNodeTest, Subtraction)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(5);
    ExpressionPtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode subtraction("-", std::move(leftNode), std::move(rightNode));

    // Act
    Value result = subtraction.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 2);
}

TEST_F(FArithmeticOperatorNodeTest, Multiplication)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(4);
    ExpressionPtr rightNode = std::make_unique<FNumberNode>(5);
    FArithmeticOperatorNode multiplication("*", std::move(leftNode), std::move(rightNode));

    // Act
    Value result = multiplication.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 20);
}

TEST_F(FArithmeticOperatorNodeTest, Division)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(10);
    ExpressionPtr rightNode = std::make_unique<FNumberNode>(2);
    FArithmeticOperatorNode division("/", std::move(leftNode), std::move(rightNode));

    // Act
    Value result = division.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 5);
}

TEST_F(FArithmeticOperatorNodeTest, Modulo)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(10);
    ExpressionPtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode modulo("%", std::move(leftNode), std::move(rightNode));

    // Act
    Value result = modulo.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 1);
}

TEST_F(FArithmeticOperatorNodeTest, InvalidOperands)
{
    // Arrange
    ExpressionPtr leftNode = std::make_unique<FNumberNode>(10);
    ExpressionPtr rightNode = std::make_unique<FStringNode>("invalid");
    FArithmeticOperatorNode addition("+", std::move(leftNode), std::move(rightNode));

    // Act & Assert
    EXPECT_THROW({
        addition.Evaluate(context);
    }, std::runtime_error);
}
