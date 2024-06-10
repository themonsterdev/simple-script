#include <gtest/gtest.h>

#include "lexer.hpp"
#include "parser.hpp"
#include "context.hpp"

// Statement
#include "statement/declaration/assignment_statement.hpp"
#include "statement/declaration/var_declaration_list_statement.hpp"
#include "statement/declaration/var_declaration_statement.hpp"

// Expression
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/operator/multiplicative/multiply_expression.hpp"
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"

#include "number_value.hpp"

// Test fixture for expressions
class FParserTest : public ::testing::Test
{
protected:

    FContext context;

    // SetUp() function will be called before each test
    void SetUp() override
    {
        // Initialize the context with necessary variables for the tests
        context.SetVariable("x", std::make_shared<FNumberValue>(10));
        context.SetVariable("y", std::make_shared<FNumberValue>(5));
    }

    // TearDown() function will be called after each test
    void TearDown() override
    {
        // Clean up after tests if necessary
    }
};

// TEST_F(FParserTest, ExecuteAssignmentStatementTest)
// {
//     ExpressionPtr number = std::make_unique<FNumberExpression>(10);
// 
//     // Create an assignment node
//     StatementPtr assignmentNode = std::make_unique<FAssignmentStatement>("x", std::move(number));
// 
//     // Execute the assignment node
//     assignmentNode->Execute(context);
// 
//     // Ensure the value is correctly initialized to 10
//     Value expectedValue = Value(10);
// 
//     // Verify if the variable has been correctly set in the context
//     ASSERT_EQ(context.GetVariable("x"), expectedValue);
// }

// TEST_F(FParserTest, ExecuteVarDeclarationStatementTest)
// {
//     ExpressionPtr number = std::make_unique<FNumberExpression>(20);
// 
//     // Create a variable declaration statement
//     StatementPtr varDeclarationNode = std::make_unique<FVarDeclarationStatement>("z", std::move(number));
// 
//     // Execute the variable declaration node
//     varDeclarationNode->Execute(context);
// 
//     // Ensure the value is correctly initialized to 20
//     Value expectedValue = Value(20);
// 
//     // Verify if the variable has been correctly declared in the context
//     ASSERT_EQ(context.GetVariable("z"), expectedValue);
// }

// TEST_F(FParserTest, ExecutePrintStatementStatementTest)
// {
//     ExpressionPtr identifier = std::make_unique<FIdentifierExpression>("x");
// 
//     // Create a print statement
//     StatementPtr printNode = std::make_unique<FPrintStatement>(std::move(identifier));
// 
//     // Capture the standard output to verify the print statement
//     testing::internal::CaptureStdout();
// 
//     // Execute the print statement node
//     printNode->Execute(context);
// 
//     // Verify if the standard output contains the value of the variable
//     std::string output = testing::internal::GetCapturedStdout();
//     ASSERT_EQ(output, "10\n");
// }

// TEST_F(FParserTest, ParseTest)
// {
//     std::string input;
//     input += "var n = 1 + 2 * 3\n";
//     input += "print(n)";
// 
//     FLexer lexer(input);
//     FParser parser(lexer);
// 
//     StatementList statements = parser.Parse();
//     ASSERT_EQ(statements.size(), 2);
// 
//     ASSERT_NE(statements.front(), nullptr);
//     const auto varDecl = dynamic_cast<FVarDeclarationStatement*>(statements.front().get());
//     ASSERT_NE(varDecl, nullptr);
// 
//     ASSERT_NE(varDecl->GetExpression(), nullptr);
//     const auto arithNode = dynamic_cast<FAdditionExpression*>(varDecl->GetExpression().get());
//     ASSERT_NE(arithNode, nullptr);
// 
//     const auto leftExpr = dynamic_cast<const FNumberExpression*>(arithNode->GetLeft().get());
//     ASSERT_NE(leftExpr, nullptr);
// 
//     const auto rightExpr = dynamic_cast<const FMultiplicationExpression*>(arithNode->GetRight().get());
//     ASSERT_NE(rightExpr, nullptr);
// 
//     ASSERT_NE(rightExpr->GetLeft(), nullptr);
//     ASSERT_NE(dynamic_cast<FNumberExpression*>(rightExpr->GetRight().get()), nullptr);
// 
//     ASSERT_NE(statements.back(), nullptr);
//     auto printStat = dynamic_cast<FPrintStatement*>(statements.back().get());
//     ASSERT_NE(printStat, nullptr);
//     ASSERT_NE(printStat->GetExpression(), nullptr);
// 
//     const auto idExpr = dynamic_cast<FIdentifierExpression*>(printStat->GetExpression().get());
//     ASSERT_NE(idExpr, nullptr);
// 
//     // Capture the standard output to verify the print statement
//     testing::internal::CaptureStdout();
// 
//     // Execute the statements
//     for (const auto& statement : statements)
//     {
//         statement->Execute(context);
//     }
// 
//     // Verify if the standard output contains the value of the variable
//     std::string output = testing::internal::GetCapturedStdout();
//     ASSERT_EQ(output, "7\n");
// }

