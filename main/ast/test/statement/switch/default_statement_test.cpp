#include "gtest/gtest.h"
#include "statement/switch/default_statement.hpp"

#include "statement/io/print_statement.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Define a fixture for the tests
class DefaultStatementTest : public ::testing::Test
{
protected:

    // Initialize a sample context
    FContext context;

    // Create a sample body statement for the default statement
    ExpressionPtr number = std::make_unique<FNumberExpression>(0);
    StatementPtr body = std::make_unique<FPrintStatement>(std::move(number));

    // Create a default statement
    FDefaultStatement defaultStatement{ std::move(body) };
};

// Test case for Execute method
TEST_F(DefaultStatementTest, Execute)
{
    // Capture the standard output to verify the print statement
    testing::internal::CaptureStdout();

    // Execute the default statement
    EXPECT_NO_THROW(defaultStatement.Execute(context));

    // Verify if the standard output contains the value of the variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "0\n");
}
