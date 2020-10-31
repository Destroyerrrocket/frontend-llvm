#include "attemptsymbol.hpp"

#include "algorithm"
#include "lexer/struct.hpp"
#include "lexer/tokens/tokenliteral.hpp"

using namespace std::string_literals;

namespace Lex
{

Lexer::ResultToken AttempterSymbol::attempt() const
{
	auto &lastChar = this->lexerState.currentChar;
	auto readByte = [&]() {return this->lexerState.readByte();};
	auto aSymbol = [](char lastChar) -> bool {
		const auto *known = std::ranges::find(suportedSymbols, lastChar);
		return known != suportedSymbols.end();
	};
	if (aSymbol(lastChar)) {
		std::string symbolRead;
		auto hasCandidates = [&symbolRead]()-> const std::pair<const char *, Lex::TokenKind>* {
			for (const auto &syntaxCandidate : syntaxList) {
				if (std::string_view(syntaxCandidate.first).starts_with(symbolRead)) {
					return &syntaxCandidate;
				}
			}
			return nullptr;
		};

		do {
			symbolRead += lastChar;
			if (!hasCandidates())
				break;
			lastChar = readByte();
		} while((aSymbol(lastChar)));

		std::string_view symbol(symbolRead.begin(), symbolRead.end()-(aSymbol(lastChar) ? 1 : 0));
		const auto *known = std::ranges::find(syntaxList, symbol, [](auto &&e) {return std::string_view(e.first);});
		if (known == syntaxList.end()) {
			return lexerState.createReport<Report::Error>("Invalid symbol '"s + std::string(symbol) + "'");
		}
		return makeTokenPtr(known->second);
	}
	return {};
}

}