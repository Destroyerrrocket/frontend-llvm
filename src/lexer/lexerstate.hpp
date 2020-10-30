#pragma once

#include "report/report.hpp"
#include <string>
#include <memory>
#include <string_view>

namespace Report
{
class Report;
class Error;
class Message;
class Warning;

}

namespace Lex
{


class LexerState
{
public:
	LexerState(std::istream &file, const char *name) : file(file), name(name) {}

	char nextLine();
	char readByte();
	char goBackByteOnLine();
	template<class T>
	std::unique_ptr<Report::Report> createReport(std::string &&msg);
	void finishedAToken();
	char currentChar = ' ';

private:
	template<class T>
	std::unique_ptr<Report::Report> createReportImpl(std::string &&msg);

	std::string currentLine = " ";
	std::string::const_iterator currentByte = currentLine.begin();
	std::string::const_iterator begginingToken = currentLine.begin();
	std::string_view previousToken;
	unsigned row = 0;
	std::istream &file;
	const char * const name;
};

template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Error>(std::string &&msg);
template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Message>(std::string &&msg);
template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Warning>(std::string &&msg);
}