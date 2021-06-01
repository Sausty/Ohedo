#ifndef OHEDO_TYPES
#define OHEDO_TYPES

#include <stdint.h> // uint32_t, int32_t etc
#include <string.h> // memcpy, memset etc
#include <stdlib.h> // malloc, calloc etc

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;
typedef float f32;

// Graphics
typedef u32 RenderID;

#define Ohedo_Define_Struct(name) typedef struct name name;
#define Ohedo_Define_Enum(name) typedef enum name name;

// Macros
#define foreach(i, count) \
    for(i32 i=0; i < (count); ++i)

#define array_count(arr) \
    ( sizeof(arr) / sizeof(*arr) )

#define kilobytes(x) (x            * 1024)
#define megabytes(x) (kilobytes(x) * 1024)
#define gigabytes(x) (megabytes(x) * 1024)

#define offset_ptr_bytes(type, ptr, offset) ((type*)((u8*)ptr + (offset)))

#endif