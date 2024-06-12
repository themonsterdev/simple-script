#pragma once

#include "parser/statement/interface/statement_rule.hpp"

class FStatementRuleFactory final
{
public:

    static StatementRuleVector CreateRules();
};
