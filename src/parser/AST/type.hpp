#pragma once

#include "expr.hpp"
#include <cstdint>

namespace AST
{

class Type : Expr
{
public:
	enum class Kind : uint32_t
	{
		k_Custom,
		k_int,
		k_float,
	};
	Type(Kind kind) : kind(kind) {}
	Kind kind;

	std::string print() const override {return kindToString(kind);}
private:
	static std::string kindToString(Kind kind)
	{
		switch (kind) {
		case Kind::k_Custom: return "CustomType";
		case Kind::k_int: return "int";
		case Kind::k_float: return "float";
		}
	}
};

}
