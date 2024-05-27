#include <gtest/gtest.h>
#include "tokenizer.hpp"
#include "parser.hpp"
#include "context.hpp"

// Statement
#include "ast/statement/arithmetic_operator_node.hpp"
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

// Test fixture pour les expressions
class FParserTest : public ::testing::Test
{
protected:

    FContext context;

    // Fonction SetUp() sera appelée avant chaque test
    void SetUp() override
    {
        // Initialiser le contexte avec les variables nécessaires pour les tests
        context.SetVariable("x", 10);
        context.SetVariable("y", 5);
    }

    // Fonction TearDown() sera appelée après chaque test
    void TearDown() override
    {
        
    }
};

TEST_F(FParserTest, EvaluateAssignmentNodeTest)
{
    ASyntaxNodePtr number = std::make_unique<FNumberNode>(10);

    // Créer un nœud de déclaration de variable
    ASyntaxNodePtr assignmentNode = std::make_unique<FAssignmentNode>("x", number.release());

    // Évaluer le nœud de déclaration de variable
    assignmentNode->Evaluate(context);

    // Assurez-vous que Value est correctement initialisé avec une valeur de 10
    Value expectedValue = Value(10);

    // Vérifier si la variable a été correctement définie dans le contexte
    ASSERT_EQ(context.GetVariable("x"), expectedValue);
}

TEST_F(FParserTest, EvaluateVarDeclarationNodeTest)
{
    ASyntaxNodePtr number = std::make_unique<FNumberNode>(20);

    // Créer un nœud de déclaration de variable
    ASyntaxNodePtr varDeclarationNode = std::make_unique<FVarDeclarationNode>("z", number.release());

    // Évaluer le nœud de déclaration de variable
    varDeclarationNode->Evaluate(context);

    // Assurez-vous que Value est correctement initialisé avec une valeur de 20
    Value expectedValue = Value(20);

    // Vérifier si la variable a été correctement déclarée dans le contexte
    ASSERT_EQ(context.GetVariable("z"), expectedValue);
}

TEST_F(FParserTest, EvaluatePrintStatementNodeTest)
{
    ASyntaxNodePtr identifier = std::make_unique<FIdentifierNode>("x");

    // Créer un nœud d'instruction d'impression
    ASyntaxNodePtr printNode = std::make_unique<FPrintStatementNode>(identifier.release());

    // Capturer la sortie standard pour vérifier l'impression
    testing::internal::CaptureStdout();

    // Évaluer le nœud d'instruction d'impression
    Value value = printNode->Evaluate(context);

    // Vérifier si la sortie standard contient la valeur de la variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "10\n");
}

TEST_F(FParserTest, ParseTest)
{
    std::string input;
    input += "var n = 1 + 2 * 3\n";
    input += "print n";

    std::vector<std::string> keywords = { "var", "print" };

    FTokenizer tokenizer(input, keywords);
    FParser parser(tokenizer);

    std::unique_ptr<FSyntaxTree> tree = parser.Parse();
    ASSERT_NE(tree, nullptr);

    const ASyntaxNode* root = tree->GetRoot();
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->GetType(), eSyntaxNodeType::None);

    std::vector<ASyntaxNode*> children = root->GetChildren();
    ASSERT_EQ(children.size(), 2);

    ASSERT_NE(children[0], nullptr);
    ASSERT_EQ(children[0]->GetType(), eSyntaxNodeType::VariableDeclaration);

    FVarDeclarationNode* varDeclNode = reinterpret_cast<FVarDeclarationNode*>(children[0]);
    ASSERT_EQ(varDeclNode->GetChildren().size(), 0);
    ASSERT_EQ(varDeclNode->GetIdentifier(), "n");

    const auto arithNode = reinterpret_cast<FArithmeticOperatorNode*>(varDeclNode->GetExpression());
    ASSERT_NE(arithNode, nullptr);
    ASSERT_EQ(arithNode->GetType(), eSyntaxNodeType::ArithmeticOperator);
    ASSERT_EQ(arithNode->GetOperator(), "+");

    const auto leftExpr = reinterpret_cast<const FNumberNode*>(arithNode->GetChild(0));
    ASSERT_NE(leftExpr, nullptr);
    ASSERT_EQ(leftExpr->GetType(), eSyntaxNodeType::Number);

    const auto rightExpr = reinterpret_cast<const FArithmeticOperatorNode*>(arithNode->GetChild(1));
    ASSERT_NE(rightExpr, nullptr);
    ASSERT_EQ(rightExpr->GetType(), eSyntaxNodeType::ArithmeticOperator);

    ASSERT_NE(rightExpr->GetChild(0), nullptr);
    ASSERT_EQ(rightExpr->GetChild(0)->GetType(), eSyntaxNodeType::Number);

    ASSERT_NE(rightExpr->GetChild(1), nullptr);
    ASSERT_EQ(rightExpr->GetChild(1)->GetType(), eSyntaxNodeType::Number);

    const auto printStat = reinterpret_cast<FPrintStatementNode*>(children[1]);
    ASSERT_NE(printStat, nullptr);
    ASSERT_EQ(printStat->GetType(), eSyntaxNodeType::PrintStatement);

    const auto idExpr = reinterpret_cast<FIdentifierNode*>(printStat->GetExpression());
    ASSERT_NE(idExpr, nullptr);
    ASSERT_EQ(idExpr->GetType(), eSyntaxNodeType::Identifier);

    // Capturer la sortie standard pour vérifier l'impression
    testing::internal::CaptureStdout();

    // Évaluer le nœud d'instruction d'impression
    // varDeclNode->Evaluate(context);  // Ensure variables are initialized
    // printStat->Evaluate(context);    // Evaluate the print statement
    root->Evaluate(context);

    // Vérifier si la sortie standard contient la valeur de la variable
    std::string output = testing::internal::GetCapturedStdout();
    ASSERT_EQ(output, "7\n");
}
