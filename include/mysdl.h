#ifndef _MYSDL_H_
#define _MYSDL_H_

#include <SDL2/SDL.h>

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
} mysdl ;

mysdl mysdl_create ( const char *, int, int, int, int, Uint32 );
void mysdl_destroy ( mysdl * );
void mysdl_texture_from_png ( mysdl * , const char * );

#endif // _MYSDL_H_
