#pragma once
#include <memory>

namespace General
{

class Compile
{
public:
	Compile() = delete;
	explicit Compile(char *file);
	~Compile();

	Compile(Compile&) = delete;
	Compile& operator=(Compile&) = delete;

	void compile();
private:
	struct D;
	std::unique_ptr<D> d;
};

}