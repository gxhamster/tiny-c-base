#include "base.h"

#include <stdarg.h>

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
// NOTE(iyaan): Compund Types

func v2s32 v2s32_add(v2s32 a, v2s32 b) {
  v2s32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  return z; 
}

func v2f32 v2f32_add(v2f32 a, v2f32 b) {
  v2f32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  return z; 
}

func v3s32 v3s32_add(v3s32 a, v3s32 b) {
  v3s32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  z.z = a.z + b.z;
  return z; 
}

func v3f32 v3f32_add(v3f32 a, v3f32 b) {
  v3f32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  z.z = a.z + b.z;
  return z; 
}

func v4s32 v4s32_add(v4s32 a, v4s32 b) {
  v4s32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  z.z = a.z + b.z;
  z.w = a.w + b.w;
  return z; 
}

func v4f32 v4f32_add(v4f32 a, v4f32 b) {
  v4f32 z = {0};
  z.x = a.x + b.x;
  z.y = a.y + b.y;
  z.z = a.z + b.z;
  z.w = a.w + b.w;
  return z; 
}

func v2s32 v2s32_sub(v2s32 a, v2s32 b) {
  v2s32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  return z; 
}

func v2f32 v2f32_sub(v2f32 a, v2f32 b) {
  v2f32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  return z;
}

func v3s32 v3s32_sub(v3s32 a, v3s32 b) {
  v3s32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  z.z = a.z - b.z;
  return z; 
}

func v3f32 v3f32_sub(v3f32 a, v3f32 b) {
  v3f32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  z.z = a.z - b.z;
  return z; 
}

func v4s32 v4s32_sub(v4s32 a, v4s32 b) {
  v4s32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  z.z = a.z - b.z;
  z.w = a.w - b.w;
  return z; 
}

func v4f32 v4f32_sub(v4f32 a, v4f32 b) {
  v4f32 z = {0};
  z.x = a.x - b.x;
  z.y = a.y - b.y;
  z.z = a.z - b.z;
  z.w = a.w - b.w;
  return z; 
}

func v2s32 v2s32_mul(v2s32 a, v2s32 b) {
  v2s32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  return z; 
}

func v2f32 v2f32_mul(v2f32 a, v2f32 b) {
  v2f32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  return z;
}

func v3s32 v3s32_mul(v3s32 a, v3s32 b) {
  v3s32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  z.z = a.z * b.z;
  return z; 
}

func v3f32 v3f32_mul(v3f32 a, v3f32 b) {
  v3f32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  z.z = a.z * b.z;
  return z; 
}

func v4s32 v4s32_mul(v4s32 a, v4s32 b) {
  v4s32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  z.z = a.z * b.z;
  z.w = a.w * b.w;
  return z; 
}

func v4f32 v4f32_mul(v4f32 a, v4f32 b) {
  v4f32 z = {0};
  z.x = a.x * b.x;
  z.y = a.y * b.y;
  z.z = a.z * b.z;
  z.w = a.w * b.w;
  return z; 
}

func v2s32 v2s32_div(v2s32 a, v2s32 b) {
  v2s32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  return z;
}

func v2f32 v2f32_div(v2f32 a, v2f32 b) {
  v2f32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  return z;
}

func v3s32 v3s32_div(v3s32 a, v3s32 b) {
  v3s32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  z.z = a.z / b.z;
  return z; 
}

func v3f32 v3f32_div(v3f32 a, v3f32 b) {
  v3f32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  z.z = a.z / b.z;
  return z; 
}

func v4s32 v4s32_div(v4s32 a, v4s32 b) {
  v4s32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  z.z = a.z / b.z;
  z.w = a.w / b.w;
  return z;
}

