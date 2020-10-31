#include "attempter.hpp"
#include "lexer/lexer.hpp"

namespace Lex
{
class AttempterIdentifier : public Attempter
{
	using Attempter::Attempter;
	Lexer::ResultToken attempt() const override;
};

}