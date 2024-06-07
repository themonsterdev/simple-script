#include <gtest/gtest.h>
#include "expression/identifier_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"
#include "statement/declaration/var_declaration_statement.hpp"

// Include declarations for context objects
#include "context.hpp"

class FVarDeclarationStatementTest : public ::testing::Test
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
        expression = std::make_unique<FNumberExpression>(42);
    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {

    }
};

// Test constructor with valid input
TEST_F(FVarDeclarationStatementTest, ConstructorValidInput)
{
    // Construct FVarDeclarationStatement
    ASSERT_NO_THROW(FVarDeclarationStatement(identifier, std::move(expression)));
}

// Test constructor with empty identifier
TEST_F(FVarDeclarationStatementTest, ConstructorEmptyIdentifier)
{
    // Construct FVarDeclarationStatement with empty identifier
    ASSERT_THROW(FVarDeclarationStatement("", std::move(expression)), std::invalid_argument);
}

// Test GetIdentifier method
TEST_F(FVarDeclarationStatementTest, GetIdentifier)
{
    FVarDeclarationStatement varDeclaration(identifier, std::move(expression));

    // Check the identifier of the statement
    ASSERT_EQ(varDeclaration.GetIdentifier(), identifier);
}

// Test GetExpression method
TEST_F(FVarDeclarationStatementTest, GetExpression)
{
    auto* rawExpressionPtr = expression.get(); // Conserver un pointeur brut pour la comparaison

    FVarDeclarationStatement varDeclaration(identifier, std::move(expression));

    // Check the expression of the statement
    ASSERT_EQ(varDeclaration.GetExpression().get(), rawExpressionPtr);
}

// Test Evaluate method with expression
TEST_F(FVarDeclarationStatementTest, EvaluateWithExpression)
{
    FVarDeclarationStatement varDeclaration(identifier, std::move(expression));

    // Evaluate the statement
    ASSERT_NO_THROW(varDeclaration.Execute(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    const auto& expr = varDeclaration.GetExpression();
    ASSERT_NE(expr, nullptr);

    // Check if the variable value is set correctly
    ASSERT_EQ(
        context.GetVariable(identifier)->ToString(),
        expr->Evaluate(context)->ToString()
    );
}

// Test Evaluate method without expression
TEST_F(FVarDeclarationStatementTest, EvaluateWithoutExpression)
{
    FVarDeclarationStatement varDeclaration(identifier, nullptr);

    // Evaluate the statement
    ASSERT_NO_THROW(varDeclaration.Execute(context));

    // Check if the variable is declared
    ASSERT_TRUE(context.IsVariableDeclared(identifier));

    // Check if the variable value is default (empty)
    ValuePtr value = context.GetVariable(identifier);
    ASSERT_EQ(value, nullptr);
}
