#include "parser.hpp"

#include "AST/binaryexpr.hpp"
#include "AST/function.hpp"
#include "lexer/tokens/tokenidentifier.hpp"
#include <array>

namespace Parser
{

template<class T, class ... Args> requires std::is_base_of_v<AST::Expr, T>
std::unique_ptr<T> makeAST(Args&& ... args)
{
	auto ast = std::make_unique<T>(std::forward<Args>(args) ...);
	std::cout << ast->print() << std::endl;
	return std::move(ast);
}

Parser::Parser(Lex::Lexer &lexer) : lexerBuff(lexer) {}

std::unique_ptr<Report::Report> LexerBuffer::getNextToken()
{
	auto &&result = lexer.getToken();
	return std::move(result.report);
	if (result.token)
		std::cout << "On token: " << Lex::tokenToStr.at(result.token->kind) << std::endl;
	tokens.push_back(std::move(result));
	return nullptr;
}

Parser::ASTResult Parser::createAST()
{
	std::vector<std::unique_ptr<AST::Expr>> data;
	std::vector<std::unique_ptr<Report::Report>> reports;
	if (lexerBuff.tokens.empty())
		getNextToken();

	while (true) {
		switch (currentToken().token->kind) {
		case Lex::TokenKind::Eof:
			return {data,{}};
		case Lex::TokenKind::Semi: // ignore top-level semicolons.
			getNextToken();
			break;
		default:
			if (auto g = global(); g)
				data.push_back(std::move(g));
			else {
				auto warn = std::make_unique<Report::Warning>();
				warn->location = lexerBuff.lexer.getSourceLocation();
				warn->message = "Unexpected value on AST generation";
				return {data, {std::move(warn)}};
			}
			break;
		}
	}
}

std::optional<AST::Type::Kind> Parser::getType() const
{
	switch (currentToken().token->kind) {
	case decltype(currentToken().token->kind)::Kw_int: return AST::Type::Kind::k_int;
	case decltype(currentToken().token->kind)::Kw_float: return AST::Type::Kind::k_float;
	default: return std::nullopt;
	}
}

bool Parser::isType() const
{
	return getType().has_value();
}

std::unique_ptr<AST::Type> Parser::typeParse()
{
	auto type = getType();
	if (!type.has_value()) {
		return nullptr;
	}
	if (getNextToken()) return nullptr;
	return makeAST<AST::Type>(type.value());
}

std::unique_ptr<AST::Expr> Parser::global()
{
	std::unique_ptr<AST::Type> kind = typeParse();
	if (!kind) return nullptr;
	if (currentToken().token->kind != Lex::TokenKind::Identifier) {
		return nullptr;
	}

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
	default: return nullptr;
	}
	return nullptr;
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
			args.push_back(makeAST<AST::Argument>(std::move(type), std::move(name)));
			getNextToken();
		}
	}
	getNextToken(); // )
	return makeAST<AST::FunctionPrototype>(std::move(type), std::move(name), std::move(args));
}

std::unique_ptr<AST::FunctionDefinition> Parser::functionDefinition(std::unique_ptr<AST::FunctionPrototype> &&prototype)
{
	getNextToken(); // {
	std::vector<std::unique_ptr<AST::Expr>> body;
	while (currentToken().token->kind != Lex::TokenKind::RBrace) {
		getNextToken();
	}
	return makeAST<AST::FunctionDefinition>(std::move(prototype), std::move(body));
}


}