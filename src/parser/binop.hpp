#pragma once

#include "lexer/tokens/tokenkind.hpp"

#include <cstdint>
#include <array>

namespace Parser
{

enum class BinaryOp : uint32_t {
	Multiply,
	Divide,
	Module,
	Add,
	Subtract,
	BitShiftLeft,
	BitShiftRight,
	CompLess,
	CompGreater,
	CompLessEqual,
	CompGreaterEqual,
	CompEqual,
	CompInequal,
	BitAnd,
	BitXor,
	BitOr,
	LogAnd,
	LogOr,

	Assign,
	AssignMultiply,
	AssignDivide,
	AssignModule,
	AssignAdd,
	AssignSubtract,
	AssignShiftLeft,
	AssignShiftRight,
	AssignAnd,
	AssignXor,
	AssignOr,
	END,
};

enum class Associativity : uint32_t {
	LtR,
	RtL,
};

using Priority = std::pair<int, Associativity>;

constexpr std::array<Priority, static_cast<uint32_t>(BinaryOp::END)> priorityOperators {{
	{0, Associativity::LtR},
	{0, Associativity::LtR},
	{0, Associativity::LtR},
	{1, Associativity::LtR},
	{1, Associativity::LtR},
	{2, Associativity::LtR},
	{2, Associativity::LtR},
	{3, Associativity::LtR},
	{3, Associativity::LtR},
	{3, Associativity::LtR},
	{3, Associativity::LtR},
	{4, Associativity::LtR},
	{4, Associativity::LtR},
	{5, Associativity::LtR},
	{6, Associativity::LtR},
	{7, Associativity::LtR},
	{8, Associativity::LtR},
	{9, Associativity::LtR},

	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
	{10, Associativity::RtL},
}};

constexpr BinaryOp TokenToBinaryOp(Lex::TokenKind tok)
{
	switch (tok) {
	case Lex::TokenKind::Minus: return BinaryOp::Subtract;
	case Lex::TokenKind::Exclaimequal: return BinaryOp::CompInequal;
	case Lex::TokenKind::Star: return BinaryOp::Multiply;
	case Lex::TokenKind::Slash: return BinaryOp::Divide;
	case Lex::TokenKind::Amp: return BinaryOp::BitAnd;
	case Lex::TokenKind::Ampamp: return BinaryOp::LogAnd;
	case Lex::TokenKind::Percent: return BinaryOp::Module;
	case Lex::TokenKind::Caret: return BinaryOp::BitXor;
	case Lex::TokenKind::Plus: return BinaryOp::Add;
	case Lex::TokenKind::Less: return BinaryOp::CompLess;
	case Lex::TokenKind::Lessless: return BinaryOp::BitShiftLeft;
	case Lex::TokenKind::Lessequal: return BinaryOp::CompLessEqual;
	case Lex::TokenKind::Equalequal: return BinaryOp::CompEqual;
	case Lex::TokenKind::Greater: return BinaryOp::CompGreater;
	case Lex::TokenKind::Greaterequal: return BinaryOp::CompGreaterEqual;
	case Lex::TokenKind::Greatergreater: return BinaryOp::BitShiftRight;
	case Lex::TokenKind::Pipe: return BinaryOp::BitOr;
	case Lex::TokenKind::Pipepipe: return BinaryOp::LogOr;
	case Lex::TokenKind::Equal: return BinaryOp::Assign;
	case Lex::TokenKind::Minusequal: return BinaryOp::AssignSubtract;
	case Lex::TokenKind::Starequal: return BinaryOp::AssignMultiply;
	case Lex::TokenKind::Slashequal: return BinaryOp::AssignDivide;
	case Lex::TokenKind::Ampequal: return BinaryOp::AssignAnd;
	case Lex::TokenKind::Percentequal: return BinaryOp::AssignModule;
	case Lex::TokenKind::Caretequal: return BinaryOp::AssignXor;
	case Lex::TokenKind::Plusequal: return BinaryOp::AssignAdd;
	case Lex::TokenKind::Lesslessequal: return BinaryOp::AssignShiftLeft;
	case Lex::TokenKind::Greatergreaterequal: return BinaryOp::AssignShiftRight;
	case Lex::TokenKind::Pipeequal: return BinaryOp::AssignOr;
	default: return BinaryOp::END;
	}
}

}