#include <gtest/gtest.h>
#include "expression/operator/unary/unary_negate_expression.hpp"
#include "expression/literal/number_expression.hpp"

class UnaryNegateExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(UnaryNegateExpressionTest, NegatePositiveInteger) {
    ExpressionPtr expression = std::make_unique<FNumberExpression>(5);
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    Value result = unaryNegate.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), -5);
}

TEST_F(UnaryNegateExpressionTest, NegateNegativeInteger) {
    ExpressionPtr expression = std::make_unique<FNumberExpression>(-3);
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    Value result = unaryNegate.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 3);
}

TEST_F(UnaryNegateExpressionTest, NegateZero) {
    ExpressionPtr expression = std::make_unique<FNumberExpression>(0);
    FUnaryNegateExpression unaryNegate(std::move(expression));

    FContext context;
    Value result = unaryNegate.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<int>(result));
    EXPECT_EQ(std::get<int>(result), 0);
}