func v4f32 v4f32_div(v4f32 a, v4f32 b) {
  v4f32 z = {0};
  z.x = a.x / b.x;
  z.y = a.y / b.y;
  z.z = a.z / b.z;
  z.w = a.w / b.w;
  return z;
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


////////////////////////////////////////
// NOTE(iyaan): Strings

u64 cstring_len(char* cstring) {
  char *ptr = cstring;
  u64 i;
  for (i = 0; ptr[i] != 0; i++)
    ;
  return i;
}

string8 string8_from_cstring_cloned(Allocator* allocator, char *cstring) {
  string8 str = {0};
  u64 cstr_len = cstring_len(cstring);

  u8* str_data = new_array(allocator, u8, cstr_len + 1);
  if (str_data == NULL) {
    return str;
  }
  MemCopy(str_data, cstring, cstr_len + 1);
  str.str = str_data;
  str.size = cstr_len;
  return str;
}

string8 string8_from_cstring(char *cstring) {
  string8 str = {0};
  str.size = cstring_len(cstring);
  str.str = cstring;
  return str;
}

string8 string8_substr(Allocator* allocator, string8 str, u64 start, u64 end) {
  string8 ret_str = {0};
  u64 len = (end - start) + 1;
  u8* ptr = new_array(allocator, u8, len + 1);
  if (ptr == NULL) {
    return ret_str;
  }
  u8* start_offset = ByteOffset(str.str, start);
  MemCopy(ptr, start_offset, len);
  ret_str.size = len;
  ret_str.str = ptr;
  return ret_str;
}

b8 string8_equal(string8 a, string8 b) {
  if (a.size != b.size) {
    return 0;
  }
  
  b8 same_same = (b8)MemCmp(a.str, b.str, a.size);
  return same_same;
}

func char* string8_to_cstring(Allocator* allocator, string8 str) {
  u8* ptr = new_array(allocator, u8, str.size + 1);
  if (ptr == NULL) {
    return (char*)0;
  }

  MemCopy(ptr, str.str, str.size);
  return ptr;
}


func Bool string8_is_ascii_space(u8 byte) {
  if (byte == ' ' || byte == '\t' || byte == '\n' || byte == '\r') {
    return 1;
  }
  else {
    return 0;
  }
}

func string8 string8_cat(Allocator* allocator, string8 a, string8 b) {
  string8 str = { 0 };
  const u64 str_size = a.size + b.size;
  u8* ptr = new_array(allocator, u8, str_size + 1);
  if (ptr == NULL) {
    return str;
  }
  str.str = ptr;
  str.size = str_size;
  MemCopy(str.str, a.str, a.size);
  MemCopy(str.str + a.size, b.str, b.size);
  return str;
}

func Bool string8_contains(string8 hay, string8 needle) {
  if (hay.size < needle.size) {
    return 0;
  }
  const s64 min_size = hay.size - needle.size;
  for (s64 i = 0; i < min_size; i++) {
    if (hay.str[i] == needle.str[0]) {
      const char* hay_ptr_offset = ByteOffset(hay.str, i);
      if MemCmp(hay_ptr_offset, needle.str, needle.size) {
        return 1;
      }
    }
  }
}

#define TMP_BUFFER_SIZE 128
func string8 string8_fmt(Allocator* allocator, const char* format, ...) {
  va_list args;
  string8 ret_str = { 0 };
  u8 temp_buffer[TMP_BUFFER_SIZE] = { 0 };
  
  va_start(args, format);
  int result = vsnprintf(temp_buffer, TMP_BUFFER_SIZE, format, args);
  va_end(args);
  
  if (result < 0) {
    return ret_str;
  }

  if (result >= TMP_BUFFER_SIZE) {
    // Truncated
    temp_buffer[TMP_BUFFER_SIZE - 1] = '\0';
  }

  u8* ptr = new_array(allocator, u8, result + 1);
  if (ptr == NULL) {
    return ret_str;
  }
  ret_str.str = ptr;
  MemCopy(ret_str.str, temp_buffer, result);
  ret_str.size = result;
  return ret_str;
}