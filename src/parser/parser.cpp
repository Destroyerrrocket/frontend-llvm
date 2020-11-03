#include "parser.hpp"

#include "AST/binaryexpr.hpp"
#include "AST/function.hpp"
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

std::optional<AST::Type::Kind> Parser::getType() const {
	switch (currentToken().token->kind) {
		case decltype(currentToken().token->kind)::Kw_int: return AST::Type::Kind::k_int;
		case decltype(currentToken().token->kind)::Kw_float: return AST::Type::Kind::k_float;
		default: return std::nullopt;
	}
}

bool Parser::isType() const {
	return getType().has_value();
}

std::unique_ptr<AST::Type> Parser::typeParse() {
	auto type = getType();
	if (!type.has_value())
		throw std::exception();
	getNextToken();
	return std::make_unique<AST::Type>(type.value());
}

std::unique_ptr<AST::Expr> Parser::global() {
	std::unique_ptr<AST::Type> kind = typeParse();

	std::cout <<  Lex::tokenToStr.at(currentToken().token->kind) << std::endl;
	if (currentToken().token->kind != Lex::TokenKind::Identifier)
		throw std::exception();


	auto identifier = dynamic_cast<Lex::TokenIdentifier&>(*currentToken().token).identifier;
	getNextToken();
	switch(currentToken().token->kind) {
	case Lex::TokenKind::LParen: {
		auto prototype = functionPrototype(std::move(kind), std::move(identifier));
		if (currentToken().token->kind == Lex::TokenKind::LBrace)
			return functionDefinition(std::move(prototype));
		if (currentToken().token->kind == Lex::TokenKind::Semi)
			return std::unique_ptr<AST::Expr>(prototype.release());
		}
	case Lex::TokenKind::Semi: // external variable, abort for now.
	case Lex::TokenKind::Equal:
	default:;
	}
	throw std::exception();
}

std::unique_ptr<AST::FunctionPrototype> Parser::functionPrototype(std::unique_ptr<AST::Type> &&type, std::string &&name)
{
	getNextToken(); // (
	AST::FunctionPrototype::Args args;
	while (currentToken().token->kind != Lex::TokenKind::RParen) {
		auto type = typeParse();
		std::string name;
		if (currentToken().token->kind == Lex::TokenKind::Identifier) {
			name = dynamic_cast<Lex::TokenIdentifier&>(*currentToken().token).identifier;
			args.push_back(std::make_unique<AST::Argument>(std::move(type), std::move(name)));
			getNextToken();
		}
	}
	getNextToken(); // )
	return std::make_unique<AST::FunctionPrototype>(std::move(type), std::move(name), std::move(args));
}

std::unique_ptr<AST::FunctionDefinition> Parser::functionDefinition(std::unique_ptr<AST::FunctionPrototype> &&prototype) {
	getNextToken(); // {
	std::vector<std::unique_ptr<AST::Expr>> body;
	while (currentToken().token->kind != Lex::TokenKind::RBrace) {
		getNextToken();
	}
	return std::make_unique<AST::FunctionDefinition>(std::move(prototype), std::move(body));
}


}