#include "compile.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens/tokenidentifier.hpp"
#include "lexer/tokens/tokenkind.hpp"
#include "lexer/tokens/tokenliteral.hpp"


#include <iostream>
#include <fstream>

namespace General
{

struct Compile::D
{
	std::ifstream input;
	std::unique_ptr<Lex::Lexer> lexer = nullptr;
	D(char *file) : input(file)
	{
		if (!input.good()) {
			std::cout << "File broken" << std::endl;
			abort();
		}
		lexer = std::make_unique<Lex::Lexer>(input, file);
	}
};


Compile::Compile(char *file) : d(std::make_unique<Compile::D>(file)) {}
Compile::~Compile() = default;

void Compile::compile()
{
	while(true) {
		auto [tok, report] = d->lexer->getToken();
		if (report) {
			std::cerr << report->toString() << std::endl;
			if (report->severity == Report::Severity::Error)
				return;
		}
		if (tok) {
			switch (tok->kind) {
			default: std::cerr << Lex::tokenToStr.at(tok->kind) << ' ';
				break;
			case Lex::TokenKind::Eof: std::cerr << "GOT: " << Lex::tokenToStr.at(tok->kind) << std::endl;
				return;
			case Lex::TokenKind::Identifier: std::cerr << dynamic_cast<Lex::TokenIdentifier*>(tok.get())->identifier << ' ';
				break;
			case Lex::TokenKind::LiteralInteger: std::cerr << dynamic_cast<Lex::TokenLiteralInteger*>(tok.get())->literal << ' ';
				break;
			}
		}

	}
}
}