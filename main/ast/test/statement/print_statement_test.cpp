#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"

// Statement
#include "statement/print_statement.hpp"

class FPrintStatementTest : public ::testing::Test
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

// Tests the creation of a print statement with a valid expression
TEST_F(FPrintStatementTest, ConstructorValidExpression)
{
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);
    FPrintStatement printStatement(std::move(expression));

    ASSERT_NE(printStatement.GetExpression(), nullptr);
}

// Tests the creation of a print statement with a null expression
TEST_F(FPrintStatementTest, ConstructorNullExpression)
{
    ExpressionPtr expression = nullptr;
    ASSERT_THROW(FPrintStatement(std::move(expression)), std::runtime_error);
}

// Tests the execution of a print statement with a number expression
TEST_F(FPrintStatementTest, ExecuteNumberExpression)
{
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);
    FPrintStatement printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Execute the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "42\n");
}

// Tests the execution of a print statement with a string expression
TEST_F(FPrintStatementTest, ExecuteeStringExpression)
{
    ExpressionPtr expression = std::make_unique<FStringExpression>("Hello, World!");
    FPrintStatement printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Execute the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "Hello, World!\n");
}

// Tests the execution of a print statement with an identifier expression
TEST_F(FPrintStatementTest, ExecuteIdentifierExpression)
{
    ExpressionPtr expression = std::make_unique<FIdentifierExpression>("x");
    FPrintStatement printStatement(std::move(expression));

    // Set the value of the identifier in the context
    context.SetVariable("x", Value("OpenAI"));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Execute the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "OpenAI\n");
}
