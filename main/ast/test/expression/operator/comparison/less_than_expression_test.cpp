#include <gtest/gtest.h>
#include "expression/operator/comparison/less_than_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class LessThanExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(LessThanExpressionTest, LessThanWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FLessThanExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LessThanExpressionTest, LessThanWithNegativeIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-5);
    FLessThanExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(LessThanExpressionTest, LessThanWithMixedIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(-3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FLessThanExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LessThanExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FLessThanExpression comparison(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
