#include "gtest/gtest.h"

#include "statement/switch/switch_statement.hpp"

#include "statement/io/print_statement.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Define a fixture for the tests
class SwitchStatementTest : public ::testing::Test {
protected:
    // Initialize a sample context
    FContext context;

    // Create a sample condition expression for the switch statement
    ExpressionPtr condition = std::make_unique<FNumberExpression>(0);

    // Create sample case statements for the switch statement
    // CaseStatementPtr c1 = mockCase(1, 1);
    // CaseStatementPtr c2 = mockCase(2, 2);
    // CaseStatementVector cases = { std::move(c1), std::move(c2) };
    CaseStatementVector cases = {};

    // Create a sample default statement for the switch statement
    ExpressionPtr number = std::make_unique<FNumberExpression>(1);
    StatementPtr print = std::make_unique<FPrintStatement>(std::move(number));
    DefaultStatementPtr defaultCase = std::make_unique<FDefaultStatement>(std::move(print));

    // Create a switch statement
    FSwitchStatement switchStatement{ std::move(condition), std::move(cases), std::move(defaultCase) };

private:

    CaseStatementPtr mockCase(int c, int n)
    {
        ExpressionPtr condition = std::make_unique<FNumberExpression>(c);

        ExpressionPtr number = std::make_unique<FNumberExpression>(n);
        StatementPtr print = std::make_unique<FPrintStatement>(std::move(number));

        return std::make_unique<FCaseStatement>(std::move(condition), std::move(print));
    }
};

// Test case for GetDefaultCase method
TEST_F(SwitchStatementTest, GetDefaultCase) {
    EXPECT_NE(switchStatement.GetDefaultCase(), nullptr);
    // Add additional assertions as needed
}
