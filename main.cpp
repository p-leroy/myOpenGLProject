#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

int main(int argc, char *argv[])
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[debug] %s", SDL_GetError());
		return -1;
	}

	SDL_Window* pWindow{ nullptr };
	SDL_Renderer* pRenderer{ nullptr };

	if (SDL_CreateWindowAndRenderer(800, 600, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Event events;
	bool isOpen{ true };
	while (isOpen)
	{
		while (SDL_PollEvent(&events))
		{
			switch (events.type)
			{
			case SDL_QUIT:
				isOpen = false;
				break;
			}
		}

		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
		SDL_RenderClear(pRenderer);

		SDL_Point point{ 800 / 2, 600 / 2};
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255); // On choisis la couleur rouge
		SDL_RenderDrawPoint(pRenderer, point.x, point.y); // On dessiner un point

		SDL_RenderPresent(pRenderer);
	}

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);

	SDL_Quit();


	return 0;
}
