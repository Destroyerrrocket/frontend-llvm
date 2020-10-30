#include "lexerstate.hpp"
#include "report/report.hpp"

#include <istream>
#include <iostream>
#include <string_view>

#define FRONTEND_LEXER_DEBUG_LEXERSTATE 0

namespace Lex
{

char LexerState::nextLine()
{
	if (file.eof())
		return EOF;
	std::getline(file, currentLine);

	if (file.fail() && !file.eof()) {
		std::cout << "FATAL ERROR: file failed" << std::endl;
		abort();
	}
	#if FRONTEND_LEXER_DEBUG_LEXERSTATE
	std::cout << "READ LINE: `" << currentLine << '`' << std::endl;
	#endif
	currentLine += '\n';
	currentByte = currentLine.begin();
	begginingToken = currentLine.begin();
	previousToken = "";
	++row;
	return *currentByte;
}

char LexerState::readByte()
{
	++currentByte;
	if (currentByte == currentLine.end())
		return nextLine();
	#if FRONTEND_LEXER_DEBUG_LEXERSTATE
	std::cout << "ON CHAR: `" << *currentByte << "` (" << std::hex << int(*currentByte) << std::dec << ')' << std::endl;
	#endif
	return *currentByte;
}

char LexerState::goBackByteOnLine()
{
	if (currentByte == currentLine.begin()) {
		return EOF;
	}
	--currentByte;
	return *currentByte;
}

void LexerState::finishedAToken()
{
	previousToken = std::string_view(begginingToken, currentByte);
	begginingToken = currentByte;
}

template<class T>
std::unique_ptr<Report::Report> LexerState::createReportImpl(std::string &&msg)
{
	auto *e = new T();
	e->column = begginingToken - currentLine.begin();
	e->line = currentLine;
	e->filePath = name;
	e->message = msg;
	e->row = row;
	e->size = std::max(currentByte - begginingToken, 1L);
	return std::unique_ptr<Report::Report>(e);
}

template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Error>(std::string &&msg)
{
	return createReportImpl<Report::Error>(std::move(msg));
}

template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Message>(std::string &&msg)
{
	return createReportImpl<Report::Message>(std::move(msg));
}
template<>
std::unique_ptr<Report::Report> LexerState::createReport<Report::Warning>(std::string &&msg)
{
	return createReportImpl<Report::Message>(std::move(msg));
}

}