#include "lexer.hpp"
#include "struct.hpp"
#include "lexerstate.hpp"

#include "tokens/token.hpp"
#include "tokens/tokenidentifier.hpp"
#include "tokens/tokenliteral.hpp"

#include "report/report.hpp"
#include <bits/ranges_algo.h>
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
	D(std::istream &file, const char *name) : lexerState(file, name) {}
};
Lexer::Lexer(std::istream &file, const char *name) : d(std::make_unique<D>(file,name)) {}
Lexer::~Lexer() = default;

template<is_token T = Token, class ... Args>
std::unique_ptr<Token> makeTokenPtr(auto ... args)
{
	auto *tokenSpecialized = new T(args ...);
	auto *tokenGeneric = dynamic_cast<Token*>(tokenSpecialized);
	if (!tokenGeneric) {
		std::cout << "FATAL ERROR: Generic token broken" << std::endl;
		abort();
	}
	return std::unique_ptr<Token>(tokenGeneric);
}

Lexer::ResultToken Lexer::getToken()
{
	auto &lexerState = d->lexerState;
	auto &lastChar = lexerState.currentChar;
	auto readByte = [&lexerState]() {return lexerState.readByte();};
	while (isspace(lastChar))
		lastChar = readByte();

	if (isalpha(lastChar)) { // identifier: [a-zA-Z][a-zA-Z0-9]*
		std::string identifier(1,lastChar);
		while (isalnum((lastChar = readByte())))
			identifier += lastChar;

		const auto *known = std::ranges::lower_bound(knownKeywords, identifier, {}, [](auto &&e) {return e.first;});
		if (known != knownKeywords.end() && known->first == identifier) {
			const auto *supported = std::ranges::lower_bound(supportedKeywords, identifier, {}, [](auto &&e) {return e.first;});
			if (supported != supportedKeywords.end() && supported->second == known->second)
				return makeTokenPtr(supported->second);
			auto warning = lexerState.createReport<Report::Warning>("The identifier: "s + identifier + " is not supported!");
			return {makeTokenPtr(supported->second), std::move(warning)};
		}

		return makeTokenPtr<TokenIdentifier>(identifier);
	}

	if (isdigit(lastChar) || lastChar == '.') {
		std::string possibleNumber;
		bool isAlreadyFloating = lastChar == '.';
		if (isAlreadyFloating) {
			if (!isdigit(lastChar = readByte()))
				return makeTokenPtr(TokenKind::Period);
			possibleNumber += '.';
		}
		do {
			possibleNumber += lastChar;
			if (lastChar = readByte(); lastChar == '.') {
				if (isAlreadyFloating) {
					return lexerState.createReport<Report::Error>("Invalid suffix '"s + lastChar + "' on floating constant");
				}
				isAlreadyFloating = true;
			}
		} while (isdigit(lastChar) || lastChar == '.');
		if (isAlreadyFloating)
			return makeTokenPtr<TokenLiteralFloat>(stof(possibleNumber));
		return makeTokenPtr<TokenLiteralInteger>(stoi(possibleNumber));
	}

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
	if (lastChar == EOF)
		return makeTokenPtr(TokenKind::Eof);


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
	return lexerState.createReport<Report::Error>("Failed at char '"s + lastChar + "'");
}
}