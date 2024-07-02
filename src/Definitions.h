#pragma once

#include <iostream>
#include <cmath>
#include <vecpp.h>

#define FINFINITY 10e30

#define MIN(a, b) ((a) < (b) ? (a):(b))
#define MAX(a, b) ((a) > (b) ? (a):(b))

#define CLAMPMIN MAX
#define CLAMPMAX MIN
#define CLAMP(v, min, max) CLAMPMIN(CLAMPMAX(v, max), min)
#define SCLAMP(v, min, max) v = CLAMP(v, min, max)

#define ABS(x) ((x) < 0.0 ? -(x):(x))
#define IABS(x) ((x) > 0.0 ? -(x):(x))
#define SIGN(x) ((x) < 0.0 ? -1:1)

#define SQRT std::sqrt
#define CBRT std::cbrt
#define POW std::pow

#define PI 3.141592653f
#define MAX_ANGLE (PI*2)

#define RADIANS(deg) ((deg)/180.0*PI)

#define MALLOC(type, length) (type*)malloc((length)*sizeof(type))

using namespace vecpp;

struct rect {
    float x, y, w, h;
};

struct color {
    float r, g, b;
    float a = 1.0;
};

typedef unsigned int uint;
typedef const char* cstr;
typedef std::string string;

char numberString[12];

cstr numberToString(int num) {
    sprintf(numberString, "%d", num);

    return (cstr)numberString;
}

string floatString(float v, cstr fmt = "%.3f") {
    char result[12];

    sprintf(result, fmt, v);

    return string(result);
}

bool isEndsWith(std::string str, std::string ending) {
    if (str.length() < ending.length()) return false;

    return str.compare(str.length()-ending.length(), ending.length(), ending) == 0;
}

bool isStartsWith(std::string str, std::string starting) {
    if (str.length() < starting.length()) return false;

    return str.compare(0, starting.length(), starting) == 0;
}

float angleOfVector(float x, float y, float d = -1.0) {
    if (d < 0.0) d = SQRT(x*x+y*y);

    if (d < 0.0001) return 0.0;

    float a = acos(x/d);

    return y < 0.0 ? MAX_ANGLE-a:a;
}