#include <iostream>
#include <SDL2/SDL.h>

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	/* Create a renderer that will draw to the window, -1 specifies that we want to load whichever
	 * video driver supports the flags we're passing
	 * SDL_RENDERER_ACCELERATED: We want to use hardware accelerated rendering
	 * SDL_RENDERER_PRESENTVSYNC: We want the renderer's present function (update screen) to be
	 * synchronized with the monitor's refresh rate
	 */
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr){
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	Uint32 rmask, gmask, bmask, amask;

/* SDL interprets each pixel as a 32-bit number, so our masks must depend
 * on the endianness (byte order) of the machine
 */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	SDL_Surface *surf = SDL_CreateRGBSurface(0, 640, 480, 32, rmask, gmask, bmask, amask);
	if (surf == nullptr) {
		std::cout << "SDL_CreateRGBSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
	SDL_FreeSurface(surf); // We no longer need the surface
	if (tex == nullptr){
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	for (int i = 0; i < 3; ++i){
		SDL_RenderClear(ren);                 // First clear the renderer
		SDL_RenderCopy(ren, tex, NULL, NULL); // Draw the texture
		SDL_RenderPresent(ren);               // Update the screen
		SDL_Delay(1000);
	}

	/* Clean up our objects and quit */
	SDL_DestroyTexture(tex);
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;
}
