#ifndef BASE_STRINGS_H_
#define BASE_STRINGS_H_

#include "base_types.h"
#include "base_allocator.h"

////////////////////////////////////////
// NOTE(iyaan): Strings


// NOTE(iyaan): string8 will not count the
// null terminator in its size
typedef struct {
  u8* str;
  u64 size;
} string8;

func string8 string8_from_cstring(char *cstring);
func string8 string8_from_cstring_cloned(Allocator* allocator, char *cstring);
func string8 string8_substr(Allocator* allocator, string8 str, u64 start, u64 end);
func Bool string8_equal(string8 a, string8 b);
func char* string8_to_cstring(Allocator* allocator, string8 str);
func Bool string8_is_ascii_space(u8 byte);
func string8 string8_cat(Allocator* allocator, string8 a, string8 b);
func Bool string8_contains(string8 hay, string8 needle);
func string8 string8_fmt(Allocator* allocator, const char* format, ...);
func string8 string8_split(Allocator* allocator, string8 sep);

#endif // BASE_STRINGS_H_