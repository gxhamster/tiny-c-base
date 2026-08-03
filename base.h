#ifndef BASE_H_
#define BASE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

////////////////////////////////////////
// NOTE(iyaan): Detect compiler platform

#if defined(_MSC_VER)
#define COMPILER_CL 1
#if defined(_WIN32)
#define OS_WINDOWS 1
#else
#error missing OS detection
#endif

#if defined(_M_AMD64)
#define ARCH_X64 1
#elif defined(_M_I86)
#define ARCH_X86 1
// NOTE(iyaan): Need ARM64 for MSVC
#elif defined(_M_ARM)
#define ARCH_ARM 1
#else
#error missing ARCH detection
#endif

#elif defined(__clang__)
#define COMPILER_CLANG 1
#if defined(_WIN32)
#define OS_WINDOWS 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error missing OS detection
#endif

#if defined(__amd64__)
#define ARCH_X64 1
#elif defined(__i386__)
#define ARCH_X86 1
#elif defined(__arm__)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#endif

#elif defined(__GNUCC__)
#define COMPILER_GCC 1
#if defined(_WIN32)
#define OS_WINDOWS 1
#elif defined(__gnu_linux__)
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error missing OS detection
#endif

#if defined(__amd64__)
#define ARCH_X64 1
#elif defined(__i386__)
#define ARCH_X86 1
#elif defined(__arm__)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error missing ARCH detection
#endif
#else
#error unknown compiler
#endif

// NOTE(iyaan): Set zero values
#if !defined(COMPILER_CL)
#define COMPILER_CL 0
#endif
#if !defined(COMPILER_CLANG)
#define COMPILER_CLANG 0
#endif
#if !defined(COMPILER_GCC)
#define COMPILER_GCC 0
#endif
#if !defined(ARCH_X64)
#define ARCH_X64 0
#endif
#if !defined(ARCH_X86)
#define ARCH_X86 0
#endif
#if !defined(ARCH_ARM)
#define ARCH_ARM 0
#endif
#if !defined(ARCH_ARM64)
#define ARCH_ARM64 0
#endif
#if !defined(OS_WINDOWS)
#define OS_WINDOWS 0
#endif
#if !defined(OS_MAC)
#define OS_MAC 0
#endif
#if !defined(OS_LINUX)
#define OS_LINUX 0
#endif

////////////////////////////////////////
// NOTE(iyaan): Custom Assertions

#define Stmt(S) \
    do          \
    {           \
        S       \
    } while (0)
#define AssertBreak() (*(int *)0xff = 0)

#if ENABLE_ASSERT
#define Assert(expr, msg) Stmt(if (!(expr)) { default_assert_handler(#expr, msg, __FILE__, __LINE__, __func__); })
#else
#define Assert(expr, msg) \
    do                    \
    {                     \
    } while (0)
#endif

void default_assert_handler(const char *expr, const char *msg, const char *file, int line, const char *func)
{
    fprintf(stderr, "%s(%d:%s()) runtime assertion: %s, %s\n", file, line, func, expr, msg);
    abort();
}

////////////////////////////////////////
// NOTE(iyaan): Helper Macros

#define KB(x) (x << 10)
#define MB(x) (x << 20)
#define GB(x) (x << 30)

#define ArrayCount(a) (sizeof(a) / sizeof((*a)))
#define IntFromPtr(p) (unsigned long long)((char *)p - (char *)0)
#define PtrFromInt(i) (void *)((char *)0 + (n))
#define Member(T, m) (((*T)0)->m)
#define OffsetOfMember(T, m) IntFromPtr(&Member(T, m))
#define ByteOffset(ptr,off) (((char*)(ptr))+off)

#define Min(a, b) (((a) < (b)) ? (a) : (b))
#define Max(a, b) (((a) > (b)) ? (a) : (b))

#define global static
#define local static
#define func static

#define MemZero(p, z) memset((p), 0, (z))
#define MemZeroStruct(p) MemZero((p), sizeof((*p)))
#define MemZeroArray(p) MemZero((p), sizeof(p))

#define MemCmp(a, b, z) (memcmp((a), (b), (z)) == 0)

#define MemCopy(d, s, z) memmove((d), (s), (sz))
#define MemCopyStruct(d, s) MemCopy(d, s, Min(sizeof((*d)), sizeof((*s))))
#define MemCopyArray(d, s) MemCopy(d, s, Min(sizeof((d)), sizeof((s))))

