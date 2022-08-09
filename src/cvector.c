#include "../include/cvector.h"

cvector cvector_create ( size_t item )
{
	cvector vec = {
		.capacity = 0,
		.size = 0,
		.item = item,
		.data = NULL,
		.ref = NULL
	};
	return vec;
}

void cvector_destroy ( cvector* vec )
{
	vec -> capacity = 0;
	vec -> size = 0;
	vec -> item = 0;
	free ( vec -> data );
	vec -> data = NULL;
	vec -> ref = NULL;
}

void cvector_for_each ( cvector* vec, void (*fun)( void* ) )
{
	for ( size_t i = 0 ; i < vec->size ; ++i ) {
		vec->ref = vec->data + (i * vec->item);
		fun ( vec->ref );
	}
}

void cvector_emplace_back ( cvector* vec, void* elem )
{
	if ( vec -> size == vec -> capacity ) {
		vec -> capacity == 0 ? (vec -> capacity = 1) : (vec -> capacity *= 2);
		vec -> data = realloc ( vec->data, vec->item * vec->capacity );
		assert ( vec -> data != NULL );
	}
	memcpy ( vec->data + (vec->size * vec->item), elem, vec->item );
	vec -> size += 1;
}

void cvector_pop_back ( cvector* vec )
{
	assert ( vec->size > 0 );
	vec->size -= 1;
}

bool cvector_empty ( cvector* vec )
{
	return vec -> size == 0;
}

size_t cvector_size ( cvector* vec )
{
	return vec -> size;
}

void cvector_reserve ( cvector* vec, size_t capacity )
{
	assert ( capacity <= ((size_t)1 << ((sizeof(size_t)*8)-1)) );
	size_t count = 0;
	for ( size_t i = 1 ; i <= capacity ; i <<= 1 ) {
		if ( capacity & i ) ++count;
	}
	assert ( count == 1 && "capacity must be power of 2" );
	vec -> capacity = capacity;
	vec -> data = realloc ( vec->data, vec->item * vec->capacity );
	assert ( vec -> data != NULL );
}

size_t cvector_capacity ( cvector* vec )
{
	return vec -> capacity;
}

void* cvector_at ( cvector* vec, size_t at )
{
	assert ( at < vec->size );
	vec->ref = vec->data + (at * vec->item);
	return vec->ref;
}

void* cvector_front ( cvector* vec )
{
	assert ( !cvector_empty(vec) );
	return cvector_at ( vec, 0 );
}

void* cvector_back ( cvector* vec )
{
	assert ( !cvector_empty(vec) );
	return cvector_at ( vec, vec->size-1 );
}

void* cvector_data ( cvector* vec )
{
	return vec->ref = vec->data;
}
