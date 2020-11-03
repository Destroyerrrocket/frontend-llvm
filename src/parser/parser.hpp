#pragma once

#include "AST/expr.hpp"
#include "binop.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens/token.hpp"

#include <memory>
#include <vector>
#include <list>
#include <exception>

namespace Parser
{

struct LexerBuffer
{
	friend class Parser;
private:
	std::list<Lex::Lexer::ResultToken> tokens;
	Lex::Lexer lexer;
	auto &currentToken() const {return tokens.back();}
	void getNextToken();
};

class Parser
{
public:
	Parser(std::istream &file, const char *name);
	Parser() = delete;

	Parser(Parser&) = delete;
	Parser& operator=(Parser&) = delete;

	std::vector<std::unique_ptr<AST::Expr>> createAST();
private:
	std::unique_ptr<AST::Expr> number();
	std::unique_ptr<AST::Expr> parenthesis();
	std::unique_ptr<AST::Expr> identifier();
	std::unique_ptr<AST::Expr> expression();
	std::unique_ptr<AST::Expr> binOpRHS(Priority priorityPrecedent, std::unique_ptr<AST::Expr> &&);
	std::unique_ptr<AST::Expr> functionPrototype();
	std::unique_ptr<AST::Expr> functionDefinition();

	LexerBuffer lexerBuff;
	inline auto &currentToken() const {return lexerBuff.currentToken();}
	inline void getNextToken() {return lexerBuff.getNextToken();}
};

}