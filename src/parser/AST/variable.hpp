#include "expr.hpp"

#include "type.hpp"
#include <string>
#include <memory>
#include <utility>
namespace AST
{

class VariableExpr : public Expr
{
	std::string name;
	std::unique_ptr<Type> type;
public:
	VariableExpr(std::unique_ptr<Type> type, std::string name) : type(std::move(type)), name(std::move(name)) {}
};

}