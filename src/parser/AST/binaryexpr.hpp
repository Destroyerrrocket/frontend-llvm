#pragma once

#include "parser/binop.hpp"
#include "type.hpp"
#include <memory>
#include <utility>

namespace AST
{

class BinaryExpr : public Expr
{
	Parser::BinaryOp op;
	std::unique_ptr<Expr> LHS;
	std::unique_ptr<Expr> RHS;
public:
	explicit BinaryExpr(Parser::BinaryOp op, std::unique_ptr<Expr> LHS, std::unique_ptr<Expr> RHS) :
		op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
};

}