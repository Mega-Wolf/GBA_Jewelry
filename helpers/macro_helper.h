
#pragma once

#if !NO_HEADERS
    //#include <stdlib.h>
    //#include <stdarg.h>
    //#include <stdio.h>
    #include <type_traits>
#endif

typedef int bool32;

typedef unsigned char       u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef volatile unsigned char       vu8;
typedef volatile unsigned short     vu16;
typedef volatile unsigned int       vu32;

typedef signed char       s8;
typedef signed short     s16;
typedef signed int       s32;
typedef volatile signed char       vs8;
typedef volatile signed short     vs16;
typedef volatile signed int       vs32;

typedef unsigned char   uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

typedef char int8;
typedef short int16;
typedef int int32;

typedef float float32;
typedef float f32;
typedef volatile float vf32;

// // const  uint8  UINT8_MAX = 0xff;
// // const uint16 UINT16_MAX = 0xffff;
// // const uint32 UINT32_MAX = 0xffffffff;
// // const uint64 UINT64_MAX = 0xffffffffffffffff;

// // const  int8  INT8_MAX = 0x7f;
// // const int16 INT16_MAX = 0x7fff;
// // const int32 INT32_MAX = 0x7fffffff;
// // const int64 INT64_MAX = 0x7fffffffffffffff;

// // const  int8  INT8_MIN = -0x7f - 1;
// // const int16 INT16_MIN = -0x7fff - 1;
// // const int32 INT32_MIN = 0x80000000;
// // const int64 INT64_MIN = 0x8000000000000000;

// TODO: Where to put the rand stuff

u32 RandomSeed;

inline void srand(u32 seed) {
    RandomSeed = seed;
}

inline u32 rand() {
    RandomSeed = 1664525 * RandomSeed + 1013904223;
    return (RandomSeed >> 16) & 0x7FFF;
}

inline int32 RandRange(int32 min, int32 max) {
    return ((rand() * (max - min)) >> 15) + min;
}

#define internal static
#define local_persist static
#define global_variable static

#define kB (1024LL)
#define MB (1024LL * kB)

// // ### Errors, etc. ###

// // TODO: UNREFERENCED_PARAMETER is windows
// #define UNUSED_PARAM(param) UNREFERENCED_PARAMETER(param)
#define UNUSED_PARAM(param) (void*) (param);

// #define Throw() \
// { \
//     char* ptr = nullptr; \
//     *ptr = 'X'; \
// }

inline void Throw() {
    char* ptr = nullptr; \
    *ptr = 'X'; \
}

#if NDEBUG
inline void Assert(bool condition, char* errorMsg, ...) { __assume(condition); }
#else
inline void Assert(bool condition, char* errorMsg, ...) {
    if (!condition) {
        //va_list args;
        //va_start(args, errorMsg);
        // TODO: Implement printf
        // fprintf(stderr, "Wrong assertion error:\n\t");
        // vfprintf(stderr, errorMsg, args);
        // fprintf(stderr, "\n");
        //va_end(args);
        Throw();
    }
}
#endif

#define UNION_STRUCT(structName, variables, type, combineName) \
    union { \
        struct structName { \
            variables \
        }; \
        struct { \
            variables \
        }; \
        type combineName [sizeof(structName) / sizeof(type)]; \
    };

#define NAMED_AND_UNNAMED(structName, text, varName) \
    union { \
        struct structName { \
            text \
        } varName; \
        struct { \
            text \
        }; \
    };

inline void Unimplemented(char* msg) {
    // fprintf(stderr, "Unimplemented: %s\n", msg);
    // Throw();
}

inline void Error(char* msg, ...) {
    // va_list args;
    // va_start(args, msg);
    // fprintf(stderr, "Error:\n\t");
    // vfprintf(stderr, msg, args);
    // fprintf(stderr, "\n");
    // va_end(args);

    // getchar();
    // exit(-1);
}

template<typename T>
T MAX(T x, T y) {
    if (x > y) {
        return x;
    }
    return y;
}

template<typename T>
T MIN(T x, T y) {
    if (x < y) {
        return x;
    }
    return y;
}

#define AT_LEAST MAX
#define AT_MOST MIN