#define AlignUp(v,a) (((v) + ((a) - 1)) & ~((a) - 1))
#define AlignDown(v,a) ((v) & ~((a) - 1))

#define EvalPrint(x) printf("%s = %d\n", #x, (x))

////////////////////////////////////////
// NOTE(iyaan): Basic Types

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef s8 b8;
typedef s16 b16;
typedef s32 b32;
typedef s64 b64;
typedef float f32;
typedef double f64;

const s8 MIN_S8 = (s8)0x80;
const s16 MIN_S16 = (s16)0x8000;
const s32 MIN_S32 = (s32)0x80000000;
const s64 MIN_S64 = (s64)0x8000000000000000llu;

const s8 MAX_S8 = (s8)0x7f;
const s16 MAX_S16 = (s16)0x7fff;
const s32 MAX_S32 = (s32)0x7fffffff;
const s64 MAX_S64 = (s64)0x7fffffffffffffffllu;

const u8 MAX_U8 = (u8)0xff;
const u16 MAX_U16 = (u16)0xffff;
const u32 MAX_U32 = (u32)0xffffffff;
const u64 MAX_U64 = (u64)0xffffffffffffffffllu;

////////////////////////////////////////
// NOTE(iyaan): Float constants

func f32 f32_inf(void);
func f32 f32_neg_inf(void);
func f64 f64_inf(void);
func f64 f64_neg_inf(void);

////////////////////////////////////////
// NOTE(iyaan): Floating point math

func f32 f32_abs(f32 x);
func f64 f64_abs(f64 x);

////////////////////////////////////////
// NOTE(iyaan): Compound Types

typedef union
{
    struct
    {
        s32 x;
        s32 y;
    };
    s32 v[2];
} v2s32;

typedef union
{
    struct
    {
        s32 x;
        s32 y;
        s32 z;
    };
    s32 v[3];
} v3s32;

typedef union
{
    struct
    {
        s32 x;
        s32 y;
        s32 z;
        s32 w;
    };
    s32 v[4];
} v4s32;

typedef union
{
    struct
    {
        f32 x;
        f32 y;
    };
    f32 v[2];
} v2f32;

typedef union
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
    };
    f32 v[3];
} v3f32;

typedef union
{
    struct
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    f32 v[4];
} v4f32;

////////////////////////////////////////
// NOTE(iyaan): Compound Types Helpers

func v2s32 v2s32_add(v2s32 a, v2s32 b);
func v2f32 v2f32_add(v2f32 a, v2f32 b);
func v3s32 v3s32_add(v3s32 a, v3s32 b);
func v3f32 v3f32_add(v3f32 a, v3f32 b);
func v4s32 v4s32_add(v4s32 a, v4s32 b);
func v4f32 v4f32_add(v4f32 a, v4f32 b);

func v2s32 v2s32_sub(v2s32 a, v2s32 b);
func v2f32 v2f32_sub(v2f32 a, v2f32 b);
func v3s32 v3s32_sub(v3s32 a, v3s32 b);
func v3f32 v3f32_sub(v3f32 a, v3f32 b);
func v4s32 v4s32_sub(v4s32 a, v4s32 b);
func v4f32 v4f32_sub(v4f32 a, v4f32 b);

func v2s32 v2s32_mul(v2s32 a, v2s32 b);
func v2f32 v2f32_mul(v2f32 a, v2f32 b);
func v3s32 v3s32_mul(v3s32 a, v3s32 b);
func v3f32 v3f32_mul(v3f32 a, v3f32 b);
func v4s32 v4s32_mul(v4s32 a, v4s32 b);
func v4f32 v4f32_mul(v4f32 a, v4f32 b);

func v2s32 v2s32_div(v2s32 a, v2s32 b);
func v2f32 v2f32_div(v2f32 a, v2f32 b);
func v3s32 v3s32_div(v3s32 a, v3s32 b);
func v3f32 v3f32_div(v3f32 a, v3f32 b);
func v4s32 v4s32_div(v4s32 a, v4s32 b);
func v4f32 v4f32_div(v4f32 a, v4f32 b);

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

#define AProc AProcReturn (*procedure)(void *data, AllocMode mode, u64 size, u64 alignment)

// typedef AProcReturn AllocatorProc(void *data, AllocMode mode, u64 size, u64 alignment);
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

#endif // BASE_H_
