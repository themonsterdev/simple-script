#include <gtest/gtest.h>
#include "expression/operator/unary/unary_not_expression.hpp"
#include "expression/literal/boolean_expression.hpp"

class UnaryNotExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(UnaryNotExpressionTest, NotTrue) {
    ExpressionPtr expression = std::make_unique<FBooleanExpression>(true);
    FUnaryNotExpression unaryNot(std::move(expression));

    FContext context;
    Value result = unaryNot.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_EQ(std::get<bool>(result), false);
}

TEST_F(UnaryNotExpressionTest, NotFalse) {
    ExpressionPtr expression = std::make_unique<FBooleanExpression>(false);
    FUnaryNotExpression unaryNot(std::move(expression));

    FContext context;
    Value result = unaryNot.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_EQ(std::get<bool>(result), true);
}
