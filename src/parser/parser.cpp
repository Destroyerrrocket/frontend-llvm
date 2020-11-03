#include "parser.hpp"

#include "AST/binaryexpr.hpp"
#include <array>

namespace Parser
{

void LexerBuffer::getNextToken()
{
	auto &&result = lexer.getToken();
	if (result.report) {
		std::cerr << result.report->toString() << std::endl;
		if (result.report->severity == Report::Severity::Error)
			throw std::exception();
	}
	if (!result.token)
		return getNextToken();
	tokens.push_back(std::move(result));
}

std::vector<std::unique_ptr<AST::Expr>> Parser::createAST()
{
	std::vector<std::unique_ptr<AST::Expr>> data;
	if (lexerBuff.tokens.empty())
		lexerBuff.getNextToken();
	;
	while (true) {
		switch (currentToken().token->kind) {
		case Lex::TokenKind::Eof:
			return data;
		case Lex::TokenKind::Semi: // ignore top-level semicolons.
			getNextToken();
			break;
		default:
			globalExpr();
		}
	}
}

}