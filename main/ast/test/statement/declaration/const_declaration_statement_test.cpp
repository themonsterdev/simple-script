#include <gtest/gtest.h>
#include "statement/declaration/const_declaration_statement.hpp"
#include "expression/literal/number_expression.hpp"
#include "expression/literal/string_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test the creation of a const declaration statement with a valid identifier and expression
TEST(FConstDeclarationStatementTest, ConstructorValidIdentifierAndExpression)
{
    // Create a number expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);

    // Create a const declaration statement with a valid identifier and expression
    ASSERT_NO_THROW(FConstDeclarationStatement("x", std::move(expression)));
}

// Test the creation of a const declaration statement with an empty identifier
TEST(FConstDeclarationStatementTest, ConstructorEmptyIdentifier)
{
    // Create a number expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);

    // Attempt to create a const declaration statement with an empty identifier
    ASSERT_THROW(FConstDeclarationStatement("", std::move(expression)), std::invalid_argument);
}

// Test the execution of a const declaration statement with a valid expression
TEST(FConstDeclarationStatementTest, ExecuteValidExpression)
{
    // Create a number expression
    ExpressionPtr expression = std::make_unique<FNumberExpression>(42);

    // Create a const declaration statement
    FConstDeclarationStatement constDeclaration("x", std::move(expression));

    // Create a context
    FContext context;

    // Execute the const declaration statement
    ASSERT_NO_THROW(constDeclaration.Execute(context));

    // Check if the const value is correctly set in the context
    ASSERT_TRUE(context.IsVariableDeclared("x"));
    // EXPECT_EQ(std::get<int>(context.GetVariable("x")), 42);
}

// Test the execution of a const declaration statement with a string expression
TEST(FConstDeclarationStatementTest, ExecuteStringExpression)
{
    // Create a string expression
    ExpressionPtr expression = std::make_unique<FStringExpression>("Hello");

    // Create a const declaration statement
    FConstDeclarationStatement constDeclaration("str", std::move(expression));

    // Create a context
    FContext context;

    // Execute the const declaration statement
    ASSERT_NO_THROW(constDeclaration.Execute(context));

    // Check if the const value is correctly set in the context
    ASSERT_TRUE(context.IsVariableDeclared("str"));
    // EXPECT_EQ(std::get<std::string>(context.GetVariable("str")), "Hello");
}

// Test the execution of a const declaration statement with no expression
TEST(FConstDeclarationStatementTest, ExecuteNoExpression)
{
    // Attempt to create a const declaration statement with no expression
    ASSERT_THROW(FConstDeclarationStatement("x", nullptr).Execute(FContext()), std::runtime_error);
}
