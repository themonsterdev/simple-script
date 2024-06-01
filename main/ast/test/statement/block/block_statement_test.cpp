#include <gtest/gtest.h>
#include "statement/block/block_statement.hpp"
#include "statement/print/print_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"

// Test the creation of a block statement with valid statements
TEST(FBlockStatementTest, ConstructorValidStatements)
{
    // Create some print statements
    StatementList statements;
    statements.push_back(std::make_unique<FPrintStatement>(std::make_unique<FNumberExpression>(42)));
    statements.push_back(std::make_unique<FPrintStatement>(std::make_unique<FStringExpression>("Hello, World!")));

    // Create a block statement with the print statements
    FBlockStatement block(std::move(statements));

    // Ensure that the block statement contains the correct number of statements
    EXPECT_EQ(block.GetStatements().size(), 2);
}

// Test the execution of a block statement with valid statements
TEST(FBlockStatementTest, ExecuteValidStatements)
{
    // Create some print statements
    StatementList statements;
    statements.push_back(std::make_unique<FPrintStatement>(std::make_unique<FNumberExpression>(42)));
    statements.push_back(std::make_unique<FPrintStatement>(std::make_unique<FStringExpression>("Hello, World!")));

    // Create a block statement with the print statements
    FBlockStatement block(std::move(statements));

    // Capture standard output
    testing::internal::CaptureStdout();

    // Execute the block statement
    FContext context;
    block.Execute(context);

    // Retrieve the captured output
    std::string output = testing::internal::GetCapturedStdout();

    // Check if the output matches the expected value
    EXPECT_EQ(output, "42\nHello, World!\n");
}

// Test the execution of a block statement with an empty list of statements
TEST(FBlockStatementTest, ExecuteEmptyStatements)
{
    // Create an empty list of statements
    StatementList statements;

    // Create a block statement with the empty list of statements
    FBlockStatement block(std::move(statements));

    // Ensure that executing the block statement with an empty list of statements does not throw any errors
    EXPECT_NO_THROW(block.Execute(FContext()));
}
