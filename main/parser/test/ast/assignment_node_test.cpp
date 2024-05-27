#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

// Statement
#include "ast/statement/arithmetic_operator_node.hpp"
#include "ast/statement/assignment_node.hpp"

class FAssignmentNodeTest : public ::testing::Test
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
TEST_F(FAssignmentNodeTest, ConstructorValidArguments)
{
    ASyntaxNodePtr expression = std::make_unique<FIdentifierNode>("x");
    FAssignmentNode assignment("y", expression.release());

    // Verify assignment identifier and expression type
    EXPECT_EQ(assignment.GetIdentifier(), "y");
    EXPECT_EQ(assignment.GetExpression()->GetType(), eSyntaxNodeType::Identifier);
}

// Test constructor with null expression
TEST_F(FAssignmentNodeTest, ConstructorNullExpression)
{
    ASyntaxNodePtr expression = nullptr;

    // Verify that constructor throws exception for null expression
    ASSERT_THROW(FAssignmentNode("y", expression.release()), std::runtime_error);
}

// Test evaluation with valid context
TEST_F(FAssignmentNodeTest, EvaluateValidContext)
{
    ASyntaxNodePtr expression = std::make_unique<FNumberNode>(42);
    FAssignmentNode assignment("y", expression.release());
    EXPECT_NO_THROW(assignment.Evaluate(context));

    // Verify that evaluation does not throw and assigns correct value to variable
    EXPECT_EQ(context.GetVariable("y"), Value(42));
}

// Test evaluation with null expression
// TEST_F(FAssignmentNodeTest, EvaluateNullExpression)
// {
//     ASyntaxNodePtr expression = nullptr;
//     AssignmentNode assignment("y", expression.release());
// 
//     // Verify that evaluation throws exception for null expression
//     ASSERT_THROW(assignment.Evaluate(context), std::runtime_error);
// }
