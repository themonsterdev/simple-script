#include <gtest/gtest.h>
#include "expression/operator/multiplicative/modulo_expression.hpp"
#include "expression/literal/number_expression.hpp"

class ModuloExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(ModuloExpressionTest, ModuloWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FModuloExpression modulo(std::move(left), std::move(right));

    FContext context;
    Value result = modulo.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 0);
}

TEST_F(ModuloExpressionTest, ModuloByZero) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    ExpressionPtr right = std::make_unique<FNumberExpression>(0);
    FModuloExpression modulo(std::move(left), std::move(right));

    FContext context;
    EXPECT_THROW(modulo.Evaluate(context), std::runtime_error);
}

TEST_F(ModuloExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(6);
    FModuloExpression modulo(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(modulo.Evaluate(context), std::runtime_error);
}
