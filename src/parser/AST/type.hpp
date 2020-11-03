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
};

}
