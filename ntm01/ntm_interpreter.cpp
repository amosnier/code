#include <string>
#include <sstream>
#include <deque>
#include <map>
#include <stdexcept>
#include <bitset>

#include "ntm_interpreter.hpp"

using Stack = std::deque<std::string>; // mostly stack, but dumped FIFO
using Map = std::map<std::string, void(*)(Stack&)>;
using Bit = std::bitset<1>;

static bool token_is_valid(const std::string& token)
{
	return token.size() != 0 && token.find('#') == std::string::npos;
}

static void assert_not_empty(Stack& stack)
{
	if (stack.empty())
		throw std::invalid_argument(std::string(__func__) + ": stack empty");
}

static void neg(Stack& stack)
{
	assert_not_empty(stack);

	auto sa = stack.front();
	stack.pop_front();

	Bit a = Bit(stoi(sa, nullptr, 0));

	stack.push_front((~a).to_string());
}

static void one(Stack& stack)
{
	assert_not_empty(stack);

	stack.pop_front();

	stack.push_front("1");
}

static void nand(Stack& stack)
{
	assert_not_empty(stack);

	auto sa = stack.front();
	stack.pop_front();

	Bit a = Bit(stoi(sa, nullptr, 0));

	if (a[0])
		neg(stack);
	else
		one(stack);
}

static Map known_functions(void)
{
	Map map;
	map["one"] = one;
	map["not"] = neg;
	map["nand"] = nand;
	return map;
}

// The point of going through a line level is especially
// error reporting, that will have to be mapped against
// source code lines to the user.
static void interpret_line(Stack& stack, std::istream& in)
{
	std::string token;
	Map map = known_functions();
	while (!in.eof()) {
		in >> token;
		if (!token_is_valid(token))
			break;
		auto it = map.find(token);
		if (it != map.end()) {
			it->second(stack);
		} else {
			stack.push_front(token);
		}
	}		
}

static void dump(std::ostream& out, Stack& stack)
{
	while (!stack.empty()) {
		out << stack.back() << std::endl;
		stack.pop_back();
	}
}

void ntm::interpret(std::ostream& out, std::istream& in)
{
	std::string line;
	Stack stack;
	while (!in.eof()) {
		std::getline(in, line);
		std::istringstream iss(line);
		iss.exceptions(std::istream::badbit); // we will get failbit at eof
		interpret_line(stack, iss);
	}
	dump(out, stack);
}
