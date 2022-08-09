#ifndef __CVECTOR_H__
#define __CVECTOR_H__

/* Necessary C library */
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/* Structures */
typedef struct {
	size_t capacity, size, item;
	void *data, *ref;
} cvector ;

/* CREATE DESTROY */
cvector cvector_create ( size_t item );
void cvector_destroy ( cvector* vec );

/* Traversing or side effect */
void cvector_for_each ( cvector* vec, void (*fun)( void* ) );

/* Element access */
void* cvector_at ( cvector* vec, size_t at );
void* cvector_front ( cvector* vec );
void* cvector_back ( cvector* vec );
void* cvector_data ( cvector* vec );

/* Capacity */
bool cvector_empty ( cvector* vec );
size_t cvector_size ( cvector* vec );
void cvector_reserve ( cvector* vec, size_t capacity );
size_t cvector_capacity ( cvector* vec );

/* MODIFIERS */
void cvector_emplace_back ( cvector* vec, void* elem );
void cvector_pop_back ( cvector* vec );

#endif // __CVECTOR_H__
