#include <gtest/gtest.h>
#include "expression/operator/multiplicative/multiply_expression.hpp"
#include "expression/literal/number_expression.hpp"

class MultiplyExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(MultiplyExpressionTest, MultiplyWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FMultiplyExpression multiply(std::move(left), std::move(right));

    FContext context;
    Value result = multiply.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 18);
}

TEST_F(MultiplyExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FMultiplyExpression multiply(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(multiply.Evaluate(context), std::runtime_error);
}
