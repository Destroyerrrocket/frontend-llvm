#pragma once
#include "token.hpp"

#include <string>

namespace Lex
{

struct TokenIdentifier : public GenericToken<TokenKind::Identifier>
{
	template <class T> requires std::convertible_to<T, std::string>
	TokenIdentifier(T data) : identifier(data) {}
	std::string identifier;
};

}