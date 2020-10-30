#pragma once
#include <array>
#include <cstdint>
#include <unordered_map>
#include "macro.h"
#define K(X) COMB(Kw_, X)
#define PAIR(X) std::pair{STR(X), TokenKind::K(X)}
#define TOK_TO_STR(X) {TokenKind::X, #X}
#define TOK_TO_STR_K(X) {TokenKind::K(X), #X}

#define TOK_TO_STR2(X, Y) {TokenKind::X, Y}

namespace Lex {

enum struct TokenKind : uint32_t {
	// Anotations
	Eof,

	// primary
	Identifier,
	LiteralInteger,
	LiteralFloat,

	// Syntax
	LSquare, // "["
	RSquare, // "]"
	LParen, // "("
	RParen, // ")"
	LBrace, // "{"
	RBrace, // "}"
	Period, // "."
	Amp, // "&"
	Ampamp, // "&&"
	Ampequal, // "&="
	Star, // "*"
	Starequal, // "*="
	Plus, // "+"
	Plusplus, // "++"
	Plusequal, // "+="
	Minus, // "-"
	Arrow, // "->"
	Minusminus, // "--"
	Minusequal, // "-="
	Tilde, // "~"
	Exclaim, // "!"
	Exclaimequal, // "!="
	Slash, // "/"
	Slashequal, // "/="
	Percent, // "%"
	Percentequal, // "%="
	Less, // "<"
	Lessless, // "<<"
	Lessequal, // "<="
	Lesslessequal, // "<<="
	Spaceship, // "<=>"
	Greater, // ">"
	Greatergreater, // ">>"
	Greaterequal, // ">="
	Greatergreaterequal, // ">>="
	Caret, // "^"
	Caretequal, // "^="
	Pipe, // "|"
	Pipepipe, // "||"
	Pipeequal, // "|="
	Question, // "?"
	Colon, // ":"
	Semi, // ";"
	Equal, // "="
	Equalequal, // "=="
	Comma, // ","
	Hash, // "#"
	Hashhash, // "##"
	Hashat, // "#@"

