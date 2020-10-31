#pragma once
#include "lexer/lexer.hpp"
#include "lexer/lexerstate.hpp"
#include "macro.h"
namespace Lex
{
class Attempter
{
public:
	Attempter(LexerState &state) : lexerState(state) {}
	virtual ~Attempter() = default;
	template<is_token T = Token, class ... Args>
	static std::unique_ptr<Token> makeTokenPtr(auto ... args)
	{
		auto *tokenSpecialized = new T(args ...);
		auto *tokenGeneric = dynamic_cast<Token*>(tokenSpecialized);
		if (!tokenGeneric) {
			std::cout << "FATAL ERROR: Generic token broken" << std::endl;
			abort();
		}
		return std::unique_ptr<Token>(tokenGeneric);
	}

	virtual Lexer::ResultToken attempt() const = 0;
protected:
	LexerState &lexerState;
};

}
