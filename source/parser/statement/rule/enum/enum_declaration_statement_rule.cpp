#pragma once

#include "parser/statement/rule/enum/enum_declaration_statement_rule.hpp"
#include "ast/statement/enum/enum_declaration_statement.hpp"
#include "parser/expression/expression_parser.hpp"
#include "lexer/lexer.hpp"

bool FEnumDeclarationStatementRule::Match(FLexer& lexer) const
{
	return lexer.TryConsumeToken(eTokenType::Keyword, "enum");
}

StatementPtr FEnumDeclarationStatementRule::Parse(FLexer& lexer, FStatementParser& statementParser, FExpressionParser& expressionParser) const
{
	const auto& token = lexer.GetNextToken();

	if (!token.IsSameType(eTokenType::Identifier))
	{
		// throw error
	}

	const auto& enumName = token.GetLexeme();
	ExpressionList expressions;

	EnumValues values;

	while (lexer.HasNextToken())
	{
		const auto& token = lexer.PeekNextToken();

		if (token.IsSameType(eTokenType::Identifier))
		{
			const auto& name = token.GetLexeme();
			lexer.GetNextToken();

			values[name] = std::make_shared<FType>("number");
		}
		else
		{
			break;
		}
	}

	if (!lexer.TryConsumeToken(eTokenType::Keyword, "end"))
	{
		// throw error
	}

	const auto& enumDefinition = std::make_shared<FEnumDefinition>(
		enumName,
		values
	);

	return std::make_unique<FEnumDeclarationStatement>(
		enumDefinition,
		std::move(expressions)
	);
}
