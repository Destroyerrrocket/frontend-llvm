#include "attemptdigitliteral.hpp"

#include "algorithm"
#include "lexer/tokens/tokenliteral.hpp"

using namespace std::string_literals;

namespace Lex
{

Lexer::ResultToken AttempterDigitLiteral::attempt() const
{
	auto &lastChar = this->lexerState.currentChar;
	auto readByte = [&]() {return this->lexerState.readByte();};
	if (isdigit(lastChar) || lastChar == '.') {
		std::string possibleNumber;
		bool isAlreadyFloating = lastChar == '.';
		if (isAlreadyFloating) {
			if (!isdigit(lastChar = readByte())) {
				lexerState.goBackByteOnLine();
				return {};
			}
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
	return {};
}

}