#include "attemptidentifier.hpp"
#include "lexer/tokens/tokenidentifier.hpp"

#include <algorithm>

using namespace std::string_literals;

namespace Lex
{

Lexer::ResultToken AttempterIdentifier::attempt() const
{
	auto &lastChar = this->lexerState.currentChar;
	auto readByte = [&]() {return this->lexerState.readByte();};
	if (isalpha(lastChar) || lastChar == '_') { // identifier: [_a-zA-Z][a-zA-Z0-9]*
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
	return {};
}

}