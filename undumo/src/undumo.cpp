#include <cstdlib>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vertex_simple.glsl.h"
#include "fragment_color.glsl.h"

static const GLuint WIDTH = 800;
static const GLuint HEIGHT = 600;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

static void error_callback(int error, const char* description)
{
	std::cout << "ERROR::GLFW\n" << description << std::endl;
}

int main(void)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "undumo", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	/* Initialize GLAD with GLFW's extension fetcher. */
	gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

	/*
	 * Set vsync to one, i.e. OpenGL refreshing frequency is the
	 * same as the screen refreshing frequency.
	 */
	glfwSwapInterval(1);
	
	/* Define the viewport dimensions */
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);  
	glViewport(0, 0, width, height);

	/* Build and compile our shader program */
	/* Vertex shader */
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	GLchar *p = (GLchar *) vertex_simple_glsl;
	glShaderSource(vertex_shader, 1, &p, (GLint *) &vertex_simple_glsl_len);
	glCompileShader(vertex_shader);
	/* Check for compile time errors */
	GLint success;
	GLchar info_log[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, sizeof info_log, NULL, info_log);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	/* Fragment shader */
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	p = (GLchar *) fragment_color_glsl;
	glShaderSource(fragment_shader, 1, &p, (GLint *) &fragment_color_glsl_len);
	glCompileShader(fragment_shader);
	/* Check for compile time errors */
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, sizeof info_log, NULL, info_log);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
	}
	/* Link shaders */
	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	/* Check for linking errors */
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, sizeof info_log, NULL, info_log);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	/* Set up vertex data (and buffer(s)) and attribute pointers */
	GLfloat vertices[] = {
		-0.5f, -0.5f, 0.0f, // Left  
		0.5f, -0.5f, 0.0f, // Right 
		0.0f,  0.5f, 0.0f  // Top   
	};
	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	/*
	 * Bind the Vertex Array Object first, then bind and set
	 * vertex buffer(s) and attribute pointer(s).
	 */
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof (GLfloat), (GLvoid*) 0);
	glEnableVertexAttribArray(0);

	/*
	 * Note that this is allowed, the call to
	 * glVertexAttribPointer registered VBO as the currently bound
	 * vertex buffer object so afterwards we can safely unbind
	 */
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*
	 * Unbind VAO (it's always a good thing to unbind any
	 * buffer/array to prevent strange bugs)
	 */
	glBindVertexArray(0);

	while (!glfwWindowShouldClose(window))
	{
		/*
		 * Check if any events have been activiated (key
		 * pressed, mouse moved etc.) and call corresponding
		 * response functions
		 */
		glfwPollEvents();

		/* Render */
		/* Clear the colorbuffer */
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/* Draw our first triangle */
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		/* Swap the screen buffers */
		glfwSwapBuffers(window);
	}
	/* Properly de-allocate all resources once they've outlived their purpose */
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	/* Terminate GLFW, clearing any resources allocated by GLFW. */
	glfwTerminate();

	exit(EXIT_SUCCESS);
}
