#ifndef BASE_STRINGS_H_
#define BASE_STRINGS_H_

#include <stdarg.h>
#include "base_types.h"
#include "base_allocator.h"

////////////////////////////////////////
/// Strings: Count based strings with methods
/// to convert between normal cstrings. These strings
/// will require an allocator.

// NOTE(iyaan): string8 will not count the
// null terminator in its size
typedef struct {
  u8* str;
  u64 size;
} string8;

// Public Interface for Strings

string8 string8_from_cstring(char *cstring);
string8 string8_from_cstring_cloned(Allocator* allocator, char *cstring);
string8 string8_substr(Allocator* allocator, string8 str, u64 start, u64 end);
bool string8_equal(string8 a, string8 b);
char* string8_to_cstring(Allocator* allocator, string8 str);
bool string8_is_ascii_space(u8 byte);
string8 string8_cat(Allocator* allocator, string8 a, string8 b);
bool string8_contains(string8 hay, string8 needle);
string8 string8_fmt(Allocator* allocator, const char* format, ...);
string8 string8_split(Allocator* allocator, string8 sep);

#ifdef BASE_IMPL

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
  char* start_offset = ByteOffset(str.str, start);
  MemCopy(ptr, start_offset, len);
  ret_str.size = len;
  ret_str.str = ptr;
  return ret_str;
}

bool string8_equal(string8 a, string8 b) {
  if (a.size != b.size) {
    return 0;
  }

  b8 same_same = (b8)MemCmp(a.str, b.str, a.size);
  return same_same;
}

char* string8_to_cstring(Allocator* allocator, string8 str) {
  u8* ptr = new_array(allocator, u8, str.size + 1);
  if (ptr == NULL) {
    return (char*)0;
  }

  MemCopy(ptr, str.str, str.size);
  return ptr;
}


bool string8_is_ascii_space(u8 byte) {
  if (byte == ' ' || byte == '\t' || byte == '\n' || byte == '\r') {
    return 1;
  }
  else {
    return 0;
  }
}

string8 string8_cat(Allocator* allocator, string8 a, string8 b) {
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

bool string8_contains(string8 hay, string8 needle) {
  if (hay.size < needle.size) {
    return 0;
  }
  const s64 min_size = hay.size - needle.size;
  for (s64 i = 0; i < min_size; i++) {
    if (hay.str[i] == needle.str[0]) {
      const char* hay_ptr_offset = ByteOffset(hay.str, i);
      if MemCmp(hay_ptr_offset, needle.str, needle.size) {
        return true;
      }
    }
  }

  return false;
}

#define TMP_BUFFER_SIZE 128
string8 string8_fmt(Allocator* allocator, const char* format, ...) {
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

#endif // BASE_IMPL

#endif // BASE_STRINGS_H_
