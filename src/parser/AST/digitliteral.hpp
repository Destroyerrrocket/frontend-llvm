#pragma once

#include "expr.hpp"
#include <cstdint>

namespace AST
{

class LiteralKind : public Expr
{
public:
	enum class Kind : uint32_t
	{
		k_Custom,
		k_int,
		k_float,
	} kind;
	LiteralKind() = delete;
	explicit LiteralKind(Kind k) : kind(k) {}
	~LiteralKind() override = default;
};

template<class T>
struct LiteralKindFromType {LiteralKind::Kind value = LiteralKind::Kind::k_Custom;};
template<> struct LiteralKindFromType<int32_t> {LiteralKind::Kind value = LiteralKind::Kind::k_int;};
template<> struct LiteralKindFromType<float> {LiteralKind::Kind value = LiteralKind::Kind::k_float;};
template<class T>
using LiteralKindFromType_v = typename LiteralKindFromType<T>::value;

template<class T>
class Literal : public LiteralKind
{
	T literal;
public:
	Literal(T data) : literal(data), LiteralKind(LiteralKindFromType_v<T>()) {}
};

class IntLiteral : public Literal<int32_t>
{
	using Literal<int32_t>::Literal;
};

class FloatLiteral : public Literal<float>
{
	using Literal<float>::Literal;
};

}