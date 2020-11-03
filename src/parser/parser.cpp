#include "parser.hpp"

#include "AST/binaryexpr.hpp"
#include "lexer/tokens/tokenidentifier.hpp"
#include <array>

namespace Parser
{

Parser::Parser(Lex::Lexer &lexer) : lexerBuff(lexer) {}

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
			data.push_back(global());
		}
	}
}

std::unique_ptr<AST::Expr> Parser::global() {
	std::unique_ptr<AST::Type> kind;
	if (currentToken().token->kind == Lex::TokenKind::LiteralInteger)
		kind = std::make_unique<AST::Type>(AST::Type::Kind::k_int);
	else if (currentToken().token->kind == Lex::TokenKind::LiteralFloat)
		kind = std::make_unique<AST::Type>(AST::Type::Kind::k_int);
	else throw std::exception();
	getNextToken();
	if (currentToken().token->kind != Lex::TokenKind::Identifier)
		throw std::exception();

	auto identifier = dynamic_cast<Lex::TokenIdentifier&>(*currentToken().token).identifier;
	getNextToken();
	if (currentToken().token->kind == Lex::TokenKind::LParen) {
		auto functionPrototype = functionPrototype(std::move(kind), std::move(identifier));
	}

}

}