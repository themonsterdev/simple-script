#include <gtest/gtest.h>
#include "expression/operator/comparison/greater_than_or_equal_to_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class GreaterThanOrEqualToExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FGreaterThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithNegativeIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FGreaterThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(GreaterThanOrEqualToExpressionTest, GreaterThanOrEqualToWithMixedIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FGreaterThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(GreaterThanOrEqualToExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FGreaterThanOrEqualToExpression comparison(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