template<typename T>
T CLAMP(T value, T min, T max) {
    return AT_MOST(AT_LEAST((value), (min)), (max));
}

// TODO: Not only do I not know exactly anymore what deferFinally is; I also think it should be (end) ?
#define defer(start, end) start; for (int _i_ = 0; _i_ < 1; ++_i_, (end))
#define deferIf(start, end) for (int _i_ = (start) ? 0 : 1; _i_ < 1; ++_i_, (end))
#define deferFinally(start, end) for (int _i_ = (start) ? 0 : 1; _i_ < 1 || (end, false); ++_i_)
#define deferSkipEnd break
#define deferFinish continue

#define FunctionPointer(name, ret, ...) ret (*name) (__VA_ARGS__)


template<class T>
void Swap(T* x, T* y) {
    T z = *x;
    *x = *y;
    *y = z;
}

template<class T>
void Shuffle(T* array, int globalElementAmount) {
    for (int i = globalElementAmount; --i >= 1;) {
        int j = rand() % (i + 1);
        Swap(&array[i], &array[j]);
    }
}



// Glue strings

#define MACRO_NAME_TO_STRING_(x) #x
#define MACRO_NAME_TO_STRING(x) MACRO_NAME_TO_STRING_(x)

#define MACRO_GLUE_WITH_UNDERSCORE_(x, y) x ## _ ## y
#define MACRO_GLUE_WITH_UNDERSCORE(x, y) MACRO_GLUE_WITH_UNDERSCORE_(x, y)

// // Testing

// #ifdef NDEBUG
// #define WHILE_TRUE while(true)
// #else
// #define WHILE_TRUE \
// for (int iiiiiiiiii = 0; iiiiiiiiii < 5000; ++iiiiiiiiii) \
// if (iiiiiiiiii == 5000 - 1) { \
//     /*Error("You reached an endless loop\n");*/ \
// } \
// else
// #endif

// #ifdef NDEBUG
// #define WHILE(condition) while(condition)
// #else
// #define WHILE(condition) \
// for (int iiiiiiiii = 0; iiiiiiiii < 5000 && (condition); ++iiiiiiiii) \
// if (iiiiiiiii == 5000 - 1) { \
//     Error("You reached an endless loop\n"); \
// } \
// else
// #endif

#define inc(variable, start, max_comp) for (int variable = (start); variable < (max_comp); ++variable)
#define inc0(variable, max_comp) for (int variable = 0; variable < (max_comp); ++variable)

#define inc_t(variable, start, max_comp) for (uint32 variable = (start); variable < (max_comp); ++variable)
#define inc0_t(variable, max_comp) for (uint32 variable = 0; variable < (max_comp); ++variable)

#define dec(variable, start, min_comp) for (int variable = (start); --variable >= (min_comp); )
#define dec0(variable, start) for (int variable = (start); --variable >= 0; )

#define ArrayCount(array) (sizeof(array) / sizeof((array)[0]))

// #pragma region [Enum magic]

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // constexpr T operator~(T lhs) {
// //     return static_cast<T>(
// //         ~static_cast<typename std::underlying_type<T>::type>(lhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // constexpr T operator|(T lhs, T rhs) {
// //     return static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) |
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // constexpr T operator&(T lhs, T rhs) {
// //     return static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) &
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // constexpr T operator^(T lhs, T rhs) {
// //     return static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) ^
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // void operator|=(T& lhs, T rhs) {
// //     lhs = static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) |
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // void operator&=(T& lhs, T rhs) {
// //     lhs = static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) &
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// // template <typename T = typename std::enable_if<std::is_enum<T>::value, T>::type>
// // void operator^=(T& lhs, T rhs) {
// //     lhs = static_cast<T>(
// //         static_cast<typename std::underlying_type<T>::type>(lhs) ^
// //         static_cast<typename std::underlying_type<T>::type>(rhs)
// //     );
// // }

// #pragma endregion

#pragma region [For Each Macro]

