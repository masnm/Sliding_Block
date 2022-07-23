#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <SDL2/SDL.h>
#include "../include/mysdl.h"
#include <stdbool.h>

typedef void (*func) ( SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect );

typedef struct {
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Rect src;
	func fun;
	bool can_move;
} block ;

void block_player ( SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect );
void block_box ( SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect );
void block_wall ( SDL_Renderer *, SDL_Texture *, SDL_Rect, SDL_Rect );

void block_get_player ( mysdl *, block * );
void block_get_box ( mysdl *, block * );
void block_get_wall ( mysdl *, block * );
void block_get_empty ( mysdl *, block * );

void initialize_block_map_from_file ( mysdl *, block [16][16], size_t, size_t, const char * );
SDL_Point get_player_pos_from_file ( size_t, size_t, const char * );
void clear_block_map ( block [16][16], size_t, size_t );

#endif // _BLOCK_H_
