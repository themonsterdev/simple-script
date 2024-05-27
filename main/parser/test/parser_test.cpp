#include <gtest/gtest.h>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "context.hpp"

// Statement
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/print_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/arithmetic_operator_node.hpp"
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

// Test fixture for expressions
class FParserTest : public ::testing::Test
{
protected:

    FContext context;

    // SetUp() function will be called before each test
    void SetUp() override
    {
        // Initialize the context with necessary variables for the tests
        context.SetVariable("x", 10);
        context.SetVariable("y", 5);
    }

    // TearDown() function will be called after each test
    void TearDown() override
    {
        // Clean up after tests if necessary
    }
};

TEST_F(FParserTest, EvaluateAssignmentNodeTest)
{
    ExpressionPtr number = std::make_unique<FNumberNode>(10);

    // Create an assignment node
    StatementPtr assignmentNode = std::make_unique<FAssignmentNode>("x", std::move(number));

    // Execute the assignment node
    assignmentNode->Execute(context);

    // Ensure the value is correctly initialized to 10
    Value expectedValue = Value(10);

    // Verify if the variable has been correctly set in the context
    ASSERT_EQ(context.GetVariable("x"), expectedValue);
}

TEST_F(FParserTest, EvaluateVarDeclarationNodeTest)
{
    ExpressionPtr number = std::make_unique<FNumberNode>(20);

    // Create a variable declaration node
    StatementPtr varDeclarationNode = std::make_unique<FVarDeclarationNode>("z", std::move(number));

    // Execute the variable declaration node
    varDeclarationNode->Execute(context);

    // Ensure the value is correctly initialized to 20
    Value expectedValue = Value(20);

    // Verify if the variable has been correctly declared in the context
    ASSERT_EQ(context.GetVariable("z"), expectedValue);
}

TEST_F(FParserTest, EvaluatePrintStatementNodeTest)
{
    ExpressionPtr identifier = std::make_unique<FIdentifierNode>("x");

    // Create a print statement node
    StatementPtr printNode = std::make_unique<FPrintNode>(std::move(identifier));

    // Capture the standard output to verify the print statement
    testing::internal::CaptureStdout();

    // Execute the print statement node
    printNode->Execute(context);

    // Verify if the standard output contains the value of the variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "10\n");
}

TEST_F(FParserTest, ParseTest)
{
    std::string input;
    input += "var n = 1 + 2 * 3\n";
    input += "print n";

    std::vector<std::string> keywords = { "var", "print" };

    FTokenizer tokenizer(input, keywords);
    FParser parser(tokenizer);

    StatementList statements = parser.Parse();
    ASSERT_EQ(statements.size(), 2);

    ASSERT_NE(statements.front(), nullptr);
    auto varDecl = dynamic_cast<FVarDeclarationNode*>(statements.front().get());
    ASSERT_NE(varDecl, nullptr);
    ASSERT_EQ(varDecl->GetIdentifier(), "n");

    const auto arithNode = dynamic_cast<FArithmeticOperatorNode*>(varDecl->GetExpression().get());
    ASSERT_NE(arithNode, nullptr);
    ASSERT_EQ(arithNode->GetOperator(), "+");

    const auto leftExpr = dynamic_cast<const FNumberNode*>(arithNode->GetLeft().get());
    ASSERT_NE(leftExpr, nullptr);

    const auto rightExpr = dynamic_cast<const FArithmeticOperatorNode*>(arithNode->GetRight().get());
    ASSERT_NE(rightExpr, nullptr);

    ASSERT_NE(rightExpr->GetLeft(), nullptr);
    ASSERT_NE(dynamic_cast<FNumberNode*>(rightExpr->GetRight().get()), nullptr);

    ASSERT_NE(statements.back(), nullptr);
    auto printStat = dynamic_cast<FPrintNode*>(statements.back().get());
    ASSERT_NE(printStat, nullptr);
    ASSERT_NE(printStat->GetExpression(), nullptr);

    const auto idExpr = dynamic_cast<FIdentifierNode*>(printStat->GetExpression().get());
    ASSERT_NE(idExpr, nullptr);

    // Capture the standard output to verify the print statement
    testing::internal::CaptureStdout();

    // Execute the statements
    for (const auto& statement : statements)
    {
        statement->Execute(context);
    }

    // Verify if the standard output contains the value of the variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "7\n");
}
