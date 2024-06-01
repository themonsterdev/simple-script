#include <gtest/gtest.h>
#include "statement/loop/do_while_loop_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "statement/print/print_statement.hpp"

// Test the execution of a do-while loop with a false condition
TEST(FDoWhileLoopStatementTest, ExecuteFalseCondition)
{
    // Body of the do-while loop
    auto body = std::make_unique<FPrintStatement>(std::make_unique<FStringExpression>("Inside loop"));
    // Condition of the do-while loop
    auto condition = std::make_unique<FNumberExpression>(0); // Always false condition

    // Create the do-while loop statement
    FDoWhileLoopStatement doWhileLoop(std::move(body), std::move(condition));

    // Create a stringstream to capture stdout
    std::stringstream buffer;

    // Redirect cout to our stringstream buffer
    std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());

    // Execute the do-while loop
    FContext context;
    doWhileLoop.Execute(context);

    // Retrieve the captured output
    std::string actual = buffer.str();

    // Restore cout's original buffer
    std::cout.rdbuf(old_cout);

    // Check if the output is empty since the loop should not execute
    EXPECT_EQ(actual, "Inside loop\n");
}
