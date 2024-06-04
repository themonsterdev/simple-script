#include "gtest/gtest.h"
#include "statement/switch/case_statement.hpp"

#include "statement/io/print_statement.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Define a fixture for the tests
class CaseStatementTest : public ::testing::Test
{
protected:

    // Initialize a sample context
    FContext context;

    // Create a sample expression for the case statement
    ExpressionPtr condition = std::make_unique<FNumberExpression>(0);

    // Create a sample body statement for the case statement
    ExpressionPtr number = std::make_unique<FNumberExpression>(0);
    StatementPtr body = std::make_unique<FPrintStatement>(std::move(number));

    // Create a case statement
    FCaseStatement caseStatement{ std::move(condition), std::move(body) };
};

// Test case for Execute method
TEST_F(CaseStatementTest, Execute)
{
    // Capture the standard output to verify the print statement
    testing::internal::CaptureStdout();

    // Execute the case statement
    EXPECT_NO_THROW(caseStatement.Execute(context));

    // Verify if the standard output contains the value of the variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "0\n");
}
