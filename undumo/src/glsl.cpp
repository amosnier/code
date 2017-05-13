#include "glsl.hpp"
#include "utils.hpp"

const GLchar * SIMPLE_VERTEX_SHADER;
const GLchar * COLOR_FRAGMENT_SHADER;

void load_shader_strings(void)
{
	SIMPLE_VERTEX_SHADER = file_to_c_string_on_heap("vertex_simple.glsl");
	COLOR_FRAGMENT_SHADER = file_to_c_string_on_heap("fragment_color.glsl");
}
