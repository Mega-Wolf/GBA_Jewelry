#pragma once

// TODO: Is this still necessary given that there is the handmade maths file (which I btw do not use here apparently)

#include "macro_helper.h"

int32 RoundFloat32ToInt32(float32 in) {
    // TODO: Intrinsic?
    return (int32) (in + 0.5f);
}

uint32 RoundFloat32ToUInt32(float32 in) {
    // TODO: Intrinsic?
    return (uint32) (in + 0.5f);
}

#pragma region [vec2i]

struct vec2f {
    union {
        struct {
            float32 X;
    	    float32 Y;
        };
        float32 Data[2];
    };

    // NOTE: Is that possible somehow
    //explicit operator vec2i() { return vec2i({(int32) X, (int32) Y}); }
};

struct vec2i {
    union {
        struct {
            int32 X;
    	    int32 Y;
        };
        int32 Data[2];
    };

    // NOTE: Ugly because of metaprogramming
    operator vec2f() { return vec2f({(float32) X, (float32) Y}); }
};

vec2i operator+(vec2i vec1, vec2i vec2) {
    return vec2i{ vec1.X + vec2.X, vec1.Y + vec2.Y};
}

vec2i operator-(vec2i vec1, vec2i vec2) {
    return vec2i{ vec1.X - vec2.X, vec1.Y - vec2.Y};
}

void operator+=(vec2i &vec, vec2i vec2) {
    vec.X += vec2.X;
    vec.Y += vec2.Y;
}

void operator-=(vec2i &vec, vec2i vec2) {
    vec.X -= vec2.X;
    vec.Y -= vec2.Y;
}

vec2i operator-(vec2i vec) {
    return vec2i{ -vec.X, -vec.Y };
}

vec2i operator*(vec2i vec, int32 scalar) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator*(vec2i vec, float32 scalar) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2i operator*(int32 scalar, vec2i vec) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator*(float32 scalar, vec2i vec) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2i operator/(vec2i vec, int32 scalar) {
    return { vec.X / scalar, vec.Y / scalar };
}

vec2f operator/(vec2i vec, float32 scalar) {
    return { vec.X / scalar, vec.Y / scalar };
}

vec2i operator%(vec2i vec, int32 scalar) {
    return { vec.X % scalar, vec.Y % scalar };
}

void operator*=(vec2i &vec, int32 scalar) {
    vec.X *= scalar;
    vec.Y *= scalar;
}

// void operator*=(vec2i &vec, float32 scalar) {
//     vec.X *= scalar;
//     vec.Y *= scalar;
// }

// void operator*=(int32 scalar, vec2i &vec) {
//     vec.X *= scalar;
//     vec.Y *= scalar;
// }

// void operator*=(float32 scalar, vec2i &vec) {
//     vec.X *= scalar;
//     vec.Y *= scalar;
// }

void operator/=(vec2i &vec, int32 scalar) {
    vec.X /= scalar;
    vec.Y /= scalar;
}

// void operator/=(vec2i &vec, float32 scalar) {
//     vec.X /= scalar;
//     vec.Y /= scalar;
// }

void operator%=(vec2i &vec, int32 scalar) {
    vec.X %= scalar;
    vec.Y %= scalar;
}

bool operator==(vec2i vec1, vec2i vec2) {
    return vec1.X == vec2.X && vec1.Y == vec2.Y;
}

bool operator!=(vec2i vec1, vec2i vec2) {
    return !(vec1.X == vec2.X && vec1.Y == vec2.Y);
}

#pragma endregion

#pragma region [vec2f]

vec2f operator+(vec2f vec1, vec2f vec2) {
    return vec2f{ vec1.X + vec2.X, vec1.Y + vec2.Y};
}

vec2f operator-(vec2f vec1, vec2f vec2) {
    return vec2f{ vec1.X - vec2.X, vec1.Y - vec2.Y};
}

void operator+=(vec2f &vec, vec2f vec2) {
    vec.X += vec2.X;
    vec.Y += vec2.Y;
}

void operator-=(vec2f &vec, vec2f vec2) {
    vec.X -= vec2.X;
    vec.Y -= vec2.Y;
}

vec2f operator-(vec2f vec) {
    return vec2f{ -vec.X, -vec.Y };
}

