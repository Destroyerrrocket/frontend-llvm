#include "lexer.hpp"

#include "struct.hpp"
#include "lexerstate.hpp"

#include "lexer/attempter/attempter.hpp"
#include "lexer/attempter/attemptidentifier.hpp"
#include "lexer/attempter/attemptdigitliteral.hpp"
#include "lexer/attempter/attemptsymbol.hpp"

#include "tokens/token.hpp"
#include "tokens/tokenidentifier.hpp"
#include "tokens/tokenliteral.hpp"

#include "report/report.hpp"
#include <cctype>
#include <cstdlib>
#include <istream>
#include <algorithm>
#include <memory>

using namespace std::string_literals;

namespace Lex
{

struct Lexer::D
{
	LexerState lexerState;
	std::vector<std::unique_ptr<Attempter>> attempters;
	template<class T>
	auto makeAttempter()->std::unique_ptr<Attempter> {return std::unique_ptr<Attempter>(new T(lexerState));}
	D(std::istream &file, const char *name) : lexerState(file, name)
	{
		attempters.push_back(makeAttempter<AttempterIdentifier>());
		attempters.push_back(makeAttempter<AttempterDigitLiteral>());
		attempters.push_back(makeAttempter<AttempterSymbol>());
	}
};

Lexer::Lexer(std::istream &file, const char *name) : d(std::make_unique<D>(file,name)) {}
Lexer::~Lexer() = default;

Lexer::ResultToken Lexer::getToken()
{
	auto &lexerState = d->lexerState;
	auto &lastChar = lexerState.currentChar;
	auto readByte = [&lexerState]() {return lexerState.readByte();};
	while (isspace(lastChar))
		lastChar = readByte();

	if (lastChar == '/') {
		if ((lastChar = readByte()) == '/') {
			lexerState.nextLine();
		} else if (lastChar == '*') {
			while (lastChar != EOF && lastChar != '/') {
				do lastChar = getchar();
				while (lastChar != EOF && lastChar != '*');
				lastChar = getchar();
			}
			if (lastChar != EOF)
				return getToken();
		} else {
			lastChar = lexerState.goBackByteOnLine();
		}
	}

	for (auto &attempter : d->attempters) {
		auto res = attempter->attempt();
		if (res.hasData())
			return res;
	}

	if (lastChar == EOF)
		return Attempter::makeTokenPtr(TokenKind::Eof);
	return lexerState.createReport<Report::Error>("Failed at char '"s + lastChar + "'");
}
}