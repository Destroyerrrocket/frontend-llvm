#include "compile.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens/tokenidentifier.hpp"
#include "lexer/tokens/tokenkind.hpp"
#include "lexer/tokens/tokenliteral.hpp"
#include "parser/parser.hpp"


#include <iostream>
#include <fstream>

namespace General
{

struct Compile::D
{
	std::ifstream input;
	std::unique_ptr<Lex::Lexer> lexer = nullptr;
	std::unique_ptr<Parser::Parser> parser;
	D(char *file) : input(file)
	{
		if (!input.good()) {
			std::cout << "File broken" << std::endl;
			abort();
		}
		lexer = std::make_unique<Lex::Lexer>(input, file);
		parser = std::make_unique<Parser::Parser>(*lexer);
	}
};


Compile::Compile(char *file) : d(std::make_unique<Compile::D>(file)) {}
Compile::~Compile() = default;

void Compile::compile()
{
	auto v = d->parser->createAST();
}
}