#include <gtest/gtest.h>
#include "expression/operator/comparison/less_than_or_equal_to_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class LessThanOrEqualToExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(LessThanOrEqualToExpressionTest, LessThanOrEqualToWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FLessThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LessThanOrEqualToExpressionTest, LessThanOrEqualToWithNegativeIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-5);
    FLessThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(LessThanOrEqualToExpressionTest, LessThanOrEqualToWithMixedIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FLessThanOrEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LessThanOrEqualToExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FLessThanOrEqualToExpression comparison(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
