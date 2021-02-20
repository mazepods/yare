#pragma once

// Boolean type
typedef int                 b32;
typedef char                b8;

// Integer types
typedef unsigned char       u8;
typedef signed char         i8;
typedef unsigned short      u16;
typedef signed short        i16;
typedef unsigned int        u32;
typedef signed int          i32;
typedef unsigned long long  u64;
typedef signed long long    i64;

// Floating point types
typedef float               f32;
typedef double              f64;

#define TRUE    1
#define FALSE   0

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif

// Verify all types are of the expected size.
STATIC_ASSERT(sizeof(u8) == 1, "Expect u8 to be 1 byte.");
STATIC_ASSERT(sizeof(i8) == 1, "Expect i8 to be 1 byte.");
STATIC_ASSERT(sizeof(u16) == 2, "Expect u16 to be 2 byte.");
STATIC_ASSERT(sizeof(i16) == 2, "Expect i16 to be 2 byte.");
STATIC_ASSERT(sizeof(u32) == 4, "Expect u32 to be 4 byte.");
STATIC_ASSERT(sizeof(i32) == 4, "Expect i32 to be 4 byte.");
STATIC_ASSERT(sizeof(u64) == 8, "Expect u64 to be 8 byte.");
STATIC_ASSERT(sizeof(i64) == 8, "Expect i64 to be 8 byte.");
STATIC_ASSERT(sizeof(f32) == 4, "Expect f32 to be 4 byte.");
STATIC_ASSERT(sizeof(f64) == 8, "Expect f64 to be 8 byte.");

//TODO: Platform detection

// Exports & Imports
#ifdef YEXPORT
#define YAPI __attribute__((visibility("default")))
#else
#define YAPI
#endif