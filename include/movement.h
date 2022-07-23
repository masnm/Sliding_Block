#ifndef _MOVEMENT_H_
#define _MOVEMENT_H_

#include <SDL2/SDL.h>
#include "../include/block.h"

typedef struct {
	size_t x;
	size_t y;
} direction ;

extern const direction dir_left;
extern const direction dir_up;
extern const direction dir_right;
extern const direction dir_down;

SDL_Point move_in_direction ( block [16][16], size_t, size_t, SDL_Point, direction );

#endif // _MOVEMENT_H_
