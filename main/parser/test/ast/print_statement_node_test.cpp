#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

// Statement
#include "ast/statement/print_statement_node.hpp"

class FPrintStatementNodeTest : public ::testing::Test
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
TEST_F(FPrintStatementNodeTest, ConstructorValidExpression)
{
    ASyntaxNodePtr expression = std::make_unique<FNumberNode>(42);
    FPrintStatementNode printStatement(expression.release());

    ASSERT_NE(printStatement.GetExpression(), nullptr);
}

// Tests the creation of a print statement node with a null expression
TEST_F(FPrintStatementNodeTest, ConstructorNullExpression)
{
    ASyntaxNodePtr expression = nullptr;
    ASSERT_THROW(FPrintStatementNode(expression.release()), std::runtime_error);
}

// Tests the evaluation of a print statement node with a number expression
TEST_F(FPrintStatementNodeTest, EvaluateNumberExpression)
{
    ASyntaxNodePtr expression = std::make_unique<FNumberNode>(42);
    FPrintStatementNode printStatement(expression.release());

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Evaluate(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "42\n");
}

// Tests the evaluation of a print statement node with a string expression
TEST_F(FPrintStatementNodeTest, EvaluateStringExpression)
{
    ASyntaxNodePtr expression = std::make_unique<FStringNode>("Hello, World!");
    FPrintStatementNode printStatement(expression.release());

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Evaluate(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "Hello, World!\n");
}

// Tests the evaluation of a print statement node with an identifier expression
TEST_F(FPrintStatementNodeTest, EvaluateIdentifierExpression)
{
    ASyntaxNodePtr expression = std::make_unique<FIdentifierNode>("x");
    FPrintStatementNode printStatement(expression.release());

    // Set the value of the identifier in the context
    context.SetVariable("x", Value("OpenAI"));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Evaluate the print statement
    EXPECT_NO_THROW(printStatement.Evaluate(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "OpenAI\n");
}
