#include <stdexcept>
#include <stack>
#include <fstream>
#include <iostream>
#include <cstddef>
#include <sstream>

struct Io {
	unsigned val;
	unsigned mask;
	Io(unsigned val = 0, unsigned mask = ~0): val(val), mask(mask) {};
};

template <class T>
std::string to_string(T t, std::ios_base & (*f)(std::ios_base&))
{
	std::ostringstream oss;
	oss << f << t;
	return oss.str();
}

void execute_token(std::stack<Io>& stack, const std::string& token)
{
	try {
		unsigned input = static_cast<unsigned>(stoi(token, nullptr, 0));
		stack.push(Io(input));
		return;
	} catch(const std::invalid_argument& e) {
		(void)e;
	}
	if (token == "nand") {
		unsigned mask = 1;
		Io a = stack.top();
		if (a.val & ~mask)
			throw std::invalid_argument("token " + to_string<unsigned>(a.val, std::hex));
		stack.pop();
		Io& b =	stack.top();
		if (b.val & ~mask)
			throw std::invalid_argument("token " + to_string<unsigned>(b.val, std::hex));
		b.mask = mask;
		b.val = !(a.val & b.val);
	}
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
