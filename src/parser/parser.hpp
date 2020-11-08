#pragma once

#include "binop.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens/token.hpp"
#include "parser/AST/type.hpp"
#include "report/report.hpp"

#include <memory>
#include <vector>
#include <list>
#include <exception>

namespace AST
{
	class Expr;
	class FunctionPrototype;
	class FunctionDefinition;
}

namespace Parser
{

struct LexerBuffer
{
	friend class Parser;
private:
	LexerBuffer(Lex::Lexer &lexer) : lexer(lexer) {};
	std::list<Lex::Lexer::ResultToken> tokens;
	Lex::Lexer &lexer;
	auto &currentToken() const {return tokens.back();}
	std::unique_ptr<Report::Report> getNextToken();
};

class Parser
{
public:
	Parser(Lex::Lexer &lexer);
	Parser() = delete;

	Parser(Parser&) = delete;
	Parser& operator=(Parser&) = delete;

	using ASTResult = std::pair<std::vector<std::unique_ptr<AST::Expr>>,
		std::vector<std::unique_ptr<Report::Report>>>;

	ASTResult createAST();
private:
	std::optional<AST::Type::Kind> getType() const;
	bool isType() const;
	std::unique_ptr<AST::Type> typeParse();
	std::unique_ptr<AST::Expr> number();
	std::unique_ptr<AST::Expr> parenthesis();
	std::unique_ptr<AST::Expr> identifier();
	std::unique_ptr<AST::Expr> expression();
	std::unique_ptr<AST::Expr> binOpRHS(Priority priorityPrecedent, std::unique_ptr<AST::Expr> &&);
	std::unique_ptr<AST::FunctionPrototype> functionPrototype(std::unique_ptr<AST::Type> &&type, std::string &&name);
	std::unique_ptr<AST::FunctionDefinition> functionDefinition(std::unique_ptr<AST::FunctionPrototype> &&proto);
	std::unique_ptr<AST::Expr> global();

	LexerBuffer lexerBuff;
	inline auto &currentToken() const {return lexerBuff.currentToken();}
	inline auto getNextToken() {return lexerBuff.getNextToken();}
};

}