#include <gtest/gtest.h>
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "statement/io/print_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

// Tests the creation of a print statement with a valid expression
TEST(FPrintStatementTest, ConstructorValidExpression)
{
    // Create a number expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);

    // Create a print statement with the expression
    FPrintStatement printStatement(std::move(expression));

    // Ensure that the expression is not null
    ASSERT_NE(printStatement.GetExpression(), nullptr);
}

// Tests the creation of a print statement with a null expression
TEST(FPrintStatementTest, ConstructorNullExpression)
{
    // Create a null expression
    ExpressionPtr expression = nullptr;

    // Ensure that constructing a print statement with a null expression throws an error
    ASSERT_THROW(FPrintStatement(std::move(expression)), std::runtime_error);
}

// Tests the execution of a print statement with a number expression
TEST(FPrintStatementTest, ExecuteNumberExpression)
{
    // Create a number expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);

    // Create a print statement with the number expression
    FPrintStatement printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Create a context
    FContext context;

    // Execute the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "42\n");
}

// Tests the execution of a print statement with a string expression
TEST(FPrintStatementTest, ExecuteeStringExpression)
{
    // Create a string expression
    ExpressionPtr expression = std::make_unique<FStringExpression>("Hello, World!");

    // Create a print statement with the string expression
    FPrintStatement printStatement(std::move(expression));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Create a context
    FContext context;

    // Execute the print statement
    EXPECT_NO_THROW(printStatement.Execute(context));

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "Hello, World!\n");
}

// Tests the execution of a print statement with an identifier expression
TEST(FPrintStatementTest, ExecuteIdentifierExpression)
{
    // Create an identifier expression
    ExpressionPtr expression = std::make_unique<FIdentifierExpression>("x");

    // Create a print statement with the identifier expression
    FPrintStatement printStatement(std::move(expression));

    // Create a context
    FContext context;

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
