#pragma once

#include "report/report.hpp"
#include "tokens/token.hpp"

#include <memory>
#include <vector>

namespace Lex
{

class Lexer
{
public:
	explicit Lexer(std::istream &file, const char *name);
	Lexer() = delete;
	~Lexer();

	Lexer(Lexer&) = delete;
	Lexer& operator=(Lexer&) = delete;

	struct ResultToken
	{
		inline ResultToken() = default;
		inline ResultToken(std::unique_ptr<Token> &&token) : token(std::move(token)) {}
		inline ResultToken(std::unique_ptr<Report::Report> &&report) : report(std::move(report)) {}
		inline ResultToken(std::unique_ptr<Token> &&token, std::unique_ptr<Report::Report> &&report) :
			token(std::move(token)), report(std::move(report)) {}
		inline bool hasData() const {return token || report;}
		std::unique_ptr<Token> token;
		std::unique_ptr<Report::Report> report;
	};
	ResultToken getToken();
private:
	struct D;
	std::unique_ptr<D> d;
};

}