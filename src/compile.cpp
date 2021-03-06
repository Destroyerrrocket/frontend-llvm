#include "compile.hpp"
#include "lexer/lexer.hpp"
#include "lexer/tokens/tokenidentifier.hpp"
#include "lexer/tokens/tokenkind.hpp"
#include "lexer/tokens/tokenliteral.hpp"
#include "parser/parser.hpp"
#include "parser/AST/expr.hpp"

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
	auto [v,e] = d->parser->createAST();
	for (auto &&ast : v) {
		if (ast)
			ast->print();
		else
			std::cerr << "Found null in ast structure!" << std::endl;
	}
	for (auto &&err : e) {
		if (err) {
			std::cerr << int(err->severity) << err->message << std::endl;
			std::cerr << err->toString() << std::endl;
		} else
			std::cerr << "Found null in reports!" << std::endl;
	}
}
}