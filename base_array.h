#pragma once

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
    

  return dyn_arr;
}

void* dynamic_array_index(dynamic_array* arr, u64 idx) {
  if (arr->count > 0 && idx < arr->count) {
    return ByteOffset(arr->data, (arr->count - 1) * arr->elem_size);
  }
  else {
    return NULL;
  }
}

Bool dynamic_array_push(dynamic_array* arr, const void* elem) {
  Bool need_resize = (arr->count + 1) > arr->cap;
  if (need_resize) {
    const u64 new_cap = (arr->cap * 2);
    const u64 new_size_bytes = new_cap * arr->elem_size;
    allocator_resize(&arr->allocator, new_size_bytes, 0);
    arr->cap = new_cap;
  }
  const void* elem_ptr = dynamic_array_index(arr, arr->count);
  if (elem_ptr != NULL) {
    MemCopy(elem_ptr, elem, arr->elem_size);
    arr->count += 1;
    return True;
  }
  else {
    return False;
  }
}

Bool dynamic_array_pop(dynamic_array* arr, void* ptr);
Bool dynamic_array_unordered_remove(dynamic_array* arr, void* ptr, u64 idx);
Bool dynamic_array_ordered_remove(dynamic_array* arr, void* ptr, u64 idx);
Bool dynamic_array_inject_at(dynamic_array* arr, u64 idx);