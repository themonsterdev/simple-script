#include <gtest/gtest.h>

#include "lexer.hpp"
#include "exception/syntax_exception.hpp"

#include "expression/expression_parser.hpp"
#include "expression/identifier_expression.hpp"

#include "statement/statement_parser.hpp"
#include "statement/block_statement.hpp"
#include "statement/conditional_statement.hpp"

TEST(FParserConditionalStatementTest, ParseIfStatementWithoutStatements)
{
    std::string input("if condition then\n"
        "end");

    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& ifStatement = dynamic_cast<FConditionalStatement*>(statement.get());
    ASSERT_NE(ifStatement, nullptr);

    // condition
    {
        const auto& conditionExpxression = ifStatement->GetCondition();
        ASSERT_NE(conditionExpxression, nullptr);

        const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpxression.get());
        ASSERT_NE(idStatement, nullptr);
        ASSERT_EQ(idStatement->GetName(), "condition");
    }

    // if then
    {
        const auto& ifThenStatement = ifStatement->GetIfStatement();
        ASSERT_NE(ifThenStatement, nullptr);

        const auto& blockStatement = dynamic_cast<FBlockStatement*>(ifThenStatement.get());
        ASSERT_NE(blockStatement, nullptr);

        const auto& statements = blockStatement->GetStatements();
        ASSERT_EQ(statements.size(), 0); // Number of statements inside the block
    }
}

TEST(FParserConditionalStatementTest, ParseIfStatementWithThenAndEnd)
{
    std::string input("if condition then\n"
        "  print 0\n"
        "  print 0\n"
        "end");

    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& ifStatement = dynamic_cast<FConditionalStatement*>(statement.get());
    ASSERT_NE(ifStatement, nullptr);

    // condition
    {
        const auto& conditionExpxression = ifStatement->GetCondition();
        ASSERT_NE(conditionExpxression, nullptr);

        const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpxression.get());
        ASSERT_NE(idStatement, nullptr);
        ASSERT_EQ(idStatement->GetName(), "condition");
    }

    // if then
    {
        const auto& blockStatement = dynamic_cast<FBlockStatement*>(ifStatement->GetIfStatement().get());
        ASSERT_NE(blockStatement, nullptr);

        const auto& statements = blockStatement->GetStatements();
        ASSERT_EQ(statements.size(), 2); // Number of statements inside the block
    }
}

TEST(FParserConditionalStatementTest, ParseIfElseIfStatement)
{
    std::string input("if condition then\n"
        "  print 0\n"
        "else if other_condition then\n"
        "  print 1\n"
        "end");

    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& ifStatement = dynamic_cast<FConditionalStatement*>(statement.get());
    ASSERT_NE(ifStatement, nullptr);

    // condition
    {
        const auto& conditionExpression = ifStatement->GetCondition();
        ASSERT_NE(conditionExpression, nullptr);

        const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
        ASSERT_NE(idStatement, nullptr);
        ASSERT_EQ(idStatement->GetName(), "condition");
    }

    // if then
    {
        const auto& blockStatement = dynamic_cast<FBlockStatement*>(ifStatement->GetIfStatement().get());
        ASSERT_NE(blockStatement, nullptr);

        const auto& statements = blockStatement->GetStatements();
        ASSERT_EQ(statements.size(), 1); // Number of statements inside the block
    }

    // else if
    {
        const auto& elseIfStatements = ifStatement->GetElseIfStatements();
        ASSERT_EQ(elseIfStatements.size(), 1);

        const auto& elseIfStatement = dynamic_cast<FConditionalStatement*>(elseIfStatements.front().get());
        ASSERT_NE(elseIfStatement, nullptr);

        const auto& elseIfCondition = elseIfStatement->GetCondition();
        ASSERT_NE(elseIfCondition, nullptr);

        const auto& elseIfIdStatement = dynamic_cast<FIdentifierExpression*>(elseIfCondition.get());
        ASSERT_NE(elseIfIdStatement, nullptr);
        ASSERT_EQ(elseIfIdStatement->GetName(), "other_condition");

        const auto& elseIfBlockStatement = dynamic_cast<FBlockStatement*>(elseIfStatement->GetIfStatement().get());
        ASSERT_NE(elseIfBlockStatement, nullptr);

        const auto& elseIfStatementsBlock = elseIfBlockStatement->GetStatements();
        ASSERT_EQ(elseIfStatementsBlock.size(), 1); // Number of statements inside the block
    }
}

