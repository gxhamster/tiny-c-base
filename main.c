#define ENABLE_ASSERT 1

#include "base.h"
#include "base.c"

int main(void) {
  const u64 arena_size = MB(1);
  void* arena_mem = malloc(arena_size);
  Arena arena = {0};
  arena_init(&arena, arena_mem, arena_size);
  Allocator allocator = arena_allocator(&arena);

  char *str1 = "hello world";
  char* str5 = "hello porld";
  string8 str2 = string8_from_cstring(str1);
  string8 str3 = string8_from_cstring_cloned(&allocator, str1);
  string8 str4 = string8_from_cstring_cloned(&allocator, str5);
  string8 str_sub = string8_substr(&allocator, str3, 1, 3);
  string8 str6 = string8_from_cstring_cloned(&allocator, "jello");
  
  // Dynamic Arrays
  dynamic_array dyn = dynamic_array_init(allocator, 64, sizeof(string8));
  dynamic_array_push(&dyn, &str2);
  dynamic_array_push(&dyn, &str3);
  dynamic_array_push(&dyn, &str4);
  dynamic_array_push(&dyn, &str_sub);
  dynamic_array_push(&dyn, &str6);

  Bool equal = string8_equal(str2, str4);
  Bool contains = string8_contains(str3, str6);

  {
    string8 cat_str = string8_from_cstring_cloned(&allocator, "");
    u64 count = 0;
    while (1) {
      string8 str = string8_fmt(&allocator, "BEEF %d", count++);
      if (str.str == 0) {
        break;
      }
      string8 new_cat_str = string8_cat(&allocator, cat_str, str);
      printf("%llu = %s\n", arena.offset, new_cat_str.str);
    }
  }
  
  free_all(&allocator);
}

