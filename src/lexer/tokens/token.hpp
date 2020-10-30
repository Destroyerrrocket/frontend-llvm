#pragma once
#include "tokenkind.hpp"

namespace Lex
{

struct Token
{
	Token(TokenKind kind) : kind(kind) {}
	virtual ~Token() = default;
	TokenKind kind;
};

template<TokenKind Kind>
struct GenericToken : public Token
{
	GenericToken() : Token{Kind} {}
	~GenericToken() override = default;
};

template<class U>
concept is_token = std::same_as<U, Token> || std::derived_from<U, Token>;
}