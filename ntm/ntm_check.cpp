#include <stdexcept>
#include <stack>
#include <fstream>
#include <iostream>

struct Io {
	unsigned val;
	unsigned mask;
	Io(unsigned val = 0, unsigned mask = 0): val(val), mask(mask) {};
};

void execute_token(std::stack<Io>& stack, const std::string& token)
{
	
}

std::stack<Io> execute(const char* file)
{
	std::stack<Io> stack;

	std::ifstream is;
	is.open(file);
	std::string token;
	is >> token;
	while (is.good()) {
		is >> token;
		execute_token(stack, token);
	}
	is.close();
	
	return stack;
}

void print(const char* file)
{
	std::ifstream is;
	is.open(file);
	std::string token;
	is >> token;
	while (is.good()) {
		std::cout << token << std::endl;
		is >> token;
	}
	is.close();
}

int main (int argc, char *argv[])
{
	if (argc != 2)
		throw std::invalid_argument("format: " + std::string(argv[0]) + " <NTM file to check>");
	print(argv[1]);
	return 0;
}