#define EXPAND(x) x
#define FOR_EACH_1(what, x, ...) what x;
#define FOR_EACH_2(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_1(what,  __VA_ARGS__))
#define FOR_EACH_3(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_2(what, __VA_ARGS__))
#define FOR_EACH_4(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_3(what,  __VA_ARGS__))
#define FOR_EACH_5(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_4(what,  __VA_ARGS__))
#define FOR_EACH_6(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_5(what,  __VA_ARGS__))
#define FOR_EACH_7(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_6(what,  __VA_ARGS__))
#define FOR_EACH_8(what, x, ...)\
  what x;\
  EXPAND(FOR_EACH_7(what,  __VA_ARGS__))
#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
#define CONCATENATE(x,y) x##y
#define FOR_EACH_(N, what, ...) EXPAND(CONCATENATE(FOR_EACH_, N)(what, __VA_ARGS__))
#define FOR_EACH(what, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), what, __VA_ARGS__)

#pragma endregion

#define ROUND_UP(value, roundValue) ((((value) + (roundValue) - 1) / (roundValue)) * (roundValue))

#define CAT1(a,b) a ## b
#define CAT2(a,b) CAT1(a,b)
#define CAT(a,b)  CAT2(a,b)
#define _i_ CAT(_i_, __LINE__)

#define MACRO_VAR(name) CAT(name, __LINE__)


// enum system_print_color {
//     PRINT_BLACK = 30,
//     PRINT_RED,
//     PRINT_GREEN,
//     PRINT_YELLOW,
//     PRINT_BLUE,
//     PRINT_MAGENTA,
//     PRINT_CYAN,
//     PRINT_WHITE,

//     PRINT_BACKGROUND = 10,
//     PRINT_BRIGHT = 60,
// };

// #ifndef NDEBUG_PRINTING
//     #define PrintDebugC(color, _Format, ...) \
//         printf("\x1b[%dm" _Format "\x1b[0m", color, __VA_ARGS__);
//     #define PrintDebug(_Format, ...) \
//         printf(_Format, __VA_ARGS__);
// #else
//     #define PrintDebugC(color, _Format, ...)
//     #define PrintDebug(_Format, ...)
// #endif

#define CAST(type, value) (*((type*) &(value)))

#define INDEX_2D(x, y, width) ((x) + (y) * (width))



// // TODO: This does not belong here; it plays together with metaprogramming and therefore I might want to group it with that


// unsigned int PrintEnumSN(unsigned int value, char* buffer, size_t bufferCount, char** names, unsigned int* values, int size, bool isFlags, bool usesComplexArray) {
//     if (isFlags) {
//         int amount = 0;
//         bool found = false;
//         for (unsigned int i = 1U << 31U; i != 0U; i >>= 1U) {
//             if ((value & i) == 0) { continue; }
//             inc0 (value_i,   size) {
//                 if (values[value_i] == i) {
//                     if (found) {
//                         amount += snprintf(&buffer[amount], bufferCount - amount, " | ");
//                     }
//                     amount += snprintf(&buffer[amount], bufferCount - amount, "%s", names[value_i]);
//                     found = true;
//                     break;
//                 }
//             }
//         }
//         if (!found) {
//             inc0 (i,   size) {
//                 if (values[i] == 0) {
//                     return snprintf(buffer, bufferCount, "%s", names[i]);
//                 }
//             }
//             return snprintf(buffer, bufferCount, "-");
//         }
//         return amount;
//     }

//     if (!usesComplexArray) {
//         return snprintf(buffer, bufferCount, "%s", names[value]);
//     } else {
//         inc0 (i,   size) {
//             if (values[i] == value) {
//                 return snprintf(buffer, bufferCount, "%s", names[i]);
//             }
//         }

//         return snprintf(buffer, bufferCount, "[%d (%c)]", value, value);
//     }
// }

// // uint32 int_dummy_values[] = {
// //      0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
// //     10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
// //     20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
// //     30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
// //     40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
// //     50, 51, 52, 53, 54, 55, 56, 57, 58, 59,
// //     60, 61, 62, 63
// // };

void memcpy32(void* dst, void* src, int size) {
    int* dstInt = (int*) dst;
    int* srcInt = (int*) src;
    inc0 (i,   size / 4) {
        dstInt[i] = srcInt[i];
    }
}