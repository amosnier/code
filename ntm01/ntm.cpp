#include <fstream>
#include <boost/filesystem.hpp>
#include <stdexcept>

#include "ntm_interpreter.hpp"

int main(int argc, char* argv[])
{
	namespace fs = boost::filesystem;
	
	fs::path ntm(argv[0]);
	if (argc != 2)
		throw std::invalid_argument("format: " + ntm.filename().string() + " <NTM file to interpret>");

	fs::path in(argv[1]);
	auto out = in;
	out.replace_extension(".res");

	std::ifstream ifs;
	std::ofstream ofs;

	// throw on error on both streams
	ifs.exceptions(std::ifstream::badbit); // we will get fail at eof
	ofs.exceptions(std::ofstream::failbit | std::ofstream::badbit);

	ifs.open(in.string());
	ofs.open(out.string());

	ntm::interpret(ofs, ifs);

	ifs.close();
	ofs.close();
}
