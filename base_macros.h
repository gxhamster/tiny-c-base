#ifndef BASE_MACROS_H_
#define BASE_MACROS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#elif defined(__GNUC__)
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

#define Panic(msg) panic(msg)
void panic(char* msg) {
  fprintf(stderr, "panic: %s\n", msg);
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

#define MemCopy(d, s, z) memmove((d), (s), (z))
#define MemCopyStruct(d, s) MemCopy(d, s, Min(sizeof((*d)), sizeof((*s))))
#define MemCopyArray(d, s) MemCopy(d, s, Min(sizeof((d)), sizeof((s))))

#define AlignUp(v,a) (((v) + ((a) - 1)) & ~((a) - 1))
#define AlignDown(v,a) ((v) & ~((a) - 1))

#define EvalPrint(x) printf("%s = %d\n", #x, (x))

#endif // BASE_MACROS_H_
