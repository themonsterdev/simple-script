#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

// Statement
#include "ast/statement/print_node.hpp"

class FPrintNodeTest : public ::testing::Test
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

// Tests the creation of a print statement node with a valid expression
TEST_F(FPrintNodeTest, ConstructorValidExpression)
{
    ExpressionPtr expression = std::make_unique<FNumberNode>(42);
    FPrintNode printStatement(std::move(expression));

    ASSERT_NE(printStatement.GetExpression(), nullptr);
}

// Tests the creation of a print statement node with a null expression
TEST_F(FPrintNodeTest, ConstructorNullExpression)
{
    ExpressionPtr expression = nullptr;
    ASSERT_THROW(FPrintNode(std::move(expression)), std::runtime_error);
}

// Tests the evaluation of a print statement node with a number expression
TEST_F(FPrintNodeTest, EvaluateNumberExpression)
{
    ExpressionPtr expression = std::make_unique<FNumberNode>(42);
    FPrintNode printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "42\n");
}

// Tests the evaluation of a print statement node with a string expression
TEST_F(FPrintNodeTest, EvaluateStringExpression)
{
    ExpressionPtr expression = std::make_unique<FStringNode>("Hello, World!");
    FPrintNode printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "Hello, World!\n");
}

// Tests the evaluation of a print statement node with an identifier expression
TEST_F(FPrintNodeTest, EvaluateIdentifierExpression)
{
    ExpressionPtr expression = std::make_unique<FIdentifierNode>("x");
    FPrintNode printStatement(std::move(expression));

    // Set the value of the identifier in the context
    context.SetVariable("x", Value("OpenAI"));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "OpenAI\n");
}
