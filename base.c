#include "base.h"


func f32 f32_inf(void) {
  union { f32 f; u32 u; } r;
  r.u = 0x7f800000;
  return r.f;
}

func f32 f32_neg_inf(void) {
  union { f32 f; u32 u; } r;
  r.u = 0xff800000;
  return r.f;
}


func f64 f64_inf(void) {
  union { f64 f; u64 u; } r;
  r.u = 0x7ff0000000000000;
  return r.f;
}

func f64 f64_neg_inf(void) {
  union { f64 f; u64 u; } r;
  r.u = 0xfff0000000000000;
  return r.f;
}


func f32 f32_abs(f32 x) {
  union { f32 f; u32 u; } r;

  r.f = x;
  r.u &= 0x7fffffff;
  return r.f;
}

func f64 f64_abs(f64 x) {
  union { f64 f; u64 u; } r;
  
  r.f = x;
  r.u &= 0x7fffffffffffffff;
  return r.f;
}


////////////////////////////////////////
// NOTE(iyaan): Allocators

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
  AProcReturn ret = allocator->procedure(allocator->data, FREE_ALL, 0, 0);
  return ret.data;
}


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
      char* cur_ptr =  ByteOffset(arena->data, arena->offset);
      MemZero(cur_ptr, size);
      arena->offset += size;
      ret.error = NONE;
      ret.data = ByteOffset(arena->data, arena->offset);
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
