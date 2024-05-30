#pragma once

#include "statement/interface/statement_rule.hpp"

class FStatementRuleFactory final
{
public:

    static StatementRuleVector CreateRules();
};
