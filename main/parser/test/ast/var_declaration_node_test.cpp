#include <gtest/gtest.h>

#include "context.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"
#include "ast/expression/string_node.hpp"

// Statement
#include "ast/statement/var_declaration_node.hpp"

class FVarDeclarationNodeTest : public ::testing::Test
{
protected:

    std::string identifier;
    ASyntaxNodePtr expression = nullptr;
    FContext context;

    // Setup method to initialize the test fixture
    void SetUp() override
    {
        // Initialize test data
        identifier = "x";
        expression = std::make_unique<FNumberNode>(42);
    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {

    }
};

// Test constructor with valid input
TEST_F(FVarDeclarationNodeTest, ConstructorValidInput)
{
    // Construct VarDeclarationNode
    ASSERT_NO_THROW(FVarDeclarationNode(identifier, expression.release()));
}

// Test constructor with empty identifier
TEST_F(FVarDeclarationNodeTest, ConstructorEmptyIdentifier)
{
    // Construct VarDeclarationNode with empty identifier
    ASSERT_THROW(FVarDeclarationNode("", expression.release()), std::invalid_argument);
}

// Test GetType method
TEST_F(FVarDeclarationNodeTest, GetType)
{
    FVarDeclarationNode varDeclaration(identifier, expression.release());

    // Check the type of the node
    ASSERT_EQ(varDeclaration.GetType(), eSyntaxNodeType::VariableDeclaration);
}

// Test GetIdentifier method
TEST_F(FVarDeclarationNodeTest, GetIdentifier)
{
    FVarDeclarationNode varDeclaration(identifier, expression.release());

    // Check the identifier of the node
    ASSERT_EQ(varDeclaration.GetIdentifier(), identifier);
}

// Test GetExpression method
TEST_F(FVarDeclarationNodeTest, GetExpression)
{
    FVarDeclarationNode varDeclaration(identifier, expression.get());

    // Check the expression of the node
    ASSERT_EQ(varDeclaration.GetExpression(), expression.release());
}

// Test Evaluate method with expression
TEST_F(FVarDeclarationNodeTest, EvaluateWithExpression)
{
    FVarDeclarationNode varDeclaration(identifier, expression.release());

    // Evaluate the node
    ASSERT_NO_THROW(varDeclaration.Evaluate(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    ASyntaxNode* expr = varDeclaration.GetExpression();
    ASSERT_NE(expr, nullptr);

    // Check if the variable value is set correctly
    ASSERT_EQ(context.GetVariable(identifier), expr->Evaluate(context));
}

// Test Evaluate method without expression
TEST_F(FVarDeclarationNodeTest, EvaluateWithoutExpression)
{
    FVarDeclarationNode varDeclaration(identifier, nullptr);

    // Evaluate the node
    ASSERT_NO_THROW(varDeclaration.Evaluate(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    // Check if the variable value is default (empty)
    ASSERT_EQ(context.GetVariable(identifier), Value());
}