TEST(FParserConditionalStatementTest, ParseIfElseIfElseStatement)
{
    std::string input("if condition then\n"
        "  print 0\n"
        "else if other_condition then\n"
        "  print 1\n"
        "else\n"
        "  print 2\n"
        "end");

    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& ifStatement = dynamic_cast<FConditionalStatement*>(statement.get());
    ASSERT_NE(ifStatement, nullptr);

    // condition
    {
        const auto& conditionExpression = ifStatement->GetCondition();
        ASSERT_NE(conditionExpression, nullptr);

        const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
        ASSERT_NE(idStatement, nullptr);
        ASSERT_EQ(idStatement->GetName(), "condition");
    }

    // if then
    {
        const auto& blockStatement = dynamic_cast<FBlockStatement*>(ifStatement->GetIfStatement().get());
        ASSERT_NE(blockStatement, nullptr);

        const auto& statements = blockStatement->GetStatements();
        ASSERT_EQ(statements.size(), 1); // Number of statements inside the block
    }

    // else if
    {
        const auto& elseIfStatements = ifStatement->GetElseIfStatements();
        ASSERT_EQ(elseIfStatements.size(), 1);

        const auto& elseIfStatement = dynamic_cast<FConditionalStatement*>(elseIfStatements.front().get());
        ASSERT_NE(elseIfStatement, nullptr);

        const auto& elseIfCondition = elseIfStatement->GetCondition();
        ASSERT_NE(elseIfCondition, nullptr);

        const auto& elseIfIdStatement = dynamic_cast<FIdentifierExpression*>(elseIfCondition.get());
        ASSERT_NE(elseIfIdStatement, nullptr);
        ASSERT_EQ(elseIfIdStatement->GetName(), "other_condition");

        const auto& elseIfBlockStatement = dynamic_cast<FBlockStatement*>(elseIfStatement->GetIfStatement().get());
        ASSERT_NE(elseIfBlockStatement, nullptr);

        const auto& elseIfStatementsBlock = elseIfBlockStatement->GetStatements();
        ASSERT_EQ(elseIfStatementsBlock.size(), 1); // Number of statements inside the block
    }

    // else
    {
        const auto& elseStatement = ifStatement->GetElseStatement();
        ASSERT_NE(elseStatement, nullptr);

        const auto& elseBlockStatement = dynamic_cast<FBlockStatement*>(elseStatement.get());
        ASSERT_NE(elseBlockStatement, nullptr);

        const auto& elseStatements = elseBlockStatement->GetStatements();
        ASSERT_EQ(elseStatements.size(), 1); // Number of statements inside the block
    }
}

TEST(FParserConditionalStatementTest, ParseNestedIfElseIfElseStatement)
{
    std::string input("if condition1 then\n"
        "  if condition2 then\n"
        "    print 1\n"
        "  else\n"
        "    print 2\n"
        "  end\n"
        "else if condition3 then\n"
        "  print 3\n"
        "else\n"
        "  print 4\n"
        "end");

    FLexer lexer(input);
    FExpressionParser expressionParser(lexer);
    FStatementParser statementParser(lexer, expressionParser);

    const auto& statement = statementParser.ParseStatement();
    ASSERT_NE(statement, nullptr);

    const auto& ifStatement = dynamic_cast<FConditionalStatement*>(statement.get());
    ASSERT_NE(ifStatement, nullptr);

    // condition1
    {
        const auto& conditionExpression = ifStatement->GetCondition();
        ASSERT_NE(conditionExpression, nullptr);

        const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
        ASSERT_NE(idStatement, nullptr);
        ASSERT_EQ(idStatement->GetName(), "condition1");
    }

    // if then
    {
        const auto& blockStatement = dynamic_cast<FBlockStatement*>(ifStatement->GetIfStatement().get());
        ASSERT_NE(blockStatement, nullptr);

        const auto& statements = blockStatement->GetStatements();
        ASSERT_EQ(statements.size(), 1); // Number of statements inside the block

        const auto& nestedIfStatement = dynamic_cast<FConditionalStatement*>(statements.front().get());
        ASSERT_NE(nestedIfStatement, nullptr);

        // condition2
        {
            const auto& conditionExpression = nestedIfStatement->GetCondition();
            ASSERT_NE(conditionExpression, nullptr);

            const auto& idStatement = dynamic_cast<FIdentifierExpression*>(conditionExpression.get());
            ASSERT_NE(idStatement, nullptr);
            ASSERT_EQ(idStatement->GetName(), "condition2");
        }

        // if then
        {
            const auto& nestedBlockStatement = dynamic_cast<FBlockStatement*>(nestedIfStatement->GetIfStatement().get());
            ASSERT_NE(nestedBlockStatement, nullptr);

            const auto& nestedStatements = nestedBlockStatement->GetStatements();
            ASSERT_EQ(nestedStatements.size(), 1); // Number of statements inside the block
        }

        // else
        {
            const auto& elseStatement = nestedIfStatement->GetElseStatement();
            ASSERT_NE(elseStatement, nullptr);

            const auto& elseBlockStatement = dynamic_cast<FBlockStatement*>(elseStatement.get());
            ASSERT_NE(elseBlockStatement, nullptr);

            const auto& elseStatements = elseBlockStatement->GetStatements();
            ASSERT_EQ(elseStatements.size(), 1); // Number of statements inside the block
        }
    }

    // else if condition3
    {
        const auto& elseIfStatements = ifStatement->GetElseIfStatements();
        ASSERT_EQ(elseIfStatements.size(), 1);

        const auto& elseIfStatement = dynamic_cast<FConditionalStatement*>(elseIfStatements.front().get());
        ASSERT_NE(elseIfStatement, nullptr);

        const auto& elseIfCondition = elseIfStatement->GetCondition();
        ASSERT_NE(elseIfCondition, nullptr);

        const auto& elseIfIdStatement = dynamic_cast<FIdentifierExpression*>(elseIfCondition.get());
        ASSERT_NE(elseIfIdStatement, nullptr);
        ASSERT_EQ(elseIfIdStatement->GetName(), "condition3");

        const auto& elseIfBlockStatement = dynamic_cast<FBlockStatement*>(elseIfStatement->GetIfStatement().get());
        ASSERT_NE(elseIfBlockStatement, nullptr);

        const auto& elseIfStatementsBlock = elseIfBlockStatement->GetStatements();
        ASSERT_EQ(elseIfStatementsBlock.size(), 1); // Number of statements inside the block
    }

    // else
    {
        const auto& elseStatement = ifStatement->GetElseStatement();
        ASSERT_NE(elseStatement, nullptr);

        const auto& elseBlockStatement = dynamic_cast<FBlockStatement*>(elseStatement.get());
        ASSERT_NE(elseBlockStatement, nullptr);

        const auto& elseStatements = elseBlockStatement->GetStatements();
        ASSERT_EQ(elseStatements.size(), 1); // Number of statements inside the block
    }
}
