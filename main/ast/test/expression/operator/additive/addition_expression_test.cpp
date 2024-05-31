#include <gtest/gtest.h>
#include "expression/operator/additive/addition_expression.hpp"
#include "expression/literal/number_expression.hpp"

class FAdditionExpressionTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        // Initialisation des données communes aux tests, si nécessaire
    }

    void TearDown() override
    {
        // Nettoyage des ressources allouées, si nécessaire
    }
};

TEST_F(FAdditionExpressionTest, AdditionWithIntegers)
{
    // Création d'une expression d'addition avec des entiers
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Création d'un contexte vide pour l'évaluation
    FContext context;

    // Vérification que l'évaluation retourne la somme attendue
    EXPECT_EQ(addition.Evaluate(context), Value(8));
}

TEST_F(FAdditionExpressionTest, AdditionWithNegativeIntegers)
{
    // Création d'une expression d'addition avec des entiers négatifs
    ExpressionPtr left = std::make_unique<FNumberExpression>(-5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Création d'un contexte vide pour l'évaluation
    FContext context;

    // Vérification que l'évaluation retourne la somme attendue
    EXPECT_EQ(addition.Evaluate(context), Value(-8));
}

TEST_F(FAdditionExpressionTest, AdditionWithMixedIntegers)
{
    // Création d'une expression d'addition avec des entiers positifs et négatifs
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    ExpressionPtr right = std::make_unique<FNumberExpression>(-3);
    FAdditionExpression addition(std::move(left), std::move(right));

    // Création d'un contexte vide pour l'évaluation
    FContext context;

    // Vérification que l'évaluation retourne la somme attendue
    EXPECT_EQ(addition.Evaluate(context), Value(2));
}

TEST_F(FAdditionExpressionTest, MissingOperands)
{
    // Création d'une expression d'addition avec un opérande manquant
    ExpressionPtr left = std::make_unique<FNumberExpression>(5);
    FAdditionExpression addition(std::move(left), nullptr);

    // Création d'un contexte vide pour l'évaluation
    FContext context;

    // Vérification que l'évaluation lève une exception
    EXPECT_THROW(addition.Evaluate(context), std::runtime_error);
}
