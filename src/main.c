#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/mysdl.h"
#include "../include/block.h"
#include "../include/movement.h"

#define map_rows 16
#define map_cols 16
const size_t rows = 16;
const size_t cols = 16;

block map[map_rows][map_cols];

int main ( int argc, char* argv[] )
{
	mysdl ms = mysdl_create ( "Sliding Block Puzzle", 10, 10, 640, 640, (Uint32)0 );
	mysdl_texture_from_png ( &ms, "./sprites/images.png" );

	initialize_block_map_from_file ( &ms, map, rows, cols, "./level/level1.txt" );
	SDL_Point player_pos = get_player_pos_from_file ( rows, cols, "./level/level1.txt" );

	int window_width, window_height, block_height, block_width;
	SDL_GetWindowSize ( ms.window, &window_width, &window_height );
	block_height = window_height / rows;
	block_width = window_width / cols;

	bool done = false;
	SDL_Event e;
	while ( !done ) {
		SDL_SetRenderDrawColor(ms.renderer, 0, 0, 0, 255);
		SDL_RenderClear(ms.renderer);
		while ( SDL_PollEvent(&e) ) {
			switch (e.type) {
				case SDL_QUIT:
					done = true;
					break;
				case SDL_WINDOWEVENT:
					switch ( e.window.event ) {
						case SDL_WINDOWEVENT_RESIZED:
							SDL_GetWindowSize ( ms.window, &window_width, &window_height );
							block_height = window_height / rows;
							block_width = window_width / cols;
							break;
						default:
							break;
					}
					break;
				case SDL_KEYDOWN:
					switch ( e.key.keysym.sym ) {
						case SDLK_LEFT:
							player_pos = move_in_direction ( map, rows, cols, player_pos, dir_left );
							break;
						case SDLK_RIGHT:
							player_pos = move_in_direction ( map, rows, cols, player_pos, dir_right );
							break;
						case SDLK_UP:
							player_pos = move_in_direction ( map, rows, cols, player_pos, dir_up );
							break;
						case SDLK_DOWN:
							player_pos = move_in_direction ( map, rows, cols, player_pos, dir_down );
							break;
						default:
							break;
					}
				default:
					break;
			}
			// done = true;
		}
		// rendering blocks game
		for ( size_t i = 0 ; i < map_rows ; ++i ) {
			for ( size_t j = 0 ; j < map_cols ; ++j ) {
				if ( map[i][j].fun != NULL ) {
					SDL_Rect dest = {
						.x = j * block_width, .y = i * block_height,
						.w = block_width, .h = block_height
					};
					map[i][j].fun ( map[i][j].renderer, map[i][j].texture, map[i][j].src, dest );
				}
			}
		}
		// SDL_RenderCopy ( ms.renderer, ms.texture, &src, &dst );
		SDL_RenderPresent(ms.renderer);
	}

	mysdl_destroy ( &ms );

	return 0;
}

