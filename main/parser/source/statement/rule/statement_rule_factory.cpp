#include "statement/rule/statement_rule_factory.hpp"

#include "statement/rule/block/block_statement_rule.hpp"
#include "statement/rule/conditional/conditional_statement_rule.hpp"

#include "statement/rule/declaration/assignment_statement_rule.hpp"
#include "statement/rule/declaration/const_declaration_statement_rule.hpp"
#include "statement/rule/declaration/var_declaration_statement_rule.hpp"

#include "statement/rule/loop/do_while_loop_statement_rule.hpp"
#include "statement/rule/loop/for_loop_statement_rule.hpp"
#include "statement/rule/loop/while_loop_statement_rule.hpp"

#include "statement/rule/print/print_statement_rule.hpp"

StatementRuleVector FStatementRuleFactory::CreateRules()
{
    StatementRuleVector rules;

    // Block statement rule
    rules.push_back(std::make_unique<FBlockStatementRule>());

    // Conditional statement rule
    rules.push_back(std::make_unique<FConditionalStatementRule>());

    // Declaration statement rule
    rules.push_back(std::make_unique<FAssignmentStatementRule>());
    rules.push_back(std::make_unique<FConstDeclarationStatementRule>());
    rules.push_back(std::make_unique<FVarDeclarationStatementRule>());

    // Loop statement rule
    rules.push_back(std::make_unique<FDoWhileLoopStatementRule>());
    // rules.push_back(std::make_unique<FForLoopStatementRule>());
    rules.push_back(std::make_unique<FWhileLoopStatementRule>());

    // Print statement rule
    rules.push_back(std::make_unique<FPrintStatementRule>());

    return rules;
}
