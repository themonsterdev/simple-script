#include "statement/rule/statement_rule_factory.hpp"

#include "statement/rule/assignment_statement_rule.hpp"
#include "statement/rule/const_declaration_statement_rule.hpp"
#include "statement/rule/print_statement_rule.hpp"
#include "statement/rule/var_declaration_statement_rule.hpp"

StatementRuleVector FStatementRuleFactory::CreateRules()
{
    StatementRuleVector rules;

    // Register statement rules
    rules.push_back(std::make_unique<FAssignmentStatementRule>());
    rules.push_back(std::make_unique<FConstDeclarationStatementRule>());
    rules.push_back(std::make_unique<FPrintStatementRule>());
    rules.push_back(std::make_unique<FVarDeclarationStatementRule>());

    return rules;
}
