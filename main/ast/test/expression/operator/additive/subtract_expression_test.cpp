#include <gtest/gtest.h>
#include "expression/operator/additive/subtract_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class FSubtractExpressionTest : public ::testing::Test
{
protected:

    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(FSubtractExpressionTest, SubtractionWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FSubtractExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(2));
}

TEST_F(FSubtractExpressionTest, SubtractionWithNegativeIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FSubtractExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(-2));
}

TEST_F(FSubtractExpressionTest, SubtractionWithMixedIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FSubtractExpression subtraction(std::move(left), std::move(right));

    FContext context;
    EXPECT_EQ(subtraction.Evaluate(context), Value(8));
}

TEST_F(FSubtractExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FSubtractExpression subtraction(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(subtraction.Evaluate(context), std::runtime_error);
}
