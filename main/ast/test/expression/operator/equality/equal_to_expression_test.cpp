#include <gtest/gtest.h>
#include "expression/operator/equality/equal_to_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class EqualToExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(EqualToExpressionTest, EqualToWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(EqualToExpressionTest, NotEqualToWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(3);
    ExpressionPtr right = std::make_unique<FNumberExpression>(5);
    FEqualToExpression comparison(std::move(left), std::move(right));

    FContext context;
    Value result = comparison.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(EqualToExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FEqualToExpression comparison(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(comparison.Evaluate(context), std::runtime_error);
}
