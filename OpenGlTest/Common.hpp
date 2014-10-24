#ifndef COMMON_HPP
#define COMMON_HPP

#include <stdexcept>
#include <string>

#define CONTEXT(str) (std::string("File ") + __FILE__ + ", line " + std::to_string(__LINE__) + \
                      ", function " + __func__ + ": " + str)

#endif // COMMON_HPP
