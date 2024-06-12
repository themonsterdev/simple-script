#include <gtest/gtest.h>
#include "context/context.hpp"

// Test fixture class for FContext
class FContextTest : public ::testing::Test
{
protected:

    FContext context;

    // Setup method to initialize the test fixture
    void SetUp() override
    {

    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {

    }
};

// Test the default constructor
TEST_F(FContextTest, DefaultConstructor)
{
    // Check if the context is not null
    ASSERT_NE(&context, nullptr);
}

// Test entering and leaving scopes
TEST_F(FContextTest, EnterLeaveScope)
{
    // Initially, there should be one scope (global scope)
    ASSERT_EQ(context.IsVariableDeclared("test_var"), false);

    // Enter a new scope
    context.EnterScope();
    ASSERT_EQ(context.IsVariableDeclared("test_var"), false);

    // Leave the current scope
    context.LeaveScope();
    ASSERT_EQ(context.IsVariableDeclared("test_var"), false);
}

// Test variable declaration and assignment
TEST_F(FContextTest, DeclareAssignVariable)
{
    // Declare and assign a variable
    context.DeclareVariable("test_var");
    // context.AssignVariable("test_var", 42);

    // Check if the variable is declared and assigned
    ASSERT_EQ(context.IsVariableDeclared("test_var"), true);
    // ASSERT_EQ(std::get<int>(context.GetVariable("test_var")), 42);
}

// Test variable declaration without assignment
TEST_F(FContextTest, DeclareVariableWithoutAssignment)
{
    // Declare a variable without assigning it
    context.DeclareVariable("test_var2");

    // Check if the variable is declared but not assigned
    ASSERT_EQ(context.IsVariableDeclared("test_var2"), true);
}

// Test variable assignment without declaration
// TEST_F(FContextTest, AssignVariableWithoutDeclaration)
// {
//     // Attempt to assign a value to an undeclared variable
//     ASSERT_THROW(context.AssignVariable("test_var", 42), std::runtime_error);
// }

// Test variable access
// TEST_F(FContextTest, GetVariable)
// {
//     // Declare and assign a variable
//     context.DeclareVariable("test_var");
//     context.AssignVariable("test_var", 42);
// 
//     // Access the variable and check its value
//     ASSERT_EQ(std::get<int>(context.GetVariable("test_var")), 42);
// }

// Test accessing an undeclared variable
TEST_F(FContextTest, AccessUndeclaredVariable)
{
    // Attempt to access an undeclared variable
    ASSERT_THROW(context.GetVariable("test_var"), std::runtime_error);
}