// TEST_F(FParserTest, MultipleVarDeclarationTest)
// {
//     std::string input = "var x2, y2 = 0";
// 
//     FLexer lexer(input);
//     FParser parser(lexer);
// 
//     StatementList statements = parser.Parse();
//     ASSERT_EQ(statements.size(), 1);
// 
//     auto varDeclList = dynamic_cast<FVarDeclarationListStatement*>(statements.front().get());
//     ASSERT_NE(varDeclList, nullptr);
//     ASSERT_EQ(varDeclList->GetDeclarations().size(), 2);
// 
//     // Evaluate statements to ensure variables are initialized
//     for (const auto& statement : statements)
//     {
//         statement->Execute(context);
//     }
// 
//     // Verify variables in the context
//     ASSERT_EQ(context.GetVariable("x2"), Value());
//     ASSERT_EQ(context.GetVariable("y2"), Value(0));
// }

TEST_F(FParserTest, SingleTernaryTest)
{
    std::string input = "var x3 = 0\n";
    input += "var y3 = x3 ? false : true";

    FLexer lexer(input);
    FParser parser(lexer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 2);

    ASSERT_NE(statements.front(), nullptr);
    auto varDeclX3 = dynamic_cast<FVarDeclarationStatement*>(statements.front().get());
    ASSERT_NE(varDeclX3, nullptr);

    ASSERT_NE(statements.back(), nullptr);
    auto varDeclY3 = dynamic_cast<FVarDeclarationStatement*>(statements.back().get());
    ASSERT_NE(varDeclY3, nullptr);
    
    // Evaluate statements to ensure variables are initialized
    varDeclX3->Execute(context);
    varDeclY3->Execute(context);

    // Verify variables in the context
    // ASSERT_EQ(context.GetVariable("x3"), Value(0));
    // ASSERT_EQ(context.GetVariable("y3"), Value(true));
}

TEST_F(FParserTest, SingleTernaryFalseTest)
{
    std::string input = "var x3 = 0\n";
    input += "var y3 = x3 ? false : true";

    FLexer lexer(input);
    FParser parser(lexer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 2);

    // for (const auto& statement : statements)
    // {
    //     statement->Execute(context);
    // }
    // 
    // ASSERT_EQ(context.GetVariable("x3"), Value(0));
    // ASSERT_EQ(context.GetVariable("y3"), Value(true));
}

TEST_F(FParserTest, NestedTernaryTest)
{
    std::string a = "true ? \"A\" : \"B\"";
    std::string b = "false ? \"1\" : \"2\"";

    std::string input = "var x3 = 1\n";
    input += "var y3 = x3\n";
    input += "? " + a + "\n";
    input += ": " + b;

    FLexer lexer(input);
    FParser parser(lexer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 2);

    // for (const auto& statement : statements)
    // {
    //     statement->Execute(context);
    // }
    // 
    // ASSERT_EQ(context.GetVariable("x3"), Value(1));
    // ASSERT_EQ(context.GetVariable("y3"), Value("A"));
}