	// Keywords
	K(auto),
	K(break),
	K(case),
	K(char),
	K(const),
	K(continue),
	K(default),
	K(do),
	K(double),
	K(else),
	K(enum),
	K(extern),
	K(float),
	K(for),
	K(goto),
	K(if),
	K(inline),
	K(int),
	K(long),
	K(register),
	K(restrict),
	K(return),
	K(short),
	K(signed),
	K(sizeof),
	K(static),
	K(struct),
	K(switch),
	K(typedef),
	K(union),
	K(unsigned),
	K(void),
	K(volatile),
	K(while),
};

static const std::unordered_map<TokenKind, const char *> tokenToStr {{
	TOK_TO_STR2(Eof, "<EOF>"),
	TOK_TO_STR(Identifier),
	TOK_TO_STR(LiteralInteger),
	TOK_TO_STR(LiteralFloat),

	TOK_TO_STR2(LSquare, "["),
	TOK_TO_STR2(RSquare, "]"),
	TOK_TO_STR2(LParen, "("),
	TOK_TO_STR2(RParen, ")"),
	TOK_TO_STR2(LBrace, "{\n"),
	TOK_TO_STR2(RBrace, "}\n"),
	TOK_TO_STR2(Period, "."),
	TOK_TO_STR2(Amp, "&"),
	TOK_TO_STR2(Ampamp, "&&"),
	TOK_TO_STR2(Ampequal, "&="),
	TOK_TO_STR2(Star, "*"),
	TOK_TO_STR2(Starequal, "*="),
	TOK_TO_STR2(Plus, "+"),
	TOK_TO_STR2(Plusplus, "++"),
	TOK_TO_STR2(Plusequal, "+="),
	TOK_TO_STR2(Minus, "-"),
	TOK_TO_STR2(Arrow, "->"),
	TOK_TO_STR2(Minusminus, "--"),
	TOK_TO_STR2(Minusequal, "-="),
	TOK_TO_STR2(Tilde, "~"),
	TOK_TO_STR2(Exclaim, "!"),
	TOK_TO_STR2(Exclaimequal, "!="),
	TOK_TO_STR2(Slash, "/"),
	TOK_TO_STR2(Slashequal, "/="),
	TOK_TO_STR2(Percent, "%"),
	TOK_TO_STR2(Percentequal, "%="),
	TOK_TO_STR2(Less, "<"),
	TOK_TO_STR2(Lessless, "<<"),
	TOK_TO_STR2(Lessequal, "<="),
	TOK_TO_STR2(Lesslessequal, "<<="),
	TOK_TO_STR2(Spaceship, "<=>"),
	TOK_TO_STR2(Greater, ">"),
	TOK_TO_STR2(Greatergreater, ">>"),
	TOK_TO_STR2(Greaterequal, ">="),
	TOK_TO_STR2(Greatergreaterequal, ">>="),
	TOK_TO_STR2(Caret, "^"),
	TOK_TO_STR2(Caretequal, "^="),
	TOK_TO_STR2(Pipe, "|"),
	TOK_TO_STR2(Pipepipe, "||"),
	TOK_TO_STR2(Pipeequal, "|="),
	TOK_TO_STR2(Question, "?"),
	TOK_TO_STR2(Colon, ":"),
	TOK_TO_STR2(Semi, ";\n"),
	TOK_TO_STR2(Equal, "="),
	TOK_TO_STR2(Equalequal, "=="),
	TOK_TO_STR2(Comma, ","),
	TOK_TO_STR2(Hash, "#"),
	TOK_TO_STR2(Hashhash, "##"),
	TOK_TO_STR2(Hashat, "#@"),
	TOK_TO_STR_K(auto),
	TOK_TO_STR_K(break),
	TOK_TO_STR_K(case),
	TOK_TO_STR_K(char),
	TOK_TO_STR_K(const),
	TOK_TO_STR_K(continue),
	TOK_TO_STR_K(default),
	TOK_TO_STR_K(do),
	TOK_TO_STR_K(double),
	TOK_TO_STR_K(else),
	TOK_TO_STR_K(enum),
	TOK_TO_STR_K(extern),
	TOK_TO_STR_K(float),
	TOK_TO_STR_K(for),
	TOK_TO_STR_K(goto),
	TOK_TO_STR_K(if),
	TOK_TO_STR_K(inline),
	TOK_TO_STR_K(int),
	TOK_TO_STR_K(long),
	TOK_TO_STR_K(register),
	TOK_TO_STR_K(restrict),
	TOK_TO_STR_K(return),
	TOK_TO_STR_K(short),
	TOK_TO_STR_K(signed),
	TOK_TO_STR_K(sizeof),
	TOK_TO_STR_K(static),
	TOK_TO_STR_K(struct),
	TOK_TO_STR_K(switch),
	TOK_TO_STR_K(typedef),
	TOK_TO_STR_K(union),
	TOK_TO_STR_K(unsigned),
	TOK_TO_STR_K(void),
	TOK_TO_STR_K(volatile),
	TOK_TO_STR_K(while),
}};

static constexpr std::array syntaxList = {
	std::pair{"--", TokenKind::Minusminus},
	std::pair{"-", TokenKind::Minus},
	std::pair{"-=", TokenKind::Minusequal},
	std::pair{"->", TokenKind::Arrow},
	std::pair{",", TokenKind::Comma},
	std::pair{";", TokenKind::Semi},
	std::pair{":", TokenKind::Colon},
	std::pair{"!", TokenKind::Exclaim},
	std::pair{"!=", TokenKind::Exclaimequal},
	std::pair{"?", TokenKind::Question},
	std::pair{".", TokenKind::Period},
	std::pair{"(", TokenKind::LParen},
	std::pair{")", TokenKind::RParen},
	std::pair{"[", TokenKind::LSquare},
	std::pair{"]", TokenKind::RSquare},
	std::pair{"{", TokenKind::LBrace},
	std::pair{"}", TokenKind::RBrace},
	std::pair{"*", TokenKind::Star},
	std::pair{"*=", TokenKind::Starequal},
	std::pair{"/", TokenKind::Slash},
	std::pair{"/=", TokenKind::Slashequal},
	std::pair{"&", TokenKind::Amp},
	std::pair{"&&", TokenKind::Ampamp},
	std::pair{"&=", TokenKind::Ampequal},
	std::pair{"#", TokenKind::Hash},
	std::pair{"#@", TokenKind::Hashat},
	std::pair{"##", TokenKind::Hashhash},
	std::pair{"%", TokenKind::Percent},
	std::pair{"%=", TokenKind::Percentequal},
	std::pair{"^", TokenKind::Caret},
	std::pair{"^=", TokenKind::Caretequal},
	std::pair{"+", TokenKind::Plus},
	std::pair{"++", TokenKind::Plusplus},
	std::pair{"+=", TokenKind::Plusequal},
	std::pair{"<", TokenKind::Less},
	std::pair{"<<", TokenKind::Lessless},
	std::pair{"<<=", TokenKind::Lesslessequal},
	std::pair{"<=", TokenKind::Lessequal},
	std::pair{"<=>", TokenKind::Spaceship},
	std::pair{"=", TokenKind::Equal},
	std::pair{"==", TokenKind::Equalequal},
	std::pair{">", TokenKind::Greater},
	std::pair{">=", TokenKind::Greaterequal},
	std::pair{">>", TokenKind::Greatergreater},
	std::pair{">>=", TokenKind::Greatergreaterequal},
	std::pair{"|", TokenKind::Pipe},
	std::pair{"|=", TokenKind::Pipeequal},
	std::pair{"||", TokenKind::Pipepipe},
	std::pair{"~", TokenKind::Tilde},
};

static constexpr std::array knownKeywords = {
	PAIR(auto),
	PAIR(break),
	PAIR(case),
	PAIR(char),
	PAIR(const),
	PAIR(continue),
	PAIR(default),
	PAIR(do),
	PAIR(double),
	PAIR(else),
	PAIR(enum),
	PAIR(extern),
	PAIR(float),
	PAIR(for),
	PAIR(goto),
	PAIR(if),
	PAIR(inline),
	PAIR(int),
	PAIR(long),
	PAIR(register),
	PAIR(restrict),
	PAIR(return),
	PAIR(short),
	PAIR(signed),
	PAIR(sizeof),
	PAIR(static),
	PAIR(struct),
	PAIR(switch),
	PAIR(typedef),
	PAIR(union),
	PAIR(unsigned),
	PAIR(void),
	PAIR(volatile),
	PAIR(while),
};

static constexpr std::array supportedKeywords = {
	PAIR(float),
	PAIR(int),
	PAIR(return),
};

}
#undef K
#undef PAIR