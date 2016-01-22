#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

static void open_file(const std::string& name)
{
	std::fstream s(name);
	while (!s.eof()) {
		std::string line;
		getline(s, line);
		std::cout << line << std::endl;
	}
	s.close();
}

static void interpret_open(std::istream& is)
{
	std::string name;
	is >> name;
	if (name.size() == 0)
		std::cout << "so you want to open the current directory?";
	else
		open_file(name);
}

static void interpret_line(const std::string& line)
{
	std::istringstream is(line);
	std::string command;
	is >> command;
	if (command == "help")
		std::cout << "welcome to neatxt!";
	else if (command == "open")
		interpret_open(is);
	else
		std::cout << "unknown command";
}

int main()
{
	for (;;) {
		std::string line;
		std::cout << "> ";
		std::getline(std::cin, line);
		interpret_line(line);
		std::cout << std::endl;
		       
	}
}
