#pragma once

#include <memory>
#include <string>

#include "ast/syntax_tree.hpp"

class FTokenizer;

class FParser final
{
	FTokenizer& m_tokenizer;

public:

    FParser(FTokenizer& tokenizer);
    std::unique_ptr<FSyntaxTree> Parse();

private:

    std::unique_ptr<ASyntaxNode> ParseStatement();
    std::unique_ptr<ASyntaxNode> ParseAssignmentStatement();
    std::unique_ptr<ASyntaxNode> ParseVarDeclarationStatement();
    std::unique_ptr<ASyntaxNode> ParsePrintStatement();

    std::unique_ptr<ASyntaxNode> ParseExpression();
    std::unique_ptr<ASyntaxNode> ParseArithmeticOperatorExpression(ASyntaxNode* left);
    std::unique_ptr<ASyntaxNode> ParseComparisonOperatorExpression(ASyntaxNode* left);
    std::unique_ptr<ASyntaxNode> ParseIdentifier();
    std::unique_ptr<ASyntaxNode> ParseNumber();

    std::unique_ptr<ASyntaxNode> ParseTerm();
    std::unique_ptr<ASyntaxNode> ParseFactor();
};
