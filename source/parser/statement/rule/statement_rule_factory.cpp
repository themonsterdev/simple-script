#include "parser/statement/rule/statement_rule_factory.hpp"

#include "parser/statement/rule/block/block_statement_rule.hpp"

#include "parser/statement/rule/conditional/conditional_statement_rule.hpp"

#include "parser/statement/rule/control_flow/return_statement_rule.hpp"

#include "parser/statement/rule/declaration/assignment_statement_rule.hpp"
#include "parser/statement/rule/declaration/const_declaration_statement_rule.hpp"
#include "parser/statement/rule/declaration/var_declaration_statement_rule.hpp"

#include "parser/statement/rule/enum/enum_declaration_statement_rule.hpp"

#include "parser/statement/rule/expression/expression_statement_rule.hpp"

#include "parser/statement/rule/function/function_statement_rule.hpp"

#include "parser/statement/rule/loop/continue_statement_rule.hpp"
#include "parser/statement/rule/loop/do_while_loop_statement_rule.hpp"
#include "parser/statement/rule/loop/for_loop_statement_rule.hpp"
#include "parser/statement/rule/loop/while_loop_statement_rule.hpp"

#include "parser/statement/rule/oop/interface_declaration_rule.hpp"
#include "parser/statement/rule/oop/class_declaration_rule.hpp"

#include "parser/statement/rule/switch/switch_statement_rule.hpp"

#include "parser/statement/rule/try_catch_finally/try_catch_finally_statement_rule.hpp"

StatementRuleVector FStatementRuleFactory::CreateRules()
{
    StatementRuleVector rules;

    // Block statement rule
    rules.push_back(std::make_unique<FBlockStatementRule>());

    // Control flow statement rule
    rules.push_back(std::make_unique<FReturnStatementRule>());

    // Conditional statement rule
    rules.push_back(std::make_unique<FConditionalStatementRule>());

    // Function statement rule
    rules.push_back(std::make_unique<FFunctionStatementRule>());

    // Enum declaration statement rule
    rules.push_back(std::make_unique<FEnumDeclarationStatementRule>());

    // Declaration statement rule
    rules.push_back(std::make_unique<FConstDeclarationStatementRule>());
    rules.push_back(std::make_unique<FVarDeclarationStatementRule>());

    // Loop statement rule
    rules.push_back(std::make_unique<FContinueStatementRule>());
    rules.push_back(std::make_unique<FDoWhileLoopStatementRule>());
    // rules.push_back(std::make_unique<FForLoopStatementRule>());
    rules.push_back(std::make_unique<FWhileLoopStatementRule>());

    // OOP statement rule
    rules.push_back(std::make_unique<FInterfaceDeclarationRule>());
    rules.push_back(std::make_unique<FClassDeclarationRule>());

    // Switch statement rule
    rules.push_back(std::make_unique<FSwitchStatementRule>());

    // Try Catch Finally statement rule
    rules.push_back(std::make_unique<FTryCatchFinallyStatementRule>());

    // Expression statement rule
    rules.push_back(std::make_unique<FExpressionStatementRule>());

    return rules;
}
