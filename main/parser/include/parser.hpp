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

    ASyntaxNodePtr ParseStatement();
    ASyntaxNodePtr ParseAssignmentStatement();
    ASyntaxNodePtr ParseVarDeclarationStatement();
    ASyntaxNodePtr ParsePrintStatement();

    ASyntaxNodePtr ParseExpression();
    ASyntaxNodePtr ParseArithmeticOperatorExpression(ASyntaxNodePtr left);
    ASyntaxNodePtr ParseStringOperatorExpression(ASyntaxNodePtr left);
    ASyntaxNodePtr ParseComparisonOperatorExpression(ASyntaxNodePtr left);
    ASyntaxNodePtr ParseIdentifier();
    ASyntaxNodePtr ParseNumber();
    ASyntaxNodePtr ParseString();

    ASyntaxNodePtr ParseTerm();
    ASyntaxNodePtr ParseFactor();
};
