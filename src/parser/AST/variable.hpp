#include "expr.hpp"

#include "type.hpp"
#include <string>
#include <memory>
#include <utility>
namespace AST
{

class Variable : public Expr
{
	std::string name;
	std::unique_ptr<Type> type;
public:
	Variable(std::unique_ptr<Type> type, std::string name) : type(std::move(type)), name(std::move(name)) {}
	std::string print() const override {return type->print() + " " + name;}
};

struct ExternalVariable : public Variable {using Variable::Variable;};
struct InternalVariable : public Variable {using Variable::Variable;};
struct Argument : public Variable {using Variable::Variable;};

}