#include <gtest/gtest.h>
#include "statement/declaration/var_declaration_list_statement.hpp"
#include "statement/declaration/const_declaration_statement.hpp"
#include "expression/literal/number_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test the creation of a variable declaration list statement with valid declarations
TEST(FVarDeclarationListStatementTest, ConstructorValidDeclarations)
{
    // Create a vector of const declaration statements
    StatementVector declarations;
    declarations.push_back(std::make_unique<FConstDeclarationStatement>("x", std::make_unique<FNumberExpression>(42)));
    declarations.push_back(std::make_unique<FConstDeclarationStatement>("y", std::make_unique<FNumberExpression>(10)));

    // Create a variable declaration list statement with valid declarations
    ASSERT_NO_THROW(FVarDeclarationListStatement(std::move(declarations)));
}

// Test the creation of a variable declaration list statement with empty declarations
TEST(FVarDeclarationListStatementTest, ConstructorEmptyDeclarations)
{
    // Create an empty vector of statements
    StatementVector declarations;

    // Attempt to create a variable declaration list statement with empty declarations
    ASSERT_NO_THROW(FVarDeclarationListStatement(std::move(declarations)));
}

// Test the execution of a variable declaration list statement with valid declarations
TEST(FVarDeclarationListStatementTest, ExecuteValidDeclarations)
{
    // Create a vector of const declaration statements
    StatementVector declarations;
    declarations.push_back(std::make_unique<FConstDeclarationStatement>("x", std::make_unique<FNumberExpression>(42)));
    declarations.push_back(std::make_unique<FConstDeclarationStatement>("y", std::make_unique<FNumberExpression>(10)));

    // Create a variable declaration list statement
    FVarDeclarationListStatement varDeclarationList(std::move(declarations));

    // Create a context
    FContext context;

    // Execute the variable declaration list statement
    ASSERT_NO_THROW(varDeclarationList.Execute(context));

    // Check if the variables are correctly set in the context
    EXPECT_TRUE(context.IsVariableDeclared("x"));
    EXPECT_TRUE(context.IsVariableDeclared("y"));
    // EXPECT_EQ(std::get<int>(context.GetVariable("x")), 42);
    // EXPECT_EQ(std::get<int>(context.GetVariable("y")), 10);
}

// Test the execution of a variable declaration list statement with empty declarations
TEST(FVarDeclarationListStatementTest, ExecuteEmptyDeclarations)
{
    // Create an empty vector of statements
    StatementVector declarations;

    // Create a variable declaration list statement with empty declarations
    FVarDeclarationListStatement varDeclarationList(std::move(declarations));

    // Create a context
    FContext context;

    // Execute the variable declaration list statement
    ASSERT_NO_THROW(varDeclarationList.Execute(context));

    // Check if no variables are set in the context
    EXPECT_FALSE(context.IsVariableDeclared("x"));
    EXPECT_FALSE(context.IsVariableDeclared("y"));
}
