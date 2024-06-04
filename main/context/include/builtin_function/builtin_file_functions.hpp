#pragma once

#include "function/invokable_function.hpp"
#include <fstream>

class FBuiltinOpenFile : public FInvokableFunction
{
public:

    FBuiltinOpenFile(std::string name, FunctionParameters parameters);
    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

class FBuiltinReadFile : public FInvokableFunction
{
public:

    FBuiltinReadFile(std::string name, FunctionParameters parameters);
    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

class FBuiltinWriteFile : public FInvokableFunction
{
public:

    FBuiltinWriteFile(std::string name, FunctionParameters parameters);
    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

class FBuiltinCloseFile : public FInvokableFunction
{
public:

    FBuiltinCloseFile(std::string name, FunctionParameters parameters);
    Value Invoke(const std::vector<Value>& arguments, const FContext& context) const override;
};

std::shared_ptr<FInvokableFunction> CreateOpenFileFunction();
std::shared_ptr<FInvokableFunction> CreateReadFileFunction();
std::shared_ptr<FInvokableFunction> CreateWriteFileFunction();
std::shared_ptr<FInvokableFunction> CreateCloseFileFunction();
