#pragma once

#include "ast/interface/ast_visitor.hpp"

class IASTNode
{
public:

    virtual ~IASTNode() = default;

    virtual void Accept(const IASTVisitor& visitor) const = 0;

};
