#pragma once

#include "ast/syntax_tree.hpp"
#include <unordered_map>

class FInterpreter final
{
	// Structure de données pour stocker les valeurs des variables
	std::unordered_map<std::string, int> m_variables;

public:

	void Interpret(const FSyntaxTree* syntaxTree);

private:

	void EvaluateNode(const ASyntaxNode* node);
	int EvaluateExpression(const ASyntaxNode* expression);
};
