#include <gtest/gtest.h>
#include "expression/operator/equality/not_equal_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class NotEqualExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(NotEqualExpressionTest, NotEqualToWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FNotEqualExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(NotEqualExpressionTest, NotEqualToWithDifferentIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FNotEqualExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(NotEqualExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FNotEqualExpression comparison(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
