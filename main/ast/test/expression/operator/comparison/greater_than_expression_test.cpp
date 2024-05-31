#include <gtest/gtest.h>
#include "expression/operator/comparison/greater_than_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class FGreaterThanExpressionTest : public ::testing::Test
{
protected:

    FContext context;

    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(FGreaterThanExpressionTest, GreaterThanWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(FGreaterThanExpressionTest, GreaterThanWithNegativeIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(FGreaterThanExpressionTest, GreaterThanWithMixedIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FGreaterThanExpression comparison(std::move(left), std::move(right));

    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(FGreaterThanExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FGreaterThanExpression comparison(std::move(left), nullptr);
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
