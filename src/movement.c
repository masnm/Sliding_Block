#include "../include/movement.h"
#include "../include/block.h"

const direction dir_left  = { .x =  0, .y = -1 };
const direction dir_up    = { .x = -1, .y =  0 };
const direction dir_right = { .x =  0, .y =  1 };
const direction dir_down  = { .x =  1, .y =  0 };

bool point_inside_map ( size_t rows, size_t cols, SDL_Point pos )
{
	return ( pos.x >= 0 && pos.x < rows
			&& pos.y >= 0 && pos.y < cols );
}

bool internal_swap ( block map[16][16], size_t rows, size_t cols, SDL_Point start, SDL_Point end )
{
	if ( point_inside_map ( rows, cols, start )
			&& point_inside_map ( rows, cols, end )
			&& map[end.x][end.y].can_move ) {
		block t = map[start.x][start.y];
		map[start.x][start.y] = map[end.x][end.y];
		map[end.x][end.y] = t;
		return true;
	}
	return false;
}

SDL_Point point_dir_add ( SDL_Point f, direction s )
{
	return (SDL_Point) {
		.x = f.x + s.x,
		.y = f.y + s.y
	};
}

SDL_Point move_in_direction ( block map[16][16], size_t rows, size_t cols, SDL_Point player_pos, direction dir )
{
	SDL_Point curr = player_pos;
	SDL_Point next = point_dir_add ( curr, dir );
	SDL_Point s_next = point_dir_add ( next, dir );
	if ( point_inside_map ( rows, cols, curr )
			&& point_inside_map ( rows, cols, next )
			&& map[next.x][next.y].fun == NULL ) {
		internal_swap ( map, rows, cols, curr, next );
		return next;
	}
	if ( point_inside_map ( rows, cols, curr )
			&& point_inside_map ( rows, cols, next )
			&& point_inside_map ( rows, cols, s_next )
			&& map[s_next.x][s_next.y].fun == NULL ) {
		internal_swap ( map, rows, cols, next, s_next );
		internal_swap ( map, rows, cols, curr, next );
		return next;
	}
	return player_pos;
}
