#include <gtest/gtest.h>
#include "statement/loop/for_loop_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "expression/identifier_expression.hpp"
#include "statement/io/print_statement.hpp"
#include "statement/declaration/var_declaration_statement.hpp"
#include "statement/declaration/assignment_statement.hpp"

// Test the execution of a for loop with a false condition
// TEST(FForLoopStatementTest, ExecuteFalseCondition)
// {
//     // Initialization statement (e.g., var i = 1;)
//     auto initialization = std::make_unique<FVarDeclarationStatement>("i", std::make_unique<FNumberExpression>(1));
// 
//     // Body of the for loop (e.g., Inside loop)
//     auto body = std::make_unique<FPrintStatement>(std::make_unique<FStringExpression>("Inside loop"));
// 
//     // Update statement (e.g., i++)
//     auto update = std::make_unique<FAssignmentStatement>("i", std::make_unique<FBinaryExpression>(
//         std::make_unique<FIdentifierExpression>("i"),
//         BinaryOperator::ADD,
//         std::make_unique<FNumberExpression>(1)
//     ));
// 
//     // Condition of the for loop (e.g., 0 for always false condition)
//     auto condition = std::make_unique<FNumberExpression>(0);
// 
//     // Create the for loop statement
//     FForLoopStatement forLoop(std::move(initialization), std::move(condition), std::move(update), std::move(body));
// 
//     // Create a stringstream to capture stdout
//     std::stringstream buffer;
// 
//     // Redirect cout to our stringstream buffer
//     std::streambuf* old_cout = std::cout.rdbuf(buffer.rdbuf());
// 
//     // Execute the for loop
//     FContext context;
//     forLoop.Execute(context);
// 
//     // Retrieve the captured output
//     std::string actual = buffer.str();
// 
//     // Restore cout's original buffer
//     std::cout.rdbuf(old_cout);
// 
//     // Check if the output is empty since the loop should not execute
//     EXPECT_EQ(actual, "");
// }
