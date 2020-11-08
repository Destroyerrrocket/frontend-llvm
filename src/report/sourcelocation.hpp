#pragma once
#include <string>

namespace Report
{
struct SourceLocation {
	std::string filePath;
	unsigned row;
	unsigned column;
	unsigned size;
	std::string line;
};

}