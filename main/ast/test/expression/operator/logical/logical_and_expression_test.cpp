#include <gtest/gtest.h>
#include "expression/operator/logical/logical_and_expression.hpp"
#include "expression/literal/number_expression.hpp"
#include "context.hpp"

class LogicalAndExpressionTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(LogicalAndExpressionTest, LogicalAndWithIntegers) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    ExpressionPtr right = std::make_unique<FNumberExpression>(true);
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    FContext context;
    Value result = logicAnd.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_TRUE(std::get<bool>(result));
}

TEST_F(LogicalAndExpressionTest, LogicalAndWithOneFalse) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    ExpressionPtr right = std::make_unique<FNumberExpression>(false);
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    FContext context;
    Value result = logicAnd.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(LogicalAndExpressionTest, LogicalAndWithBothFalse) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(false);
    ExpressionPtr right = std::make_unique<FNumberExpression>(false);
    FLogicalAndExpression logicAnd(std::move(left), std::move(right));

    FContext context;
    Value result = logicAnd.Evaluate(context);
    EXPECT_TRUE(std::holds_alternative<bool>(result));
    EXPECT_FALSE(std::get<bool>(result));
}

TEST_F(LogicalAndExpressionTest, MissingOperands) {
    ExpressionPtr left = std::make_unique<FNumberExpression>(true);
    FLogicalAndExpression logicAnd(std::move(left), nullptr);

    FContext context;
    EXPECT_THROW(logicAnd.Evaluate(context), std::runtime_error);
}
