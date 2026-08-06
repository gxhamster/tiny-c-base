#ifndef BASE_TYPES_H_
#define BASE_TYPES_H_
  
////////////////////////////////////////
// NOTE(iyaan): Basic Types

#include <stdint.h>
#include "base_macros.h"

#define True 1
#define False 0

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
typedef b8 Bool;
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

#endif // BASE_TYPES_H_