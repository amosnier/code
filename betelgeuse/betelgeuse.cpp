#include <iostream>
#include <SDL2/SDL.h>
#include <GL/gl.h>

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Betelgeuse", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	                                      640, 480, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	if (window == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);
	if (glcontext == nullptr){
		std::cout << "SDL_GL_CreateContext Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);

	for (int i = 0; i < 3; ++i){
		SDL_Delay(1000);
	}

	SDL_GL_DeleteContext(glcontext);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
