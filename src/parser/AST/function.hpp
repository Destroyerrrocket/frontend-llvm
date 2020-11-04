#pragma once

#include "type.hpp"
#include "variable.hpp"

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
	std::string print() const override
	{
		auto str = identifier;
		for (int i = 0; const auto &arg : args)
			str += arg->print() + (i == args.size()-1 ? ")" : ", ");
		return str;
	}
};

class FunctionPrototype : public Expr
{
public:
	using Args = std::vector<std::unique_ptr<Argument>>;
private:
	std::unique_ptr<Type> returnType;
	std::string identifier;
	Args args;

public:
	FunctionPrototype(std::unique_ptr<Type> &&returnType, std::string identifier, Args &&args)
		: returnType(std::move(returnType)), identifier(std::move(identifier)), args(std::move(args)) {}

	const std::string &getName() const { return identifier; }
	std::string print() const override
	{
		auto str = returnType->print() + " " + identifier + " (";
		for (int i = 0; const auto &arg : args)
			str += arg->print() + (i == args.size()-1 ? ")" : ", ");
		return str;
	}

};

class FunctionDefinition : public Expr
{
	std::unique_ptr<FunctionPrototype> proto;
	std::vector<std::unique_ptr<Expr>> body;

public:
	FunctionDefinition(std::unique_ptr<FunctionPrototype> &&proto, std::vector<std::unique_ptr<Expr>> &&body)
		: proto(std::move(proto)), body(std::move(body)) {}
	std::string print() const override
	{
		auto str = proto->print() + "\n{";
		for (int i = 0; const auto &b : body)
			str += b->print() + (i == body.size()-1 ? "\n}" : ";\n");
		return str;
	}
};

}