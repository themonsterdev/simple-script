#include "gtest/gtest.h"
#include "statement/function/function_statement.hpp"

#include "statement/block/block_statement.hpp"
#include "statement/io/print_statement.hpp"
#include "expression/identifier_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

#include <list>

// Define a fixture for the tests
class FFunctionStatementTest : public ::testing::Test
{
protected:

    // Initialize a sample context
    FContext context;

    // Sample parameters for the function
    FunctionParameters parameters = { "param1", "param2" };

    std::unique_ptr<FFunctionStatement> functionStatement;

    // Sets up the test fixture.
    virtual void SetUp() override
    {
        ExpressionPtr param1 = std::make_unique<FIdentifierExpression>("param1");
        StatementPtr print1 = std::make_unique<FPrintStatement>(std::move(param1));

        ExpressionPtr param2 = std::make_unique<FIdentifierExpression>("param2");
        StatementPtr print2 = std::make_unique<FPrintStatement>(std::move(param2));

        StatementList statements;
        statements.push_back(std::move(print1));
        statements.push_back(std::move(print2));

        // Create a sample body statement for the function
        StatementPtr body = std::make_unique<FBlockStatement>(std::move(statements));

        // Create a function statement
        functionStatement = std::make_unique<FFunctionStatement>("testFunction", parameters, std::move(body));
    }

    // Tears down the test fixture.
    virtual void TearDown() override
    {

    }
};

// Test case for GetName method
TEST_F(FFunctionStatementTest, GetName)
{
    EXPECT_EQ(functionStatement->GetName(), "testFunction");
}

// Test case for GetParameters method
TEST_F(FFunctionStatementTest, GetParameters)
{
    EXPECT_EQ(functionStatement->GetParameters(), parameters);
}
