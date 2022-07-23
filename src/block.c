#include "../include/block.h"

#include <SDL2/SDL.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void block_player ( SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dest )
{
	SDL_RenderCopy ( renderer, texture, &src, &dest );
}

void block_box ( SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dest )
{
	SDL_RenderCopy ( renderer, texture, &src, &dest );
}

void block_wall ( SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect src, SDL_Rect dest )
{
	SDL_RenderCopy ( renderer, texture, &src, &dest );
}

void block_get_player ( mysdl *ms, block *bl )
{
	SDL_Rect src = {
		.x =  360, .y = 0,
		.w = 360, .h = 360
	};
	bl->renderer = ms->renderer;
	bl->texture = ms->texture;
	bl->src = src;
	bl->fun = block_player;
	bl->can_move = true;
}

void block_get_box ( mysdl *ms, block *bl )
{
	SDL_Rect src = {
		.x = 0, .y = 0,
		.w = 360, .h = 360
	};
	bl->renderer = ms->renderer;
	bl->texture = ms->texture;
	bl->src = src;
	bl->fun = block_box;
	bl->can_move = true;
}

void block_get_wall ( mysdl *ms, block *bl )
{
	SDL_Rect src = {
		.x = 720, .y = 0,
		.w = 360, .h = 360
	};
	bl->renderer = ms->renderer;
	bl->texture = ms->texture;
	bl->src = src;
	bl->fun = block_wall;
	bl->can_move = false;
}

void block_get_empty ( mysdl *ms, block *bl )
{
	SDL_Rect src = {
		.x = 0, .y = 0,
		.w = 0, .h = 0
	};
	bl->renderer = NULL;
	bl->texture = NULL;
	bl->src = src;
	bl->fun = NULL;
	bl->can_move = true;
}

void initialize_block_map_from_file ( mysdl *ms, block map[16][16], size_t rows, size_t cols, const char * file_name )
{
	size_t cr = 0;
	char ch[cols+5];
	FILE *file = fopen ( file_name, "r" );
	while ( fscanf ( file, "%s", ch ) != EOF ) {
		if ( cr > rows ) break;
		size_t sz = strlen ( ch );
		assert ( sz == cols );
		for ( size_t i = 0 ; i < sz ; ++i ) {
			switch ( ch[i] ) {
				case 'W':
					block_get_wall ( ms, &map[cr][i] );
					break;
				case 'P':
					block_get_player ( ms, &map[cr][i] );
					break;
				case 'B':
					block_get_box ( ms, &map[cr][i] );
					break;
				default:
					block_get_empty ( ms, &map[cr][i] );
					break;
			}
		}
		++cr;
	}
	fclose ( file );
}

void clear_block_map ( block map[16][16], size_t rows, size_t cols )
{
	for ( int i = 0 ; i < rows ; ++i ) {
		for ( int j = 0 ; j < cols ; ++j ) {
			if ( map[i][j].fun != NULL ) {
				map[i][j] = (block){0};
			}
		}
	}
}

SDL_Point get_player_pos_from_file ( size_t rows, size_t cols, const char * file_name )
{
	SDL_Point player_pos;
	bool found_player = false;
	size_t cr = 0;
	char ch[cols+5];
	FILE *file = fopen ( file_name, "r" );
	while ( fscanf ( file, "%s", ch ) != EOF ) {
		if ( cr > rows ) break;
		size_t sz = strlen ( ch );
		assert ( sz == cols );
		for ( size_t i = 0 ; i < sz ; ++i ) {
			if ( ch[i] == 'P' ) {
				found_player = true;
				player_pos.x = cr;
				player_pos.y = i;
			}
		}
		++cr;
	}
	fclose ( file );
	assert ( found_player == true && "Player not found in Level Map" );
	return player_pos;
}
