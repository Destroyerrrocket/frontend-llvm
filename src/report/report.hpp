#pragma once

#include <array>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include "macro.h"
#define PAIR(X) std::pair{Severity::X, STR(X)}

namespace Report
{

enum class Severity {
	Error,
	Message,
	Warning,
};

static constexpr std::array severityStringList{
	PAIR(Error),
	PAIR(Message),
	PAIR(Warning),
};
constexpr const char *severityString(Severity s)
{
	for (auto &&e : severityStringList)
		if (e.first == s)
			return e.second;
	return "";
}

struct Report
{
	Report(Severity s) : severity(s) {}
	virtual ~Report() = default;
	Severity severity;
	std::string filePath;
	unsigned row;
	unsigned column;
	unsigned size;
	std::string line;
	std::string message;
	virtual std::string toString() const = 0;

};

template<Severity S>
struct GenericReport : public Report
{
	GenericReport() : Report{S} {}
	~GenericReport() override = default;
	std::string toString() const override
	{
		std::stringstream strstream;
		strstream << filePath << ':' << row << ':' << column << ": ";
		strstream << getColor() << severityString(S) << "\033[0m: ";
		strstream << message << std::endl;
		strstream << line << std::endl;
		std::streamsize origWidth = strstream.width(column+size);
		strstream << std::right << '^' << std::string(size-1, '~');
		strstream.width(origWidth);
		return strstream.str();
	}
	virtual const char *getColor() const = 0;
};

struct Error : GenericReport<Severity::Error>
{
	const char * getColor() const override;
	~Error() override = default;
};

struct Warning : GenericReport<Severity::Warning>
{
	const char * getColor() const override;
	~Warning() override = default;
};

struct Message : GenericReport<Severity::Message>
{
	const char * getColor() const override;
	~Message() override = default;
};

}
#undef PAIR