#include <gtest/gtest.h>
#include "expression/operator/logical/logical_or_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class LogicalOrExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(LogicalOrExpressionTest, LogicalOrWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    ExpressionPtr right = std::make_unique<FNumberExpression>(true);
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    FContext context;
    Value result = logicOr.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LogicalOrExpressionTest, LogicalOrWithOneTrue) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    ExpressionPtr right = std::make_unique<FNumberExpression>(false);
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    FContext context;
    Value result = logicOr.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LogicalOrExpressionTest, LogicalOrWithBothFalse) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(false);
    ExpressionPtr right = std::make_unique<FNumberExpression>(false);
    FLogicalOrExpression logicOr(std::move(left), std::move(right));

    FContext context;
    Value result = logicOr.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(LogicalOrExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    FLogicalOrExpression logicOr(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(logicOr.Evaluate(context), std::runtime_error);
}
