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


