#pragma once

#include <stdio.h>
#include "base_types.h"
#include "base_allocator.h"

////////////////////////////////////////
// NOTE(iyaan): Dynamic Array Type

typedef struct dynamic_array {
  void* data;
  u64 elem_size;
  u64 count; // In elements
  u64 cap;   // In elements
  Allocator allocator;
} dynamic_array;

Bool dynamic_array_init(dynamic_array* dyn_arr, Allocator allocator, const u64 cap, const u64 elem_size) {
  dyn_arr->allocator = allocator;
  
  if (cap > 0 && elem_size > 0) {
    dyn_arr->elem_size = elem_size;
    dyn_arr->cap = cap;

    void* ptr = allocator_alloc(&dyn_arr->allocator, cap, 0);
    if (ptr != NULL) {
      dyn_arr->data = ptr;
    }
    else {
      return False;
    }
  }
  else {
    return False;
  }
    

  return True;
}

Bool dynamic_array_is_empty(dynamic_array* arr) {
  return arr->count == 0;
}

u64 dynamic_array_size(dynamic_array* arr) {
  return arr->count;
}

#define index(dyn_arr, idx, T) (*((T*)dynamic_array_index(dyn_arr, idx)))

void* dynamic_array_index(dynamic_array* arr, u64 idx) {
  if (dynamic_array_is_empty(arr)) {
    if (idx > 0) {
#if defined(ARRAY_OUT_OF_BOUND_PANIC)
      char format_buffer[64] = { 0 };
      snprintf(format_buffer, 64, "%lu > %lu (array length)", idx, arr->count);
      Panic(format_buffer);
#else
      return NULL;
#endif
    }
    else {
      return arr->data;
    }
  } else {
    if (idx < arr->count) {
      return ByteOffset(arr->data, (idx) * arr->elem_size);
    } else {
#if defined(ARRAY_OUT_OF_BOUND_PANIC)
      char format_buffer[64] = { 0 };
      snprintf(format_buffer, 64, "%lu > %lu (array length)", idx, arr->count);
      Panic(format_buffer);
#else
      return NULL;
#endif
    }
  }
}

func u64 get_last_elem_idx(dynamic_array* arr) {
  if (arr->count == 0) {
    return 0;
  } else {
    return arr->count - 1;
  }
}

#define push(arr, val, T) Stmt(T v = val; dynamic_array_push(arr, (void*)&v);)

Bool dynamic_array_push(dynamic_array* arr, const void* elem) {
  Bool need_resize = (arr->count + 1) > arr->cap;
  if (need_resize) {
    const u64 new_cap = (arr->cap * 2);
    const u64 new_size_bytes = new_cap * arr->elem_size;
    allocator_resize(&arr->allocator, new_size_bytes, 0);
    arr->cap = new_cap;
  }
  const u64 last_elem_idx = get_last_elem_idx(arr);
  void* elem_ptr;
  if (arr->count > 0) {
    elem_ptr = (u8*)arr->data + (last_elem_idx + 1) * arr->elem_size;
  } else {
    elem_ptr = arr->data;
  }
  MemCopy((void*)elem_ptr, elem, arr->elem_size);
  arr->count += 1;
  return True;
}

Bool dynamic_array_pop(dynamic_array* arr, void* ptr) {
  if (arr->count > 0) {
    void* to_pop = dynamic_array_index(arr, arr->count - 1);
    // NOTE(iyaan): Caller has to give a properly sized buffer
    MemCopy(ptr, to_pop, arr->elem_size);
    MemZero(to_pop, arr->elem_size);
    arr->count -= 1;
    return True;
  } else {
    return False;
  }
}

// removes an element at a specific index. Unordered means it is O(1),
// since it swaps the last element to the removed location - making the
// array be sorted differently.
Bool dynamic_array_unordered_remove(dynamic_array* arr, void* ptr, u64 idx) {
  if (idx >= 0 && idx < arr->count) {
    void* to_remove = dynamic_array_index(arr, idx);
    MemCopy(ptr, to_remove, arr->elem_size);
    void* last_elem = dynamic_array_index(arr, arr->count - 1);
    MemCopy(to_remove, last_elem, arr->elem_size);
    MemZero(last_elem, arr->elem_size);
    arr->count -= 1;
    return True;
  } else {
    return False;
  }
}

// removes an element at a specific index. Ordered means it will move
// all elements after the index downwards with a copy - ensuring elements
// remain in the same order.
Bool dynamic_array_ordered_remove(dynamic_array* arr, void* ptr, u64 idx) {
  if (idx >= 0 && idx < arr->count) {
    void* to_remove = dynamic_array_index(arr, idx);
    MemCopy(ptr, to_remove, arr->elem_size);
    void* copy_start_offset = dynamic_array_index(arr, idx + 1);
    if (copy_start_offset != NULL) {
      u64 total_copy_size = arr->count - (idx + 1);
      void* last_elem = dynamic_array_index(arr, arr->count - 1);
      MemCopy(to_remove, copy_start_offset, total_copy_size);
      MemZero(last_elem, arr->elem_size);
    } else {
      MemZero(to_remove, arr->elem_size);
    }
    arr->count -= 1;
    return True;
  } else {
    return False;
  }
}

Bool dynamic_array_inject_at(dynamic_array* arr, u64 idx);
