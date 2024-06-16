#pragma once

class IStatement;
class IExpression;

class IASTVisitor
{
public:

    virtual void Visit(const IStatement& statement) const  = 0;
    virtual void Visit(const IExpression& expression) const = 0;

};
