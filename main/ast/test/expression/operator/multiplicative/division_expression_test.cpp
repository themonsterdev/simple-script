#include <gtest/gtest.h>
#include "expression/operator/multiplicative/division_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class DivisionExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(DivisionExpressionTest, DivisionWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FDivisionExpression division(std::move(left), std::move(right));

    FContext context;
    Value result = division.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 2);
}

TEST_F(DivisionExpressionTest, DivisionByZero) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(0);
    FDivisionExpression division(std::move(left), std::move(right));

    FContext context;
    EXPECT_THROW(division.Evaluate(context), std::runtime_error);
}

TEST_F(DivisionExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FDivisionExpression division(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(division.Evaluate(context), std::runtime_error);
}
