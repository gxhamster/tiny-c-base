#ifndef BASE_ALLOC_H_
#define BASE_ALLOC_H_

#include "base_types.h"
#include "base_macros.h"

////////////////////////////////////////
// NOTE(iyaan): Allocators

typedef enum
{
    ALLOC,          // Allocate a value on the allocator
    FREE,           // Free a single value on the allocator
    FREE_ALL,       // Free all allocated values on the allocator
    RESIZE,         // Resize the allocator
    QUERY_FEATURES, // Check the supported operations on the allocator
    ALLOC_MODE_LEN,
} AllocMode;


typedef enum {
    NONE,
    OUT_OF_MEMORY,
    INVALID_ARGUMENT,
    MODE_NOT_IMPLEMENTED,
} AllocatorError;

typedef struct {
    void* data;
    AllocatorError error;
} AProcReturn; 


typedef struct
{
  AllocMode features[ALLOC_MODE_LEN];
  u64 count;
} AllocatorQueryFeaturesArray;

typedef struct
{
    void *data;
    AProcReturn (*procedure)(void *data, AllocMode mode, u64 size, u64 alignment);
} Allocator;

#define new(A,T) ((T*)allocator_alloc(A, sizeof(T), 0))
#define new_array(A,T,C) ((T*)allocator_alloc(A, sizeof(T) * C, 0))
#define delete(A,T) allocator_free(A,sizeof(T))
#define free_all(A) allocator_free_all(A)

void* allocator_alloc(Allocator *allocator, u64 size, u64 alignment);
void* allocator_free(Allocator *allocator, u64 size);
void allocator_free_all(Allocator *allocator);
void* allocator_resize(Allocator *allocator, u64 new_size, u64 alignment);

// NOTE(iyaan): A Bump Allocator (Non-Growing Arena)

typedef struct
{
    void *data;
    u64 offset;
    u64 size;
} Arena;

const u64 ARENA_MIN_ALLOC_SIZE = KB(64);

Allocator arena_allocator(Arena *arena);
AProcReturn arena_allocator_proc(void *data, AllocMode mode, u64 size, u64 alignment);

#endif // BASE_ALLOC_H_