#pragma once
#include "token.hpp"

namespace Lex
{

template<class T, TokenKind Literal>
struct TokenLiteral : public GenericToken<Literal>
{
	template<class U> requires std::convertible_to<U, T>
	TokenLiteral (U data) : literal(data) {}
	T literal;
};

struct TokenLiteralInteger : public TokenLiteral<int32_t, TokenKind::LiteralInteger>
{
	using TokenLiteral<int32_t, TokenKind::LiteralInteger>::TokenLiteral;
};
struct TokenLiteralFloat : public TokenLiteral<float, TokenKind::LiteralFloat>
{
	static_assert(sizeof(float) == 4, "Broken float");
	using TokenLiteral<float, TokenKind::LiteralFloat>::TokenLiteral;
};

}