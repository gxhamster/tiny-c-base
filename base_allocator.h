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

void* allocator_alloc(Allocator* allocator, u64 size, u64 alignment) {
  AProcReturn ret = allocator->procedure(allocator->data, ALLOC, size, alignment);
  return ret.data;
}

void* allocator_resize(Allocator* allocator, u64 new_size, u64 alignment) {
  AProcReturn ret = allocator->procedure(allocator->data, RESIZE, new_size, alignment);
  return ret.data;
}

void* allocator_free(Allocator* allocator, u64 size) {
  AProcReturn ret = allocator->procedure(allocator->data, FREE, size, 0);
  return ret.data;
}

void allocator_free_all(Allocator* allocator) {
  allocator->procedure(allocator->data, FREE_ALL, 0, 0);
}

// NOTE(iyaan): A Bump Allocator (Non-Growing Arena)

typedef struct
{
    void *data;
    u64 offset;
    u64 size;
} Arena;

const u64 ARENA_MIN_ALLOC_SIZE = KB(64);

AProcReturn arena_allocator_proc(void *data, AllocMode mode, u64 size, u64 alignment) {
  Arena* arena = (Arena*)data;
  AProcReturn ret = {0};
  switch (mode) {
  case ALLOC:
  {
    if (arena->data == NULL) {
      ret.error = OUT_OF_MEMORY;
      break;
    }

    u64 expected_size = size + arena->offset;
    if (expected_size > arena->size) {
      ret.error = OUT_OF_MEMORY;
    } else {
      char* cur_ptr = ByteOffset(arena->data, arena->offset);
      MemZero(cur_ptr, size);
      arena->offset += size;
      ret.error = NONE;
      ret.data = (void*)cur_ptr;
    }
    break;
  }
  case RESIZE:
  {
    void* new_mem = realloc(arena->data, size);
    if (new_mem == NULL) {
      ret.error = OUT_OF_MEMORY;
      break;
    }
    u64 old_size = arena->size;
    MemZero(ByteOffset(new_mem,old_size), size-old_size);
    arena->size = size;
    arena->data = new_mem;
    break;
  }
  case FREE:
  {
    // Pop a single value from the arena
    if ((arena->offset - size) >= 0) {
      ret.error = NONE;
      ret.data = ByteOffset(arena->data, arena->offset);
      arena->offset -= size;
      break;
    } else {
      ret.error = OUT_OF_MEMORY;
      ret.data = NULL;
      break;
    }

  }
  case FREE_ALL:
  {
    if (arena->data != NULL) {
      free(arena->data);
    }
    arena->offset = 0;
    arena->size = 0;
    ret.error = NONE;
    break;
  }
  case QUERY_FEATURES:
  {
    // TODO(iyaan)
  }
  }

  return ret;
}

void arena_init(Arena* arena, void* buf, u64 buf_size) {
  arena->data = buf;
  arena->offset = 0;
  arena->size = buf_size;
}

Allocator arena_allocator(Arena* arena) {
  Allocator allocator;
  allocator.data = arena;
  allocator.procedure = &arena_allocator_proc;
  return allocator;
}

#endif // BASE_ALLOC_H_
