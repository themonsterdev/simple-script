#include <gtest/gtest.h>

#include "context.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"
#include "ast/statement/arithmetic_operator_node.hpp"

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
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(2);
    ASyntaxNodePtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode addition("+", leftNode.release(), rightNode.release());

    // Act
    Value result = addition.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 5);
}

TEST_F(FArithmeticOperatorNodeTest, Subtraction)
{
    // Arrange
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(5);
    ASyntaxNodePtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode subtraction("-", leftNode.release(), rightNode.release());

    // Act
    Value result = subtraction.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 2);
}

TEST_F(FArithmeticOperatorNodeTest, Multiplication)
{
    // Arrange
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(4);
    ASyntaxNodePtr rightNode = std::make_unique<FNumberNode>(5);
    FArithmeticOperatorNode multiplication("*", leftNode.release(), rightNode.release());

    // Act
    Value result = multiplication.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 20);
}

TEST_F(FArithmeticOperatorNodeTest, Division)
{
    // Arrange
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(10);
    ASyntaxNodePtr rightNode = std::make_unique<FNumberNode>(2);
    FArithmeticOperatorNode division("/", leftNode.release(), rightNode.release());

    // Act
    Value result = division.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 5);
}

TEST_F(FArithmeticOperatorNodeTest, Modulo)
{
    // Arrange
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(10);
    ASyntaxNodePtr rightNode = std::make_unique<FNumberNode>(3);
    FArithmeticOperatorNode modulo("%", leftNode.release(), rightNode.release());

    // Act
    Value result = modulo.Evaluate(context);

    // Assert
    EXPECT_EQ(std::get<int>(result), 1);
}

TEST_F(FArithmeticOperatorNodeTest, InvalidOperands)
{
    // Arrange
    ASyntaxNodePtr leftNode = std::make_unique<FNumberNode>(10);
    ASyntaxNodePtr rightNode = std::make_unique<FStringNode>("invalid");
    FArithmeticOperatorNode addition("+", leftNode.release(), rightNode.release());

    // Act & Assert
    EXPECT_THROW({
        addition.Evaluate(context);
    }, std::runtime_error);
}
