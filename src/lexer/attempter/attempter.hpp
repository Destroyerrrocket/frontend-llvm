#pragma once
#include "lexer/lexer.hpp"
#include "lexer/lexerstate.hpp"
#include "macro.h"
namespace Lex
{
class Attempter
{
public:
	Attempter(LexerState &state) : state(state) {}

	virtual Lexer::ResultToken attempt() const = 0;
protected:
	LexerState &state;
};

static std::vector<Attempter*> &getAttempters()
{
	static std::vector<Attempter*> attempters;
	return attempters;
}

struct RegisterAttempter
{
	RegisterAttempter(Attempter* a) {getAttempters().push_back(a);}
};
#define REGISTER_ATTEMPER2(attempter, line) \
	attempter COMB(at, line); \
	static RegisterAttempter COMB(reg, line) (attempter);
#define REGISTER_ATTEMPER(attempter) REGISTER_ATTEMPER2(attempter, __LINE__)

}
