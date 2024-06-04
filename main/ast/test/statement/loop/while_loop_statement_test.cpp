#include <gtest/gtest.h>
#include "statement/loop/while_loop_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "statement/io/print_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test the execution of a while loop with a false condition
TEST(FWhileLoopStatementTest, ExecuteFalseCondition)
{
    // Condition of the while loop (always false)
    auto condition = std::make_unique<FNumberExpression>(0);
    // Body of the while loop
    auto body = std::make_unique<FPrintStatement>(std::make_unique<FStringExpression>("Inside loop\n"));

    // Create the while loop statement
    FWhileLoopStatement whileLoop(std::move(condition), std::move(body));

    // Create a stringstream to capture stdout
    std::stringstream buffer;

    // Redirect cout to our stringstream buffer
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());

    // Execute the while loop
    FContext context;
    whileLoop.Execute(context);

    // Retrieve the captured output
    std::string actual = buffer.str();

    // Restore cout's original buffer
    std::cout.rdbuf(old_cout);

    // Check if the output is empty since the loop should not execute
    EXPECT_EQ(actual, "");
}
