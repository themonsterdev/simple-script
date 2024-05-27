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
    ExpressionPtr expression = nullptr;
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
    ASSERT_NO_THROW(FVarDeclarationNode(identifier, std::move(expression)));
}

// Test constructor with empty identifier
TEST_F(FVarDeclarationNodeTest, ConstructorEmptyIdentifier)
{
    // Construct VarDeclarationNode with empty identifier
    ASSERT_THROW(FVarDeclarationNode("", std::move(expression)), std::invalid_argument);
}

// Test GetIdentifier method
TEST_F(FVarDeclarationNodeTest, GetIdentifier)
{
    FVarDeclarationNode varDeclaration(identifier, std::move(expression));

    // Check the identifier of the node
    ASSERT_EQ(varDeclaration.GetIdentifier(), identifier);
}

// Test GetExpression method
TEST_F(FVarDeclarationNodeTest, GetExpression)
{
    auto* rawExpressionPtr = expression.get(); // Conserver un pointeur brut pour la comparaison

    FVarDeclarationNode varDeclaration(identifier, std::move(expression));

    // Check the expression of the node
    ASSERT_EQ(varDeclaration.GetExpression().get(), rawExpressionPtr);
}

// Test Evaluate method with expression
TEST_F(FVarDeclarationNodeTest, EvaluateWithExpression)
{
    FVarDeclarationNode varDeclaration(identifier, std::move(expression));

    // Evaluate the node
    ASSERT_NO_THROW(varDeclaration.Execute(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    const ExpressionPtr& expr = varDeclaration.GetExpression();
    ASSERT_NE(expr, nullptr);

    // Check if the variable value is set correctly
    ASSERT_EQ(context.GetVariable(identifier), expr->Evaluate(context));
}

// Test Evaluate method without expression
TEST_F(FVarDeclarationNodeTest, EvaluateWithoutExpression)
{
    FVarDeclarationNode varDeclaration(identifier, nullptr);

    // Evaluate the node
    ASSERT_NO_THROW(varDeclaration.Execute(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    // Check if the variable value is default (empty)
    ASSERT_EQ(context.GetVariable(identifier), Value());
}