vec2f operator*(vec2f vec, int32 scalar) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator*(vec2f vec, float32 scalar) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator*(int32 scalar, vec2f vec) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator*(float32 scalar, vec2f vec) {
    return { vec.X * scalar, vec.Y * scalar };
}

vec2f operator/(vec2f vec, int32 scalar) {
    return { vec.X / scalar, vec.Y / scalar };
}

vec2f operator/(vec2f vec, float32 scalar) {
    return { vec.X / scalar, vec.Y / scalar };
}

void operator*=(vec2f &vec, int32 scalar) {
    vec.X *= scalar;
    vec.Y *= scalar;
}

void operator*=(vec2f &vec, float32 scalar) {
    vec.X *= scalar;
    vec.Y *= scalar;
}

// void operator*=(int32 scalar, vec2f &vec) {
//     vec.X *= scalar;
//     vec.Y *= scalar;
// }

// void operator*=(float32 scalar, vec2f &vec) {
//     vec.X *= scalar;
//     vec.Y *= scalar;
// }

void operator/=(vec2f &vec, int32 scalar) {
    vec.X /= scalar;
    vec.Y /= scalar;
}

void operator/=(vec2f &vec, float32 scalar) {
    vec.X /= scalar;
    vec.Y /= scalar;
}

bool operator==(vec2f vec1, vec2f vec2) {
    return vec1.X == vec2.X && vec1.Y == vec2.Y;
}

bool operator!=(vec2f vec1, vec2f vec2) {
    return !(vec1.X == vec2.X && vec1.Y == vec2.Y);
}

vec2i vec2f_vec2i(vec2f vec) {
    return { RoundFloat32ToInt32(vec.X), RoundFloat32ToInt32(vec.Y) };
}


float32 dot(vec2f a, vec2f b) {
    return a.X * b.X + a.Y * b.Y;
}

inline vec2f rotateRet(vec2f vec, float32 rad) {
    float32 cosAlpha = cosf(rad);
    float32 sinAlpha = sinf(rad);
    vec2f ret;
    ret.X = cosAlpha * vec.X + -sinAlpha * vec.Y;
    ret.Y = sinAlpha * vec.X +  cosAlpha * vec.Y;
    return ret;
}

inline void rotateThis(vec2f* vec, float32 rad) {
    float32 cosAlpha = cosf(rad);
    float32 sinAlpha = sinf(rad);
    vec2f n;
    n.X = cosAlpha * vec->X + -sinAlpha * vec->Y;
    n.Y = sinAlpha * vec->X +  cosAlpha * vec->Y;
    *vec = n;
}


#pragma endregion

template<typename T>
bool BoxContains(T left, T top, T right, T bottom, T x, T y) {
    return 
        x >= left &&
        x <= right &&
        y >= top &&
        y <= bottom;
}

#define LERP(x, y, t) ((t)*(y) + (1.0f - (t)) * (x))
#define InvLerp(x, y, V) (((V) - (x)) / ((y) - (x)))

template<typename T>
T RemapLinear(T inputMin, T inputMax, T outputMin, T outputMax, T value) {
    float t = InvLerp(inputMin, inputMax, value);
    return Lerp(outputMin, outputMax, t);
}

#define INDEX_2(x, y, width) ((y) * (width) + (x))
#define INDEX_2_VEC(vec, width) ((vec.Y) * (width) + (vec.X))

template<typename T>
bool BetweenInIn(T value, T min, T max) {
    Assert(min <= max, "Min is bigger than max");
    return value >= min && value <= max;
}

template<typename T>
bool BetweenInEx(T value, T min, T max) {
    Assert(min <= max, "Min is bigger than max");
    return value >= min && value < max;
}

// TODO: Intrinsic ?
template<typename T>
T Abs(T value) {
    if (value > 0) {
        return value;
    } else {
        return -value;
    }
}

template<typename T>
T MinFromAray(T* values, int32 valueCount) {
    T min = values[0];
    inc (i,   1,    valueCount) {
        T value = values[i];
        if (value < min) {
            min = value;
        }
    }
    return min;
}

template<typename T>
T MaxFromAray(T* values, int32 valueCount) {
    T max = values[0];
    inc (i,   1,    valueCount) {
        T value = values[i];
        if (value > max) {
            max = value;
        }
    }
    return max;
}

#define PI 3.1415926535897f