#include "compile.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	General::Compile(argv[1]).compile();
}