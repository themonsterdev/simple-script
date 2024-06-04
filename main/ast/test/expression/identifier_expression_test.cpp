#include <gtest/gtest.h>
#include "expression/identifier_expression.hpp"

// Include declarations for context objects
#include "context.hpp"

// Test the constructor of FIdentifierExpression
TEST(FIdentifierExpressionTest, Constructor)
{
    // Create an FIdentifierExpression object with a name
    FIdentifierExpression identifier("x");

    // Check if the name is set correctly
    EXPECT_EQ(identifier.GetName(), "x");
}

// Test the GetName method of FIdentifierExpression
TEST(FIdentifierExpressionTest, GetName)
{
    // Create an FIdentifierExpression object with a name
    FIdentifierExpression identifier("x");

    // Check if the GetName method returns the correct name
    EXPECT_EQ(identifier.GetName(), "x");
}

// Test the SetName method of FIdentifierExpression
TEST(FIdentifierExpressionTest, SetName)
{
    // Create an FIdentifierExpression object with a name
    FIdentifierExpression identifier("x");

    // Set a new name for the identifier
    identifier.SetName("y");

    // Check if the name is updated correctly
    EXPECT_EQ(identifier.GetName(), "y");
}

// Test the Evaluate method of FIdentifierExpression with a valid context
TEST(FIdentifierExpressionTest, EvaluateValid)
{
    // Create an FIdentifierExpression object with a name
    FIdentifierExpression identifier("x");

    // Create a context with a variable "x"
    FContext context;
    context.SetVariable("x", 42);

    // Evaluate the identifier expression in the context
    Value result = identifier.Evaluate(context);

    // Check if the result is as expected
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 42);
}

// Test the Evaluate method of FIdentifierExpression with an undefined variable in the context
TEST(FIdentifierExpressionTest, EvaluateUndefinedVariable)
{
    // Create an FIdentifierExpression object with a name
    FIdentifierExpression identifier("x");

    // Create a context without setting the variable "x"
    FContext context;

    // Evaluate the identifier expression in the context
    // This should throw a runtime_error since the variable "x" is undefined
    EXPECT_THROW(identifier.Evaluate(context), std::runtime_error);
}
