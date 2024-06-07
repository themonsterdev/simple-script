#include <gtest/gtest.h>
#include "scope.hpp"

// Test fixture class for FScope
class FScopeTest : public ::testing::Test
{
protected:

    // Setup method to initialize the test fixture
    void SetUp() override
    {

    }

    // Teardown method to clean up the test fixture
    void TearDown() override
    {

    }
};

// Test case for adding a variable to the scope
TEST_F(FScopeTest, DeclareVariable)
{
    FScope scope;
    scope.DeclareVariable("x");
    ASSERT_TRUE(scope.IsVariableDeclared("x"));
}

// Test case for setting and getting a variable in the scope
// TEST_F(FScopeTest, SetAndGetVariable)
// {
//     FScope scope;
//     scope.SetVariable("x", 10);
//     ASSERT_EQ(std::get<int>(scope.GetVariable("x")), 10);
// }

// Test case for removing a variable from the scope
TEST_F(FScopeTest, RemoveVariable)
{
    FScope scope;
    scope.DeclareVariable("x");
    ASSERT_TRUE(scope.IsVariableDeclared("x"));
    scope.RemoveVariable("x");
    ASSERT_FALSE(scope.IsVariableDeclared("x"));
}

// Test case for checking if a variable exists in the scope
TEST_F(FScopeTest, IsVariableDeclared)
{
    FScope scope;
    scope.DeclareVariable("x");
    ASSERT_TRUE(scope.IsVariableDeclared("x"));
    ASSERT_FALSE(scope.IsVariableDeclared("y"));
}

// Test case for getting an undefined variable from the scope
TEST_F(FScopeTest, GetUndefinedVariable)
{
    FScope scope;
    ASSERT_THROW(scope.GetVariable("x"), std::runtime_error);
}

// Test case for getting a variable of a specific type from the scope
// TEST_F(FScopeTest, IsVariableOfType)
// {
//     FScope scope;
//     scope.SetVariable("x", 10);
//     ASSERT_TRUE(scope.IsVariableOfType<int>("x"));
//     ASSERT_FALSE(scope.IsVariableOfType<std::string>("x"));
// }
