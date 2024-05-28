#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "expression/identifier_node.hpp"
#include "expression/number_node.hpp"
#include "expression/string_node.hpp"

// Statement
#include "statement/assignment_statement.hpp"

class FAssignmentStatementTest : public ::testing::Test
{
protected:

    FContext context;

    // Setup method to initialize the test fixture
    void SetUp() override
    {
        // Initialize context with a declared variable
        context.DeclareVariable("y");
    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {
        // No cleanup needed
    }
};

// Test constructor with valid arguments
TEST_F(FAssignmentStatementTest, ConstructorValidArguments)
{
    ExpressionPtr expression = std::make_unique<FIdentifierNode>("x");
    FAssignmentStatement assignment("y", std::move(expression));

    // Verify assignment identifier and expression type
    EXPECT_EQ(assignment.GetIdentifier(), "y");

    EXPECT_NE(assignment.GetExpression(), nullptr);
    EXPECT_NE(dynamic_cast<FIdentifierNode*>(assignment.GetExpression().get()), nullptr);
}

// Test constructor with null expression
TEST_F(FAssignmentStatementTest, ConstructorNullExpression)
{
    ExpressionPtr expression = nullptr;

    // Verify that constructor throws exception for null expression
    ASSERT_THROW(FAssignmentStatement("y", std::move(expression)), std::runtime_error);
}

// Test evaluation with valid context
TEST_F(FAssignmentStatementTest, ExecuteValidContext)
{
    ExpressionPtr expression = std::make_unique<FNumberNode>(42);
    FAssignmentStatement assignment("y", std::move(expression));
    EXPECT_NO_THROW(assignment.Execute(context));

    // Verify that evaluation does not throw and assigns correct value to variable
    EXPECT_EQ(context.GetVariable("y"), Value(42));
}

// Test execution with null expression
// TEST_F(FAssignmentStatementTest, ExecuteNullExpression)
// {
//     ExpressionPtr expression = nullptr;
//     FAssignmentNode assignment("y", std::move(expression));
// 
//     // Verify that evaluation throws exception for null expression
//     ASSERT_THROW(assignment.Execute(context), std::runtime_error);
// }
