#include <gtest/gtest.h>

#include "lexer.hpp"
#include "exception/syntax_exception.hpp"
#include "expression/expression_parser.hpp"
#include "statement/statement_parser.hpp"
#include "statement/block/block_statement.hpp"

// TEST(FParserBlockStatementTest, ParseBlockStatementWithThenAndEnd)
// {
//     std::string input("if condition then\n"
//         "  \n"
//         "  \n"
//         "end");
// 
//     FLexer lexer(input);
//     FExpressionParser expressionParser(lexer);
//     FStatementParser parser(lexer, expressionParser);
// 
//     const auto& statement = parser.ParseStatement();
//     ASSERT_NE(statement, nullptr);
// 
//     const auto& blockStatement = dynamic_cast<FBlockStatement*>(statement.get());
//     ASSERT_NE(blockStatement, nullptr);
// 
//     const auto& statements = blockStatement->GetStatements();
//     ASSERT_EQ(statements.size(), 2); // Number of statements inside the block
// 
//     // Assert the contents of the block
//     // You can iterate over statements and further assert their types and contents if needed
// }

// TEST(FParserBlockStatementTest, ParseEmptyBlockStatementWithThenAndEnd)
// {
//     std::string input("if condition then\n"
//         "end");
// 
//     FLexer lexer(input);
//     FExpressionParser expressionParser(lexer);
//     FStatementParser parser(lexer, expressionParser);
// 
//     const auto& statement = parser.ParseStatement();
//     ASSERT_NE(statement, nullptr);
// 
//     const auto& blockStatement = dynamic_cast<FBlockStatement*>(statement.get());
//     ASSERT_NE(blockStatement, nullptr);
// 
//     const auto& statements = blockStatement->GetStatements();
//     ASSERT_TRUE(statements.empty()); // The block should have no statements
// }

// TEST(FParserBlockStatementTest, ParseBlockStatementWithoutEnd)
// {
//     std::string input("if condition then\n"
//         "  statement1\n"
//         "  statement2\n"
//         "statement3");
// 
//     FLexer lexer(input);
//     FExpressionParser expressionParser(lexer);
//     FStatementParser parser(lexer, expressionParser);
// 
//     // This should throw an exception because the END keyword is missing
//     ASSERT_THROW(parser.ParseStatement(), SyntaxException);
// }
