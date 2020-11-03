#pragma once

#include "type.hpp"
#include <string>
#include <memory>
#include <utility>
#include <vector>


namespace AST
{

class FunctionCall : public Expr
{
	std::string identifier;
	std::vector<std::unique_ptr<Expr>> args;
public:
	explicit FunctionCall(std::string identifier, std::vector<std::unique_ptr<Expr>> &&args) :
		identifier(std::move(identifier)), args(std::move(args)) {}
};

class FunctionPrototype : public Expr
{
	std::unique_ptr<Type> returnVal;
	std::string identifier;
	std::vector<std::unique_ptr<Type>> args;

public:
	FunctionPrototype(std::unique_ptr<Type> &&returnVal, std::string identifier, std::vector<std::unique_ptr<Type>> &&args)
		: returnVal(std::move(returnVal)), identifier(std::move(identifier)), args(std::move(args)) {}

	const std::string &getName() const { return identifier; }
};

class FunctionDefinition : public Expr
{
	std::unique_ptr<FunctionPrototype> proto;
	std::vector<std::unique_ptr<Expr>> body;

public:
	FunctionDefinition(std::unique_ptr<FunctionPrototype> &&proto, std::vector<std::unique_ptr<Expr>> &&body)
		: proto(std::move(proto)), body(std::move(body)) {}
};

}