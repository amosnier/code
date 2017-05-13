#include "utils.hpp"
#include <fstream>

/* 
 * Convert a file, interpreted as standard ASCII, to a C-string on the
 * heap.
 *
 * Note: the string object on the heap cannot be destroyed after this
 * function has returned. This is on purpose. This function should be
 * used to load constant strings from file at program startup.
 */
const char * file_to_c_string_on_heap(const std::string& filename)
{
	std::ifstream in(filename);
	(void) in.imbue(std::locale("C")); /* Interpret the file as standard ASCII. */
	/* Construct string on heap filling it by iterating on the file. */
	auto contents = new std::string(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
	in.close();
	
	return contents->c_str();
}
