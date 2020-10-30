#include "report.hpp"

namespace Report
{
const char *Error::getColor() const
{
	return "\033[1;31m";
}

const char *Warning::getColor() const
{
	return "\033[1;33m";
}

const char *Message::getColor() const
{
	return "\033[1;34m";
}
}