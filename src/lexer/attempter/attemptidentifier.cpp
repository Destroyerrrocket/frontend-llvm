#include "attempter.hpp"
#include "lexer/lexer.hpp"

namespace Lex
{
class IdentifierAttempter : Attempter
{
	using Attempter::Attempter;
	Lexer::ResultToken attempt() const override
	{
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
	}
};

}