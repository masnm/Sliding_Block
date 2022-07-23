#include "../include/mysdl.h"
#include <SDL2/SDL_image.h>

mysdl mysdl_create ( const char *title, int x, int y, int w, int h, Uint32 flags )
{
	if ( SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Could not initialize sdl2: %s\n", SDL_GetError());
		exit ( 1 );
	}
	SDL_Window* window = SDL_CreateWindow ( title, x, y, w, h, flags | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN );
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		exit ( 1 );
	}
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL) {
		SDL_DestroyWindow(window);
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		exit ( 1 );
	}
	return (mysdl) {
		.window = window,
		.renderer = renderer,
		.texture = NULL
	};
}

void mysdl_destroy ( mysdl * ms )
{
	SDL_DestroyTexture ( ms->texture );
	SDL_DestroyRenderer ( ms->renderer );
	SDL_DestroyWindow ( ms->window );
	SDL_Quit ();
}

void mysdl_texture_from_png ( mysdl * ms, const char *path )
{
	// extern DECLSPEC SDL_Texture * SDLCALL IMG_LoadTexture(SDL_Renderer *renderer, const char *file);
	SDL_Texture * texture = IMG_LoadTexture ( ms->renderer, path );
	if ( texture == NULL ) {
		mysdl_destroy ( ms );
		fprintf ( stderr, "SDL_IMG_LoadTexture Error: %s\n", SDL_GetError() );
		exit ( 1 );
	}
	ms->texture = texture;
}
