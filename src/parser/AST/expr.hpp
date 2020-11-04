#pragma once

#include <iostream>

namespace AST
{
struct Expr
{
	virtual ~Expr() = default;
	virtual std::string print() const = 0;
};

}