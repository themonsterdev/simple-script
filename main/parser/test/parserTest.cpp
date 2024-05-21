#include <gtest/gtest.h>
#include "tokenizer.hpp"
#include "parser.hpp"

// Statement
#include "ast/statement/assignment_node.hpp"
#include "ast/statement/binary_operator_node.hpp"
#include "ast/statement/print_statement_node.hpp"
#include "ast/statement/var_declaration_node.hpp"

// Expression
#include "ast/expression/identifier_node.hpp"
#include "ast/expression/number_node.hpp"

// Test fixture pour les expressions
class ParserTest : public ::testing::Test
{
    std::string input;
    std::vector<std::string> keywords;
    std::unique_ptr<FTokenizer> tokenizer;

protected:

    std::unique_ptr<FParser> parser;

    // Fonction SetUp() sera appelée avant chaque test
    void SetUp() override
    {
        // Initialisation des ressources communes pour les tests
        input = "var n = 0\n";
        input += "print n\n";

        input += "var o = 1 + 1\n";
        input += "print o";

        keywords = { "var", "print" };

        // Set up tokenizer and parser
        tokenizer.reset(new FTokenizer(input, keywords));
        parser.reset(new FParser(*tokenizer));
    }

    // Fonction TearDown() sera appelée après chaque test
    void TearDown() override
    {
        // Nettoyage des ressources communes après les tests
        tokenizer.reset();
        parser.reset();
    }
};

TEST_F(ParserTest, ParserTreeTest)
{
    // Parse the input
    const auto tree = parser->Parse();
    const auto root = tree->GetRoot();

    // Vérification de la présence du nœud racine
    ASSERT_NE(root, nullptr);
    ASSERT_EQ(root->GetType(), eSyntaxNodeType::None);

    // Vérification du nombre de nœuds enfants
    auto children = root->GetChildren();
    ASSERT_EQ(children.size(), 4);

    const auto varDecl = dynamic_cast<const VarDeclarationNode*>(children.at(0));
    ASSERT_NE(varDecl, nullptr);
    ASSERT_EQ(varDecl->GetType(), eSyntaxNodeType::VariableDeclaration);
    ASSERT_EQ(varDecl->GetIdentifier(), "n");

    const auto number = dynamic_cast<const NumberNode*>(varDecl->GetExpression());
    ASSERT_NE(number, nullptr);
    ASSERT_EQ(number->GetType(), eSyntaxNodeType::Number);
    ASSERT_EQ(number->GetValue(), 0);

    const auto printStmt = dynamic_cast<const PrintStatementNode*>(children.at(1));
    ASSERT_NE(printStmt, nullptr);

    const auto identifierNode = dynamic_cast<const IdentifierNode*>(printStmt->GetExpression());
    ASSERT_EQ(identifierNode->GetType(), eSyntaxNodeType::Identifier);
    ASSERT_EQ(identifierNode->GetName(), "n");
}
