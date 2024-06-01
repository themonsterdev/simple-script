#include <gtest/gtest.h>
#include "statement/conditional/conditional_statement.hpp"
#include "statement/print/print_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"

// Test when the condition is true
TEST(FConditionalStatementTest, IfConditionTrue)
{
    auto condition = std::make_unique<FNumberExpression>(1);  // Always true condition
    auto stringExpression = std::make_unique<FStringExpression>("Condition is true");
    auto ifStatement = std::make_unique<FPrintStatement>(std::move(stringExpression));

    FConditionalStatement conditionalStatement(std::move(condition), std::move(ifStatement));

    testing::internal::CaptureStdout();  // Capture standard output
    FContext context;
    conditionalStatement.Execute(context);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Condition is true\n");
}

// Test when the condition is false with an else statement
TEST(FConditionalStatementTest, IfConditionFalseElse)
{
    auto condition = std::make_unique<FNumberExpression>(0);  // Always false condition

    auto stringTrue = std::make_unique<FStringExpression>("Condition is true");
    auto ifStatement = std::make_unique<FPrintStatement>(std::move(stringTrue));

    auto stringFalse = std::make_unique<FStringExpression>("Condition is false");
    auto elseStatement = std::make_unique<FPrintStatement>(std::move(stringFalse));

    FConditionalStatement conditionalStatement(std::move(condition), std::move(ifStatement));
    conditionalStatement.SetElseStatement(std::move(elseStatement));

    testing::internal::CaptureStdout();  // Capture standard output
    FContext context;
    conditionalStatement.Execute(context);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Condition is false\n");
}

// Test when the condition is false with multiple else if statements
TEST(FConditionalStatementTest, IfConditionFalseElseIf)
{
    auto condition = std::make_unique<FNumberExpression>(0);  // Always false condition

    auto stringTrue = std::make_unique<FStringExpression>("Condition is true");
    auto ifStatement = std::make_unique<FPrintStatement>(std::move(stringTrue));

    auto elseIfCondition = std::make_unique<FNumberExpression>(1);  // Always true condition

    auto stringElseIfTrue = std::make_unique<FStringExpression>("Condition is else if true");
    auto elseIfStatement = std::make_unique<FPrintStatement>(std::move(stringElseIfTrue));

    FConditionalStatement conditionalStatement(std::move(condition), std::move(ifStatement));
    conditionalStatement.AddElseIfStatement(std::make_unique<FConditionalStatement>(std::move(elseIfCondition), std::move(elseIfStatement)));

    testing::internal::CaptureStdout();  // Capture standard output
    FContext context;
    conditionalStatement.Execute(context);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Condition is else if true\n");
}

// Test when the condition is false with else if and else statements
TEST(FConditionalStatementTest, IfConditionFalseElseIfElse)
{
    // if
    auto condition = std::make_unique<FNumberExpression>(0);
    auto stringTrue = std::make_unique<FStringExpression>("Condition is true");
    auto ifStatement = std::make_unique<FPrintStatement>(std::move(stringTrue));
    FConditionalStatement conditionalStatement(std::move(condition), std::move(ifStatement));

    // else if
    auto elseIfCondition = std::make_unique<FNumberExpression>(0);
    auto stringElseIfTrue = std::make_unique<FStringExpression>("Condition is else if true");
    auto elseIfStatement = std::make_unique<FPrintStatement>(std::move(stringElseIfTrue));
    conditionalStatement.AddElseIfStatement(
        std::make_unique<FConditionalStatement>(
            std::move(elseIfCondition),
            std::move(elseIfStatement)
        )
    );

    // else
    auto stringFalse = std::make_unique<FStringExpression>("Condition is false");
    auto elseStatement = std::make_unique<FPrintStatement>(std::move(stringFalse));
    conditionalStatement.SetElseStatement(std::move(elseStatement));

    testing::internal::CaptureStdout();
    FContext context;
    conditionalStatement.Execute(context);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Condition is false\n");
}

// Test nested conditional statements
TEST(FConditionalStatementTest, NestedConditionalStatements)
{
    auto condition1 = std::make_unique<FNumberExpression>(1);  // Always true condition
    auto condition2 = std::make_unique<FNumberExpression>(1);  // Always true condition

    auto stringTrue = std::make_unique<FStringExpression>("Nested condition is true");
    auto nestedIfStatement = std::make_unique<FPrintStatement>(std::move(stringTrue));
    auto ifStatement = std::make_unique<FConditionalStatement>(std::move(condition2), std::move(nestedIfStatement));

    FConditionalStatement conditionalStatement(std::move(condition1), std::move(ifStatement));

    testing::internal::CaptureStdout();  // Capture standard output
    FContext context;
    conditionalStatement.Execute(context);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Nested condition is true\n");
}
