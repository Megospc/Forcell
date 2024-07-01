// vecpp by Megospc
// GitHub: https://github.com/Megospc/vecpp
// Vesion: 1.7.3 (24.04.2024)

#pragma once

#include <iostream>
#include <cmath>

namespace vecpp {
    typedef float vec1;
    typedef double dvec1;
    typedef bool bvec1;

    struct bvec2 {
        bool x, y;

        bvec2() {
            x = 0.0, y = 0.0;
        }
        bvec2(bool x, bool y) {
            this->x = x, this->y = y;
        }
        bvec2(bool v) {
            x = v, y = v;
        }
        bvec2(bvec2* v) {
            x = v->x, y = v->y;
        }
        
        bvec2 xy() {
            return bvec2(x, y);
        }
        bvec2 yx() {
            return bvec2(y, x);
        }
        
        void xy(bvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(bvec2 value) {
            y = value.x, x = value.y;
        }

        bvec2 operator!() {
            return bvec2(-x, -y);
        }
        
        bool operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                default: return false;
            }
        }
        
        bool all() {
            return x && y;
        }
        bool any() {
            return x || y;
        }

        bvec2 operator==(bvec2 other) {
            return bvec2(x == other.x, y == other.y);
        }
        bvec2 operator!=(bvec2 other) {
            return bvec2(x != other.x, y != other.y);
        }

        bvec2 operator==(bool other) {
            return bvec2(x == other, y == other);
        }
        bvec2 operator!=(bool other) {
            return bvec2(x != other, y != other);
        }
    };

    struct bvec3 {
        bool x, y, z;

        bvec3() {
            x = 0.0, y = 0.0, z = 0.0;
        }
        bvec3(bool x, bool y, bool z) {
            this->x = x, this->y = y, this->z = z;
        }
        bvec3(bvec2 a, bool b) {
            x = a.x, y = a.y, z = b;
        }
        bvec3(bool a, bvec2 b) {
            x = a, y = b.x, z = b.y;
        }
        bvec3(bool v) {
            x = v, y = v, z = v;
        }
        bvec3(bvec3* v) {
            x = v->x, y = v->y, z = v->z;
        }
        
        bvec2 xy() {
            return bvec2(x, y);
        }
        bvec2 yx() {
            return bvec2(y, x);
        }
        bvec2 xz() {
            return bvec2(x, z);
        }
        bvec2 zx() {
            return bvec2(z, x);
        }
        bvec2 yz() {
            return bvec2(y, z);
        }
        bvec2 zy() {
            return bvec2(z, y);
        }
        bvec3 xyz() {
            return bvec3(x, y, z);
        }
        bvec3 xzy() {
            return bvec3(x, z, y);
        }
        bvec3 yxz() {
            return bvec3(y, x, z);
        }
        bvec3 yzx() {
            return bvec3(y, z, x);
        }
        bvec3 zxy() {
            return bvec3(z, x, y);
        }
        bvec3 zyx() {
            return bvec3(z, y, x);
        }
        
        void xy(bvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(bvec2 value) {
            y = value.x, x = value.y;
        }
        void xz(bvec2 value) {
            x = value.x, z = value.y;
        }
        void zx(bvec2 value) {
            z = value.x, x = value.y;
        }
        void yz(bvec2 value) {
            y = value.x, z = value.y;
        }
        void zy(bvec2 value) {
            z = value.x, y = value.y;
        }
        void xyz(bvec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(bvec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(bvec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(bvec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(bvec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(bvec3 value) {
            z = value.x, y = value.y, x = value.z;
        }

        bvec3 operator!() {
            return bvec3(-x, -y, -z);
        }
        
        bool operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: return false;
            }
        }
        
        bool all() {
            return x && y && z;
        }
        bool any() {
            return x || y || z;
        }

        bvec3 operator==(bvec3 other) {
            return bvec3(x == other.x, y == other.y, z == other.z);
        }
        bvec3 operator!=(bvec3 other) {
            return bvec3(x != other.x, y != other.y, z != other.z);
        }

        bvec3 operator==(bool other) {
            return bvec3(x == other, y == other, z == other);
        }
        bvec3 operator!=(bool other) {
            return bvec3(x != other, y != other, z != other);
        }
    };

    struct bvec4 {
        bool x, y, z, w;

        bvec4() {
            x = 0.0, y = 0.0, z = 0.0, w = 0.0;
        }
        bvec4(bool x, bool y, bool z, bool w) {
            this->x = x, this->y = y, this->z = z, this->w = w;
        }
        bvec4(bvec3 a, bool b) {
            x = a.x, y = a.y, z = a.z, w = b;
        }
        bvec4(bool a, bvec3 b) {
            x = a, y = b.x, z = b.y, w = b.z;
        }
        bvec4(bvec2 a, bvec2 b) {
            x = a.x, y = a.y, z = b.x, w = b.y;
        }
        bvec4(bvec2 a, bool b, bool c) {
            x = a.x, y = a.y, z = b, w = c;
        }
        bvec4(bool a, bool b, bvec2 c) {
            x = a, y = b, z = c.x, w = c.y;
        }
        bvec4(bool a, bvec2 b, bool c) {
            x = a, y = b.x, z = b.y, w = c;
        }
        bvec4(bool v) {
            x = v, y = v, z = v, w = v;
        }
        bvec4(bvec4* v) {
            x = v->x, y = v->y, z = v->z, w = v->w;
        }
        
        bvec2 xy() {
            return bvec2(x, y);
        }
        bvec2 yx() {
            return bvec2(y, x);
        }
        bvec2 yz() {
            return bvec2(y, z);
        }
        bvec2 zy() {
            return bvec2(z, y);
        }
        bvec2 zw() {
            return bvec2(z, w);
        }
        bvec2 wz() {
            return bvec2(w, z);
        }
        bvec2 xz() {
            return bvec2(x, z);
        }
        bvec2 zx() {
            return bvec2(z, x);
        }
        bvec2 xw() {
            return bvec2(x, w);
        }
        bvec2 wx() {
            return bvec2(w, x);
        }
        bvec2 yw() {
            return bvec2(y, w);
        }
        bvec2 wy() {
            return bvec2(w, y);
        }
        bvec3 xyz() {
            return bvec3(x, y, z);
        }
        bvec3 xzy() {
            return bvec3(x, z, y);
        }
        bvec3 yxz() {
            return bvec3(y, x, z);
        }
        bvec3 yzx() {
            return bvec3(y, z, x);
        }
        bvec3 zxy() {
            return bvec3(z, x, y);
        }
        bvec3 zyx() {
            return bvec3(z, y, x);
        }
        bvec3 xyw() {
            return bvec3(x, y, w);
        }
        bvec3 xwy() {
            return bvec3(x, w, y);
        }
        bvec3 yxw() {
            return bvec3(y, x, w);
        }
        bvec3 ywx() {
            return bvec3(y, w, x);
        }
        bvec3 wxy() {
            return bvec3(w, x, y);
        }
        bvec3 wyx() {
            return bvec3(w, y, x);
        }
        bvec3 xzw() {
            return bvec3(x, z, w);
        }
        bvec3 xwz() {
            return bvec3(x, w, z);
        }
        bvec3 zxw() {
            return bvec3(z, x, w);
        }
        bvec3 zwx() {
            return bvec3(z, w, x);
        }
        bvec3 wxz() {
            return bvec3(w, x, z);
        }
        bvec3 wzx() {
            return bvec3(w, z, x);
        }
        bvec3 zyw() {
            return bvec3(z, y, w);
        }
        bvec3 zwy() {
            return bvec3(z, w, y);
        }
        bvec3 yzw() {
            return bvec3(y, z, w);
        }
        bvec3 ywz() {
            return bvec3(y, w, z);
        }
        bvec3 wzy() {
            return bvec3(w, z, y);
        }
        bvec3 wyz() {
            return bvec3(w, y, z);
        }
        bvec4 xyzw() {
            return bvec4(x, y, z, w);
        }
        bvec4 xywz() {
            return bvec4(x, y, w, z);
        }
        bvec4 xzyw() {
            return bvec4(x, z, y, w);
        }
        bvec4 xzwy() {
            return bvec4(x, z, w, y);
        }
        bvec4 xwyz() {
            return bvec4(x, w, y, z);
        }
        bvec4 xwzy() {
            return bvec4(x, w, z, y);
        }
        bvec4 yxzw() {
            return bvec4(y, x, z, w);
        }
        bvec4 yxwz() {
            return bvec4(y, x, w, z);
        }
        bvec4 yzxw() {
            return bvec4(y, z, x, w);
        }
        bvec4 yzwx() {
            return bvec4(y, z, w, x);
        }
        bvec4 ywxz() {
            return bvec4(y, w, x, z);
        }
        bvec4 ywzx() {
            return bvec4(y, w, z, x);
        }
        bvec4 zyxw() {
            return bvec4(z, y, x, w);
        }
        bvec4 zywx() {
            return bvec4(z, y, w, x);
        }
        bvec4 zxyw() {
            return bvec4(z, x, y, w);
        }
        bvec4 zxwy() {
            return bvec4(z, x, w, y);
        }
        bvec4 zwyx() {
            return bvec4(z, w, y, x);
        }
        bvec4 zwxy() {
            return bvec4(z, w, x, y);
        }
        bvec4 wyzx() {
            return bvec4(w, y, z, x);
        }
        bvec4 wyxz() {
            return bvec4(w, y, x, z);
        }
        bvec4 wzyx() {
            return bvec4(w, z, y, x);
        }
        bvec4 wzxy() {
            return bvec4(w, z, x, y);
        }
        bvec4 wxyz() {
            return bvec4(w, x, y, z);
        }
        bvec4 wxzy() {
            return bvec4(w, x, z, y);
        }
        
        void xy(bvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(bvec2 value) {
            y = value.x, x = value.y;
        }
        void yz(bvec2 value) {
            y = value.x, z = value.y;
        }
        void zy(bvec2 value) {
            z = value.x, y = value.y;
        }
        void zw(bvec2 value) {
            z = value.x, w = value.y;
        }
        void wz(bvec2 value) {
            w = value.x, z = value.y;
        }
        void xz(bvec2 value) {
            x = value.x, z = value.y;
        }
        void zx(bvec2 value) {
            z = value.x, x = value.y;
        }
        void xw(bvec2 value) {
            x = value.x, w = value.y;
        }
        void wx(bvec2 value) {
            w = value.x, x = value.y;
        }
        void yw(bvec2 value) {
            y = value.x, w = value.y;
        }
        void wy(bvec2 value) {
            w = value.x, y = value.y;
        }
        void xyz(bvec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(bvec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(bvec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(bvec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(bvec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(bvec3 value) {
            z = value.x, y = value.y, x = value.z;
        }
        void xyw(bvec3 value) {
            x = value.x, y = value.y, w = value.z;
        }
        void xwy(bvec3 value) {
            x = value.x, w = value.y, y = value.z;
        }
        void yxw(bvec3 value) {
            y = value.x, x = value.y, w = value.z;
        }
        void ywx(bvec3 value) {
            y = value.x, w = value.y, x = value.z;
        }
        void wxy(bvec3 value) {
            w = value.x, x = value.y, y = value.z;
        }
        void wyx(bvec3 value) {
            w = value.x, y = value.y, x = value.z;
        }
        void xzw(bvec3 value) {
            x = value.x, z = value.y, w = value.z;
        }
        void xwz(bvec3 value) {
            x = value.x, w = value.y, z = value.z;
        }
        void zxw(bvec3 value) {
            z = value.x, x = value.y, w = value.z;
        }
        void zwx(bvec3 value) {
            z = value.x, w = value.y, x = value.z;
        }
        void wxz(bvec3 value) {
            w = value.x, x = value.y, z = value.z;
        }
        void wzx(bvec3 value) {
            w = value.x, z = value.y, x = value.z;
        }
        void zyw(bvec3 value) {
            z = value.x, y = value.y, w = value.z;
        }
        void zwy(bvec3 value) {
            z = value.x, w = value.y, y = value.z;
        }
        void yzw(bvec3 value) {
            y = value.x, z = value.y, w = value.z;
        }
        void ywz(bvec3 value) {
            y = value.x, w = value.y, z = value.z;
        }
        void wzy(bvec3 value) {
            w = value.x, z = value.y, y = value.z;
        }
        void wyz(bvec3 value) {
            w = value.x, y = value.y, z = value.z;
        }
        void xyzw(bvec4 value) {
            x = value.x, y = value.y, z = value.z, w = value.w;
        }
        void xywz(bvec4 value) {
            x = value.x, y = value.y, w = value.z, z = value.w;
        }
        void xzyw(bvec4 value) {
            x = value.x, z = value.y, y = value.z, w = value.w;
        }
        void xzwy(bvec4 value) {
            x = value.x, z = value.y, w = value.z, y = value.w;
        }
        void xwyz(bvec4 value) {
            x = value.x, w = value.y, y = value.z, z = value.w;
        }
        void xwzy(bvec4 value) {
            x = value.x, w = value.y, z = value.z, y = value.w;
        }
        void yxzw(bvec4 value) {
            y = value.x, x = value.y, z = value.z, w = value.w;
        }
        void yxwz(bvec4 value) {
            y = value.x, x = value.y, w = value.z, z = value.w;
        }
        void yzxw(bvec4 value) {
            y = value.x, z = value.y, x = value.z, w = value.w;
        }
        void yzwx(bvec4 value) {
            y = value.x, z = value.y, w = value.z, x = value.w;
        }
        void ywxz(bvec4 value) {
            y = value.x, w = value.y, x = value.z, z = value.w;
        }
        void ywzx(bvec4 value) {
            y = value.x, w = value.y, z = value.z, x = value.w;
        }
        void zyxw(bvec4 value) {
            z = value.x, y = value.y, x = value.z, w = value.w;
        }
        void zywx(bvec4 value) {
            z = value.x, y = value.y, w = value.z, x = value.w;
        }
        void zxyw(bvec4 value) {
            z = value.x, x = value.y, y = value.z, w = value.w;
        }
        void zxwy(bvec4 value) {
            z = value.x, x = value.y, w = value.z, y = value.w;
        }
        void zwyx(bvec4 value) {
            z = value.x, w = value.y, y = value.z, x = value.w;
        }
        void zwxy(bvec4 value) {
            z = value.x, w = value.y, x = value.z, y = value.w;
        }
        void wyzx(bvec4 value) {
            w = value.x, y = value.y, z = value.z, x = value.w;
        }
        void wyxz(bvec4 value) {
            w = value.x, y = value.y, x = value.z, z = value.w;
        }
        void wzyx(bvec4 value) {
            w = value.x, z = value.y, y = value.z, x = value.w;
        }
        void wzxy(bvec4 value) {
            w = value.x, z = value.y, x = value.z, y = value.w;
        }
        void wxyz(bvec4 value) {
            w = value.x, x = value.y, y = value.z, z = value.w;
        }
        void wxzy(bvec4 value) {
            w = value.x, x = value.y, z = value.z, y = value.w;
        }

        bvec4 operator!() {
            return bvec4(-x, -y, -z, -w);
        }
        
        bool operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: return false;
            }
        }
        
        bool all() {
            return x && y && z && w;
        }
        bool any() {
            return x || y || z || w;
        }

        bvec4 operator==(bvec4 other) {
            return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
        }
        bvec4 operator!=(bvec4 other) {
            return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
        }

        bvec4 operator==(bool other) {
            return bvec4(x == other, y == other, z == other, w == other);
        }
        bvec4 operator!=(bool other) {
            return bvec4(x != other, y != other, z != other, w != other);
        }
    };

    struct vec2 {
        float x, y;
        
        vec2() {
            x = 0.0, y = 0.0;
        }
        vec2(float x, float y) {
            this->x = x, this->y = y;
        }
        vec2(float v) {
            x = v, y = v;
        }
        vec2(vec2* v) {
            x = v->x, y = v->y;
        }
        
        vec2 xy() {
            return vec2(x, y);
        }
        vec2 yx() {
            return vec2(y, x);
        }
        
        void xy(vec2 value) {
            x = value.x, y = value.y;
        }
        void yx(vec2 value) {
            y = value.x, x = value.y;
        }
        
        float length2() {
            return x*x+y*y;
        }
        float length() {
            return std::sqrt(x*x+y*y);
        }
        
        vec2 normalize() {
            float len = length();
            
            if (len < 0.00001) return vec2(0.0);
            
            return vec2(x/len, y/len);
        }
        
        vec2 operator-() {
            return vec2(-x, -y);
        }
        vec2 operator~() {
            return normalize();
        }
        
        float operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                default: return 0.0;
            }
        }
        
        vec2 operator+(vec2 other) {
            return vec2(x+other.x, y+other.y);
        }
        vec2 operator-(vec2 other) {
            return vec2(x-other.x, y-other.y);
        }
        vec2 operator*(vec2 other) {
            return vec2(x*other.x, y*other.y);
        }
        vec2 operator/(vec2 other) {
            return vec2(x/other.x, y/other.y);
        }
        
        void operator+=(vec2 other) {
            x += other.x, y += other.y;
        }
        void operator-=(vec2 other) {
            x -= other.x, y -= other.y;
        }
        void operator*=(vec2 other) {
            x *= other.x, y *= other.y;
        }
        void operator/=(vec2 other) {
            x /= other.x, y /= other.y;
        }

        vec2 operator+(float other) {
            return vec2(x+other, y+other);
        }
        vec2 operator-(float other) {
            return vec2(x-other, y-other);
        }
        vec2 operator*(float other) {
            return vec2(x*other, y*other);
        }
        vec2 operator/(float other) {
            return vec2(x/other, y/other);
        }
        
        void operator+=(float other) {
            x += other, y += other;
        }
        void operator-=(float other) {
            x -= other, y -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other;
        }

        vec2 operator+(double other) {
            return vec2(x+other, y+other);
        }
        vec2 operator-(double other) {
            return vec2(x-other, y-other);
        }
        vec2 operator*(double other) {
            return vec2(x*other, y*other);
        }
        vec2 operator/(double other) {
            return vec2(x/other, y/other);
        }
        
        void operator+=(double other) {
            x += other, y += other;
        }
        void operator-=(double other) {
            x -= other, y -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other;
        }
        
        bvec2 operator==(vec2 other) {
            return bvec2(x == other.x, y == other.y);
        }
        bvec2 operator!=(vec2 other) {
            return bvec2(x != other.x, y != other.y);
        }
        bvec2 operator>(vec2 other) {
            return bvec2(x > other.x, y > other.y);
        }
        bvec2 operator<(vec2 other) {
            return bvec2(x < other.x, y < other.y);
        }
        bvec2 operator<=(vec2 other) {
            return bvec2(x <= other.x, y <= other.y);
        }
        bvec2 operator>=(vec2 other) {
            return bvec2(x >= other.x, y >= other.y);
        }

        bvec2 operator==(float other) {
            return bvec2(x == other, y == other);
        }
        bvec2 operator!=(float other) {
            return bvec2(x != other, y != other);
        }
        bvec2 operator>(float other) {
            return bvec2(x > other, y > other);
        }
        bvec2 operator<(float other) {
            return bvec2(x < other, y < other);
        }
        bvec2 operator<=(float other) {
            return bvec2(x <= other, y <= other);
        }
        bvec2 operator>=(float other) {
            return bvec2(x >= other, y >= other);
        }
        
        bvec2 operator==(double other) {
            return bvec2(x == other, y == other);
        }
        bvec2 operator!=(double other) {
            return bvec2(x != other, y != other);
        }
        bvec2 operator>(double other) {
            return bvec2(x > other, y > other);
        }
        bvec2 operator<(double other) {
            return bvec2(x < other, y < other);
        }
        bvec2 operator<=(double other) {
            return bvec2(x <= other, y <= other);
        }
        bvec2 operator>=(double other) {
            return bvec2(x >= other, y >= other);
        }
    };

    struct vec3 {
        float x, y, z;
        
        vec3() {
            x = 0.0, y = 0.0, z = 0.0;
        }
        vec3(float x, float y, float z) {
            this->x = x, this->y = y, this->z = z;
        }
        vec3(vec2 a, float b) {
            x = a.x, y = a.y, z = b;
        }
        vec3(float a, vec2 b) {
            x = a, y = b.x, z = b.y;
        }
        vec3(float v) {
            x = v, y = v, z = v;
        }
        vec3(vec3* v) {
            x = v->x, y = v->y, z = v->z;
        }
        
        vec2 xy() {
            return vec2(x, y);
        }
        vec2 yx() {
            return vec2(y, x);
        }
        vec2 xz() {
            return vec2(x, z);
        }
        vec2 zx() {
            return vec2(z, x);
        }
        vec2 yz() {
            return vec2(y, z);
        }
        vec2 zy() {
            return vec2(z, y);
        }
        vec3 xyz() {
            return vec3(x, y, z);
        }
        vec3 xzy() {
            return vec3(x, z, y);
        }
        vec3 yxz() {
            return vec3(y, x, z);
        }
        vec3 yzx() {
            return vec3(y, z, x);
        }
        vec3 zxy() {
            return vec3(z, x, y);
        }
        vec3 zyx() {
            return vec3(z, y, x);
        }
        
        void xy(vec2 value) {
            x = value.x, y = value.y;
        }
        void yx(vec2 value) {
            y = value.x, x = value.y;
        }
        void xz(vec2 value) {
            x = value.x, z = value.y;
        }
        void zx(vec2 value) {
            z = value.x, x = value.y;
        }
        void yz(vec2 value) {
            y = value.x, z = value.y;
        }
        void zy(vec2 value) {
            z = value.x, y = value.y;
        }
        void xyz(vec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(vec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(vec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(vec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(vec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(vec3 value) {
            z = value.x, y = value.y, x = value.z;
        }
        
        float length2() {
            return x*x+y*y+z*z;
        }
        float length() {
            return std::sqrt(x*x+y*y+z*z);
        }
        
        vec3 normalize() {
            float len = length();
            
            if (len < 0.00001) return vec3(0.0);
            
            return vec3(x/len, y/len, z/len);
        }
        
        vec3 operator-() {
            return vec3(-x, -y, -z);
        }
        vec3 operator~() {
            return normalize();
        }
        
        float operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: return 0.0;
            }
        }
        
        vec3 operator+(vec3 other) {
            return vec3(x+other.x, y+other.y, z+other.z);
        }
        vec3 operator-(vec3 other) {
            return vec3(x-other.x, y-other.y, z-other.z);
        }
        vec3 operator*(vec3 other) {
            return vec3(x*other.x, y*other.y, z*other.z);
        }
        vec3 operator/(vec3 other) {
            return vec3(x/other.x, y/other.y, z/other.z);
        }
        
        void operator+=(vec3 other) {
            x += other.x, y += other.y, z += other.z;
        }
        void operator-=(vec3 other) {
            x -= other.x, y -= other.y, z -= other.z;
        }
        void operator*=(vec3 other) {
            x *= other.x, y *= other.y, z *= other.z;
        }
        void operator/=(vec3 other) {
            x /= other.x, y /= other.y, z /= other.z;
        }

        vec3 operator+(float other) {
            return vec3(x+other, y+other, z+other);
        }
        vec3 operator-(float other) {
            return vec3(x-other, y-other, z-other);
        }
        vec3 operator*(float other) {
            return vec3(x*other, y*other, z*other);
        }
        vec3 operator/(float other) {
            return vec3(x/other, y/other, z/other);
        }
        
        void operator+=(float other) {
            x += other, y += other, z += other;
        }
        void operator-=(float other) {
            x -= other, y -= other, z -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other, z *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other, z /= other;
        }

        vec3 operator+(double other) {
            return vec3(x+other, y+other, z+other);
        }
        vec3 operator-(double other) {
            return vec3(x-other, y-other, z-other);
        }
        vec3 operator*(double other) {
            return vec3(x*other, y*other, z*other);
        }
        vec3 operator/(double other) {
            return vec3(x/other, y/other, z/other);
        }
        
        void operator+=(double other) {
            x += other, y += other, z += other;
        }
        void operator-=(double other) {
            x -= other, y -= other, z -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other, z *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other, z /= other;
        }
        
        bvec3 operator==(vec3 other) {
            return bvec3(x == other.x, y == other.y, z == other.z);
        }
        bvec3 operator!=(vec3 other) {
            return bvec3(x != other.x, y != other.y, z != other.z);
        }
        bvec3 operator>(vec3 other) {
            return bvec3(x > other.x, y > other.y, z > other.z);
        }
        bvec3 operator<(vec3 other) {
            return bvec3(x < other.x, y < other.y, z < other.z);
        }
        bvec3 operator<=(vec3 other) {
            return bvec3(x <= other.x, y <= other.y, z <= other.z);
        }
        bvec3 operator>=(vec3 other) {
            return bvec3(x >= other.x, y >= other.y, z >= other.z);
        }

        bvec3 operator==(float other) {
            return bvec3(x == other, y == other, z == other);
        }
        bvec3 operator!=(float other) {
            return bvec3(x != other, y != other, z != other);
        }
        bvec3 operator>(float other) {
            return bvec3(x > other, y > other, z > other);
        }
        bvec3 operator<(float other) {
            return bvec3(x < other, y < other, z < other);
        }
        bvec3 operator<=(float other) {
            return bvec3(x <= other, y <= other, z <= other);
        }
        bvec3 operator>=(float other) {
            return bvec3(x >= other, y >= other, z >= other);
        }
        
        bvec3 operator==(double other) {
            return bvec3(x == other, y == other, z == other);
        }
        bvec3 operator!=(double other) {
            return bvec3(x != other, y != other, z != other);
        }
        bvec3 operator>(double other) {
            return bvec3(x > other, y > other, z > other);
        }
        bvec3 operator<(double other) {
            return bvec3(x < other, y < other, z < other);
        }
        bvec3 operator<=(double other) {
            return bvec3(x <= other, y <= other, z <= other);
        }
        bvec3 operator>=(double other) {
            return bvec3(x >= other, y >= other, z >= other);
        }
    };

    struct vec4 {
        float x, y, z, w;
        
        vec4() {
            x = 0.0, y = 0.0, z = 0.0, w = 0.0;
        }
        vec4(float x, float y, float z, float w) {
            this->x = x, this->y = y, this->z = z, this->w = w;
        }
        vec4(vec3 a, float b) {
            x = a.x, y = a.y, z = a.z, w = b;
        }
        vec4(float a, vec3 b) {
            x = a, y = b.x, z = b.y, w = b.z;
        }
        vec4(vec2 a, vec2 b) {
            x = a.x, y = a.y, z = b.x, w = b.y;
        }
        vec4(vec2 a, float b, float c) {
            x = a.x, y = a.y, z = b, w = c;
        }
        vec4(float a, float b, vec2 c) {
            x = a, y = b, z = c.x, w = c.y;
        }
        vec4(float a, vec2 b, float c) {
            x = a, y = b.x, z = b.y, w = c;
        }
        vec4(float v) {
            x = v, y = v, z = v, w = v;
        }
        vec4(vec4* v) {
            x = v->x, y = v->y, z = v->z, w = v->w;
        }
        
        vec2 xy() {
            return vec2(x, y);
        }
        vec2 yx() {
            return vec2(y, x);
        }
        vec2 yz() {
            return vec2(y, z);
        }
        vec2 zy() {
            return vec2(z, y);
        }
        vec2 zw() {
            return vec2(z, w);
        }
        vec2 wz() {
            return vec2(w, z);
        }
        vec2 xz() {
            return vec2(x, z);
        }
        vec2 zx() {
            return vec2(z, x);
        }
        vec2 xw() {
            return vec2(x, w);
        }
        vec2 wx() {
            return vec2(w, x);
        }
        vec2 yw() {
            return vec2(y, w);
        }
        vec2 wy() {
            return vec2(w, y);
        }
        vec3 xyz() {
            return vec3(x, y, z);
        }
        vec3 xzy() {
            return vec3(x, z, y);
        }
        vec3 yxz() {
            return vec3(y, x, z);
        }
        vec3 yzx() {
            return vec3(y, z, x);
        }
        vec3 zxy() {
            return vec3(z, x, y);
        }
        vec3 zyx() {
            return vec3(z, y, x);
        }
        vec3 xyw() {
            return vec3(x, y, w);
        }
        vec3 xwy() {
            return vec3(x, w, y);
        }
        vec3 yxw() {
            return vec3(y, x, w);
        }
        vec3 ywx() {
            return vec3(y, w, x);
        }
        vec3 wxy() {
            return vec3(w, x, y);
        }
        vec3 wyx() {
            return vec3(w, y, x);
        }
        vec3 xzw() {
            return vec3(x, z, w);
        }
        vec3 xwz() {
            return vec3(x, w, z);
        }
        vec3 zxw() {
            return vec3(z, x, w);
        }
        vec3 zwx() {
            return vec3(z, w, x);
        }
        vec3 wxz() {
            return vec3(w, x, z);
        }
        vec3 wzx() {
            return vec3(w, z, x);
        }
        vec3 zyw() {
            return vec3(z, y, w);
        }
        vec3 zwy() {
            return vec3(z, w, y);
        }
        vec3 yzw() {
            return vec3(y, z, w);
        }
        vec3 ywz() {
            return vec3(y, w, z);
        }
        vec3 wzy() {
            return vec3(w, z, y);
        }
        vec3 wyz() {
            return vec3(w, y, z);
        }
        vec4 xyzw() {
            return vec4(x, y, z, w);
        }
        vec4 xywz() {
            return vec4(x, y, w, z);
        }
        vec4 xzyw() {
            return vec4(x, z, y, w);
        }
        vec4 xzwy() {
            return vec4(x, z, w, y);
        }
        vec4 xwyz() {
            return vec4(x, w, y, z);
        }
        vec4 xwzy() {
            return vec4(x, w, z, y);
        }
        vec4 yxzw() {
            return vec4(y, x, z, w);
        }
        vec4 yxwz() {
            return vec4(y, x, w, z);
        }
        vec4 yzxw() {
            return vec4(y, z, x, w);
        }
        vec4 yzwx() {
            return vec4(y, z, w, x);
        }
        vec4 ywxz() {
            return vec4(y, w, x, z);
        }
        vec4 ywzx() {
            return vec4(y, w, z, x);
        }
        vec4 zyxw() {
            return vec4(z, y, x, w);
        }
        vec4 zywx() {
            return vec4(z, y, w, x);
        }
        vec4 zxyw() {
            return vec4(z, x, y, w);
        }
        vec4 zxwy() {
            return vec4(z, x, w, y);
        }
        vec4 zwyx() {
            return vec4(z, w, y, x);
        }
        vec4 zwxy() {
            return vec4(z, w, x, y);
        }
        vec4 wyzx() {
            return vec4(w, y, z, x);
        }
        vec4 wyxz() {
            return vec4(w, y, x, z);
        }
        vec4 wzyx() {
            return vec4(w, z, y, x);
        }
        vec4 wzxy() {
            return vec4(w, z, x, y);
        }
        vec4 wxyz() {
            return vec4(w, x, y, z);
        }
        vec4 wxzy() {
            return vec4(w, x, z, y);
        }
        
        void xy(vec2 value) {
            x = value.x, y = value.y;
        }
        void yx(vec2 value) {
            y = value.x, x = value.y;
        }
        void yz(vec2 value) {
            y = value.x, z = value.y;
        }
        void zy(vec2 value) {
            z = value.x, y = value.y;
        }
        void zw(vec2 value) {
            z = value.x, w = value.y;
        }
        void wz(vec2 value) {
            w = value.x, z = value.y;
        }
        void xz(vec2 value) {
            x = value.x, z = value.y;
        }
        void zx(vec2 value) {
            z = value.x, x = value.y;
        }
        void xw(vec2 value) {
            x = value.x, w = value.y;
        }
        void wx(vec2 value) {
            w = value.x, x = value.y;
        }
        void yw(vec2 value) {
            y = value.x, w = value.y;
        }
        void wy(vec2 value) {
            w = value.x, y = value.y;
        }
        void xyz(vec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(vec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(vec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(vec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(vec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(vec3 value) {
            z = value.x, y = value.y, x = value.z;
        }
        void xyw(vec3 value) {
            x = value.x, y = value.y, w = value.z;
        }
        void xwy(vec3 value) {
            x = value.x, w = value.y, y = value.z;
        }
        void yxw(vec3 value) {
            y = value.x, x = value.y, w = value.z;
        }
        void ywx(vec3 value) {
            y = value.x, w = value.y, x = value.z;
        }
        void wxy(vec3 value) {
            w = value.x, x = value.y, y = value.z;
        }
        void wyx(vec3 value) {
            w = value.x, y = value.y, x = value.z;
        }
        void xzw(vec3 value) {
            x = value.x, z = value.y, w = value.z;
        }
        void xwz(vec3 value) {
            x = value.x, w = value.y, z = value.z;
        }
        void zxw(vec3 value) {
            z = value.x, x = value.y, w = value.z;
        }
        void zwx(vec3 value) {
            z = value.x, w = value.y, x = value.z;
        }
        void wxz(vec3 value) {
            w = value.x, x = value.y, z = value.z;
        }
        void wzx(vec3 value) {
            w = value.x, z = value.y, x = value.z;
        }
        void zyw(vec3 value) {
            z = value.x, y = value.y, w = value.z;
        }
        void zwy(vec3 value) {
            z = value.x, w = value.y, y = value.z;
        }
        void yzw(vec3 value) {
            y = value.x, z = value.y, w = value.z;
        }
        void ywz(vec3 value) {
            y = value.x, w = value.y, z = value.z;
        }
        void wzy(vec3 value) {
            w = value.x, z = value.y, y = value.z;
        }
        void wyz(vec3 value) {
            w = value.x, y = value.y, z = value.z;
        }
        void xyzw(vec4 value) {
            x = value.x, y = value.y, z = value.z, w = value.w;
        }
        void xywz(vec4 value) {
            x = value.x, y = value.y, w = value.z, z = value.w;
        }
        void xzyw(vec4 value) {
            x = value.x, z = value.y, y = value.z, w = value.w;
        }
        void xzwy(vec4 value) {
            x = value.x, z = value.y, w = value.z, y = value.w;
        }
        void xwyz(vec4 value) {
            x = value.x, w = value.y, y = value.z, z = value.w;
        }
        void xwzy(vec4 value) {
            x = value.x, w = value.y, z = value.z, y = value.w;
        }
        void yxzw(vec4 value) {
            y = value.x, x = value.y, z = value.z, w = value.w;
        }
        void yxwz(vec4 value) {
            y = value.x, x = value.y, w = value.z, z = value.w;
        }
        void yzxw(vec4 value) {
            y = value.x, z = value.y, x = value.z, w = value.w;
        }
        void yzwx(vec4 value) {
            y = value.x, z = value.y, w = value.z, x = value.w;
        }
        void ywxz(vec4 value) {
            y = value.x, w = value.y, x = value.z, z = value.w;
        }
        void ywzx(vec4 value) {
            y = value.x, w = value.y, z = value.z, x = value.w;
        }
        void zyxw(vec4 value) {
            z = value.x, y = value.y, x = value.z, w = value.w;
        }
        void zywx(vec4 value) {
            z = value.x, y = value.y, w = value.z, x = value.w;
        }
        void zxyw(vec4 value) {
            z = value.x, x = value.y, y = value.z, w = value.w;
        }
        void zxwy(vec4 value) {
            z = value.x, x = value.y, w = value.z, y = value.w;
        }
        void zwyx(vec4 value) {
            z = value.x, w = value.y, y = value.z, x = value.w;
        }
        void zwxy(vec4 value) {
            z = value.x, w = value.y, x = value.z, y = value.w;
        }
        void wyzx(vec4 value) {
            w = value.x, y = value.y, z = value.z, x = value.w;
        }
        void wyxz(vec4 value) {
            w = value.x, y = value.y, x = value.z, z = value.w;
        }
        void wzyx(vec4 value) {
            w = value.x, z = value.y, y = value.z, x = value.w;
        }
        void wzxy(vec4 value) {
            w = value.x, z = value.y, x = value.z, y = value.w;
        }
        void wxyz(vec4 value) {
            w = value.x, x = value.y, y = value.z, z = value.w;
        }
        void wxzy(vec4 value) {
            w = value.x, x = value.y, z = value.z, y = value.w;
        }
        
        float length2() {
            return x*x+y*y+z*z+w*w;
        }
        float length() {
            return std::sqrt(x*x+y*y+z*z+w*w);
        }
        
        vec4 normalize() {
            float len = length();
            
            if (len < 0.00001) return vec4(0.0);
            
            return vec4(x/len, y/len, z/len, w/len);
        }
        
        vec4 operator-() {
            return vec4(-x, -y, -z, -w);
        }
        vec4 operator~() {
            return normalize();
        }
        
        float operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: return 0.0;
            }
        }
        
        vec4 operator+(vec4 other) {
            return vec4(x+other.x, y+other.y, z+other.z, w+other.w);
        }
        vec4 operator-(vec4 other) {
            return vec4(x-other.x, y-other.y, z-other.z, w-other.w);
        }
        vec4 operator*(vec4 other) {
            return vec4(x*other.x, y*other.y, z*other.z, w*other.w);
        }
        vec4 operator/(vec4 other) {
            return vec4(x/other.x, y/other.y, z/other.z, w/other.w);
        }
        
        void operator+=(vec4 other) {
            x += other.x, y += other.y, z += other.z, w += other.w;
        }
        void operator-=(vec4 other) {
            x -= other.x, y -= other.y, z -= other.z, w -= other.w;
        }
        void operator*=(vec4 other) {
            x *= other.x, y *= other.y, z *= other.z, w *= other.w;
        }
        void operator/=(vec4 other) {
            x /= other.x, y /= other.y, z /= other.z, w /= other.w;
        }

        vec4 operator+(float other) {
            return vec4(x+other, y+other, z+other, w+other);
        }
        vec4 operator-(float other) {
            return vec4(x-other, y-other, z-other, w-other);
        }
        vec4 operator*(float other) {
            return vec4(x*other, y*other, z*other, w*other);
        }
        vec4 operator/(float other) {
            return vec4(x/other, y/other, z/other, w/other);
        }
        
        void operator+=(float other) {
            x += other, y += other, z += other, w += other;
        }
        void operator-=(float other) {
            x -= other, y -= other, z -= other, w -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other, z *= other, w *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other, z /= other, w /= other;
        }

        vec4 operator+(double other) {
            return vec4(x+other, y+other, z+other, w+other);
        }
        vec4 operator-(double other) {
            return vec4(x-other, y-other, z-other, w-other);
        }
        vec4 operator*(double other) {
            return vec4(x*other, y*other, z*other, w*other);
        }
        vec4 operator/(double other) {
            return vec4(x/other, y/other, z/other, w/other);
        }
        
        void operator+=(double other) {
            x += other, y += other, z += other, w += other;
        }
        void operator-=(double other) {
            x -= other, y -= other, z -= other, w -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other, z *= other, w *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other, z /= other, w /= other;
        }
        
        bvec4 operator==(vec4 other) {
            return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
        }
        bvec4 operator!=(vec4 other) {
            return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
        }
        bvec4 operator>(vec4 other) {
            return bvec4(x > other.x, y > other.y, z > other.z, w > other.w);
        }
        bvec4 operator<(vec4 other) {
            return bvec4(x < other.x, y < other.y, z < other.z, w < other.w);
        }
        bvec4 operator<=(vec4 other) {
            return bvec4(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
        }
        bvec4 operator>=(vec4 other) {
            return bvec4(x >= other.x, y >= other.y, z >= other.z, w >= other.w);
        }

        bvec4 operator==(float other) {
            return bvec4(x == other, y == other, z == other, w == other);
        }
        bvec4 operator!=(float other) {
            return bvec4(x != other, y != other, z != other, w != other);
        }
        bvec4 operator>(float other) {
            return bvec4(x > other, y > other, z > other, w > other);
        }
        bvec4 operator<(float other) {
            return bvec4(x < other, y < other, z < other, w < other);
        }
        bvec4 operator<=(float other) {
            return bvec4(x <= other, y <= other, z <= other, w <= other);
        }
        bvec4 operator>=(float other) {
            return bvec4(x >= other, y >= other, z >= other, w >= other);
        }
        
        bvec4 operator==(double other) {
            return bvec4(x == other, y == other, z == other, w == other);
        }
        bvec4 operator!=(double other) {
            return bvec4(x != other, y != other, z != other, w != other);
        }
        bvec4 operator>(double other) {
            return bvec4(x > other, y > other, z > other, w > other);
        }
        bvec4 operator<(double other) {
            return bvec4(x < other, y < other, z < other, w < other);
        }
        bvec4 operator<=(double other) {
            return bvec4(x <= other, y <= other, z <= other, w <= other);
        }
        bvec4 operator>=(double other) {
            return bvec4(x >= other, y >= other, z >= other, w >= other);
        }
    };

    struct dvec2 {
        double x, y;
        
        dvec2() {
            x = 0.0, y = 0.0;
        }
        dvec2(double x, double y) {
            this->x = x, this->y = y;
        }
        dvec2(double v) {
            x = v, y = v;
        }
        dvec2(dvec2* v) {
            x = v->x, y = v->y;
        }
        
        dvec2 xy() {
            return dvec2(x, y);
        }
        dvec2 yx() {
            return dvec2(y, x);
        }
        
        void xy(dvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(dvec2 value) {
            y = value.x, x = value.y;
        }
        
        double length2() {
            return x*x+y*y;
        }
        double length() {
            return std::sqrt(x*x+y*y);
        }
        
        dvec2 normalize() {
            double len = length();
            
            if (len < 1e-13) return dvec2(0.0);
            
            return dvec2(x/len, y/len);
        }
        
        dvec2 operator-() {
            return dvec2(-x, -y);
        }
        dvec2 operator~() {
            return normalize();
        }
        
        double operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                default: return 0.0;
            }
        }
        
        dvec2 operator+(dvec2 other) {
            return dvec2(x+other.x, y+other.y);
        }
        dvec2 operator-(dvec2 other) {
            return dvec2(x-other.x, y-other.y);
        }
        dvec2 operator*(dvec2 other) {
            return dvec2(x*other.x, y*other.y);
        }
        dvec2 operator/(dvec2 other) {
            return dvec2(x/other.x, y/other.y);
        }
        
        void operator+=(dvec2 other) {
            x += other.x, y += other.y;
        }
        void operator-=(dvec2 other) {
            x -= other.x, y -= other.y;
        }
        void operator*=(dvec2 other) {
            x *= other.x, y *= other.y;
        }
        void operator/=(dvec2 other) {
            x /= other.x, y /= other.y;
        }

        dvec2 operator+(float other) {
            return dvec2(x+other, y+other);
        }
        dvec2 operator-(float other) {
            return dvec2(x-other, y-other);
        }
        dvec2 operator*(float other) {
            return dvec2(x*other, y*other);
        }
        dvec2 operator/(float other) {
            return dvec2(x/other, y/other);
        }
        
        void operator+=(float other) {
            x += other, y += other;
        }
        void operator-=(float other) {
            x -= other, y -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other;
        }

        dvec2 operator+(double other) {
            return dvec2(x+other, y+other);
        }
        dvec2 operator-(double other) {
            return dvec2(x-other, y-other);
        }
        dvec2 operator*(double other) {
            return dvec2(x*other, y*other);
        }
        dvec2 operator/(double other) {
            return dvec2(x/other, y/other);
        }
        
        void operator+=(double other) {
            x += other, y += other;
        }
        void operator-=(double other) {
            x -= other, y -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other;
        }
        
        bvec2 operator==(dvec2 other) {
            return bvec2(x == other.x, y == other.y);
        }
        bvec2 operator!=(dvec2 other) {
            return bvec2(x != other.x, y != other.y);
        }
        bvec2 operator>(dvec2 other) {
            return bvec2(x > other.x, y > other.y);
        }
        bvec2 operator<(dvec2 other) {
            return bvec2(x < other.x, y < other.y);
        }
        bvec2 operator<=(dvec2 other) {
            return bvec2(x <= other.x, y <= other.y);
        }
        bvec2 operator>=(dvec2 other) {
            return bvec2(x >= other.x, y >= other.y);
        }

        bvec2 operator==(float other) {
            return bvec2(x == other, y == other);
        }
        bvec2 operator!=(float other) {
            return bvec2(x != other, y != other);
        }
        bvec2 operator>(float other) {
            return bvec2(x > other, y > other);
        }
        bvec2 operator<(float other) {
            return bvec2(x < other, y < other);
        }
        bvec2 operator<=(float other) {
            return bvec2(x <= other, y <= other);
        }
        bvec2 operator>=(float other) {
            return bvec2(x >= other, y >= other);
        }
        
        bvec2 operator==(double other) {
            return bvec2(x == other, y == other);
        }
        bvec2 operator!=(double other) {
            return bvec2(x != other, y != other);
        }
        bvec2 operator>(double other) {
            return bvec2(x > other, y > other);
        }
        bvec2 operator<(double other) {
            return bvec2(x < other, y < other);
        }
        bvec2 operator<=(double other) {
            return bvec2(x <= other, y <= other);
        }
        bvec2 operator>=(double other) {
            return bvec2(x >= other, y >= other);
        }
    };

    struct dvec3 {
        double x, y, z;
        
        dvec3() {
            x = 0.0, y = 0.0, z = 0.0;
        }
        dvec3(double x, double y, double z) {
            this->x = x, this->y = y, this->z = z;
        }
        dvec3(dvec2 a, double b) {
            x = a.x, y = a.y, z = b;
        }
        dvec3(double a, dvec2 b) {
            x = a, y = b.x, z = b.y;
        }
        dvec3(double v) {
            x = v, y = v, z = v;
        }
        dvec3(dvec3* v) {
            x = v->x, y = v->y, z = v->z;
        }
        
        dvec2 xy() {
            return dvec2(x, y);
        }
        dvec2 yx() {
            return dvec2(y, x);
        }
        dvec2 xz() {
            return dvec2(x, z);
        }
        dvec2 zx() {
            return dvec2(z, x);
        }
        dvec2 yz() {
            return dvec2(y, z);
        }
        dvec2 zy() {
            return dvec2(z, y);
        }
        dvec3 xyz() {
            return dvec3(x, y, z);
        }
        dvec3 xzy() {
            return dvec3(x, z, y);
        }
        dvec3 yxz() {
            return dvec3(y, x, z);
        }
        dvec3 yzx() {
            return dvec3(y, z, x);
        }
        dvec3 zxy() {
            return dvec3(z, x, y);
        }
        dvec3 zyx() {
            return dvec3(z, y, x);
        }
        
        void xy(dvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(dvec2 value) {
            y = value.x, x = value.y;
        }
        void xz(dvec2 value) {
            x = value.x, z = value.y;
        }
        void zx(dvec2 value) {
            z = value.x, x = value.y;
        }
        void yz(dvec2 value) {
            y = value.x, z = value.y;
        }
        void zy(dvec2 value) {
            z = value.x, y = value.y;
        }
        void xyz(dvec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(dvec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(dvec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(dvec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(dvec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(dvec3 value) {
            z = value.x, y = value.y, x = value.z;
        }
        
        double length2() {
            return x*x+y*y+z*z;
        }
        double length() {
            return std::sqrt(x*x+y*y+z*z);
        }
        
        dvec3 normalize() {
            double len = length();
            
            if (len < 1e-13) return dvec3(0.0);
            
            return dvec3(x/len, y/len, z/len);
        }
        
        dvec3 operator-() {
            return dvec3(-x, -y, -z);
        }
        dvec3 operator~() {
            return normalize();
        }
        
        double operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                default: return 0.0;
            }
        }
        
        dvec3 operator+(dvec3 other) {
            return dvec3(x+other.x, y+other.y, z+other.z);
        }
        dvec3 operator-(dvec3 other) {
            return dvec3(x-other.x, y-other.y, z-other.z);
        }
        dvec3 operator*(dvec3 other) {
            return dvec3(x*other.x, y*other.y, z*other.z);
        }
        dvec3 operator/(dvec3 other) {
            return dvec3(x/other.x, y/other.y, z/other.z);
        }
        
        void operator+=(dvec3 other) {
            x += other.x, y += other.y, z += other.z;
        }
        void operator-=(dvec3 other) {
            x -= other.x, y -= other.y, z -= other.z;
        }
        void operator*=(dvec3 other) {
            x *= other.x, y *= other.y, z *= other.z;
        }
        void operator/=(dvec3 other) {
            x /= other.x, y /= other.y, z /= other.z;
        }

        dvec3 operator+(float other) {
            return dvec3(x+other, y+other, z+other);
        }
        dvec3 operator-(float other) {
            return dvec3(x-other, y-other, z-other);
        }
        dvec3 operator*(float other) {
            return dvec3(x*other, y*other, z*other);
        }
        dvec3 operator/(float other) {
            return dvec3(x/other, y/other, z/other);
        }
        
        void operator+=(float other) {
            x += other, y += other, z += other;
        }
        void operator-=(float other) {
            x -= other, y -= other, z -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other, z *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other, z /= other;
        }

        dvec3 operator+(double other) {
            return dvec3(x+other, y+other, z+other);
        }
        dvec3 operator-(double other) {
            return dvec3(x-other, y-other, z-other);
        }
        dvec3 operator*(double other) {
            return dvec3(x*other, y*other, z*other);
        }
        dvec3 operator/(double other) {
            return dvec3(x/other, y/other, z/other);
        }
        
        void operator+=(double other) {
            x += other, y += other, z += other;
        }
        void operator-=(double other) {
            x -= other, y -= other, z -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other, z *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other, z /= other;
        }
        
        bvec3 operator==(dvec3 other) {
            return bvec3(x == other.x, y == other.y, z == other.z);
        }
        bvec3 operator!=(dvec3 other) {
            return bvec3(x != other.x, y != other.y, z != other.z);
        }
        bvec3 operator>(dvec3 other) {
            return bvec3(x > other.x, y > other.y, z > other.z);
        }
        bvec3 operator<(dvec3 other) {
            return bvec3(x < other.x, y < other.y, z < other.z);
        }
        bvec3 operator<=(dvec3 other) {
            return bvec3(x <= other.x, y <= other.y, z <= other.z);
        }
        bvec3 operator>=(dvec3 other) {
            return bvec3(x >= other.x, y >= other.y, z >= other.z);
        }

        bvec3 operator==(float other) {
            return bvec3(x == other, y == other, z == other);
        }
        bvec3 operator!=(float other) {
            return bvec3(x != other, y != other, z != other);
        }
        bvec3 operator>(float other) {
            return bvec3(x > other, y > other, z > other);
        }
        bvec3 operator<(float other) {
            return bvec3(x < other, y < other, z < other);
        }
        bvec3 operator<=(float other) {
            return bvec3(x <= other, y <= other, z <= other);
        }
        bvec3 operator>=(float other) {
            return bvec3(x >= other, y >= other, z >= other);
        }
        
        bvec3 operator==(double other) {
            return bvec3(x == other, y == other, z == other);
        }
        bvec3 operator!=(double other) {
            return bvec3(x != other, y != other, z != other);
        }
        bvec3 operator>(double other) {
            return bvec3(x > other, y > other, z > other);
        }
        bvec3 operator<(double other) {
            return bvec3(x < other, y < other, z < other);
        }
        bvec3 operator<=(double other) {
            return bvec3(x <= other, y <= other, z <= other);
        }
        bvec3 operator>=(double other) {
            return bvec3(x >= other, y >= other, z >= other);
        }
    };

    struct dvec4 {
        double x, y, z, w;
        
        dvec4() {
            x = 0.0, y = 0.0, z = 0.0, w = 0.0;
        }
        dvec4(double x, double y, double z, double w) {
            this->x = x, this->y = y, this->z = z, this->w = w;
        }
        dvec4(dvec3 a, double b) {
            x = a.x, y = a.y, z = a.z, w = b;
        }
        dvec4(double a, dvec3 b) {
            x = a, y = b.x, z = b.y, w = b.z;
        }
        dvec4(dvec2 a, dvec2 b) {
            x = a.x, y = a.y, z = b.x, w = b.y;
        }
        dvec4(dvec2 a, double b, double c) {
            x = a.x, y = a.y, z = b, w = c;
        }
        dvec4(double a, double b, dvec2 c) {
            x = a, y = b, z = c.x, w = c.y;
        }
        dvec4(double a, dvec2 b, double c) {
            x = a, y = b.x, z = b.y, w = c;
        }
        dvec4(double v) {
            x = v, y = v, z = v, w = v;
        }
        dvec4(dvec4* v) {
            x = v->x, y = v->y, z = v->z, w = v->w;
        }
        
        dvec2 xy() {
            return dvec2(x, y);
        }
        dvec2 yx() {
            return dvec2(y, x);
        }
        dvec2 yz() {
            return dvec2(y, z);
        }
        dvec2 zy() {
            return dvec2(z, y);
        }
        dvec2 zw() {
            return dvec2(z, w);
        }
        dvec2 wz() {
            return dvec2(w, z);
        }
        dvec2 xz() {
            return dvec2(x, z);
        }
        dvec2 zx() {
            return dvec2(z, x);
        }
        dvec2 xw() {
            return dvec2(x, w);
        }
        dvec2 wx() {
            return dvec2(w, x);
        }
        dvec2 yw() {
            return dvec2(y, w);
        }
        dvec2 wy() {
            return dvec2(w, y);
        }
        dvec3 xyz() {
            return dvec3(x, y, z);
        }
        dvec3 xzy() {
            return dvec3(x, z, y);
        }
        dvec3 yxz() {
            return dvec3(y, x, z);
        }
        dvec3 yzx() {
            return dvec3(y, z, x);
        }
        dvec3 zxy() {
            return dvec3(z, x, y);
        }
        dvec3 zyx() {
            return dvec3(z, y, x);
        }
        dvec3 xyw() {
            return dvec3(x, y, w);
        }
        dvec3 xwy() {
            return dvec3(x, w, y);
        }
        dvec3 yxw() {
            return dvec3(y, x, w);
        }
        dvec3 ywx() {
            return dvec3(y, w, x);
        }
        dvec3 wxy() {
            return dvec3(w, x, y);
        }
        dvec3 wyx() {
            return dvec3(w, y, x);
        }
        dvec3 xzw() {
            return dvec3(x, z, w);
        }
        dvec3 xwz() {
            return dvec3(x, w, z);
        }
        dvec3 zxw() {
            return dvec3(z, x, w);
        }
        dvec3 zwx() {
            return dvec3(z, w, x);
        }
        dvec3 wxz() {
            return dvec3(w, x, z);
        }
        dvec3 wzx() {
            return dvec3(w, z, x);
        }
        dvec3 zyw() {
            return dvec3(z, y, w);
        }
        dvec3 zwy() {
            return dvec3(z, w, y);
        }
        dvec3 yzw() {
            return dvec3(y, z, w);
        }
        dvec3 ywz() {
            return dvec3(y, w, z);
        }
        dvec3 wzy() {
            return dvec3(w, z, y);
        }
        dvec3 wyz() {
            return dvec3(w, y, z);
        }
        dvec4 xyzw() {
            return dvec4(x, y, z, w);
        }
        dvec4 xywz() {
            return dvec4(x, y, w, z);
        }
        dvec4 xzyw() {
            return dvec4(x, z, y, w);
        }
        dvec4 xzwy() {
            return dvec4(x, z, w, y);
        }
        dvec4 xwyz() {
            return dvec4(x, w, y, z);
        }
        dvec4 xwzy() {
            return dvec4(x, w, z, y);
        }
        dvec4 yxzw() {
            return dvec4(y, x, z, w);
        }
        dvec4 yxwz() {
            return dvec4(y, x, w, z);
        }
        dvec4 yzxw() {
            return dvec4(y, z, x, w);
        }
        dvec4 yzwx() {
            return dvec4(y, z, w, x);
        }
        dvec4 ywxz() {
            return dvec4(y, w, x, z);
        }
        dvec4 ywzx() {
            return dvec4(y, w, z, x);
        }
        dvec4 zyxw() {
            return dvec4(z, y, x, w);
        }
        dvec4 zywx() {
            return dvec4(z, y, w, x);
        }
        dvec4 zxyw() {
            return dvec4(z, x, y, w);
        }
        dvec4 zxwy() {
            return dvec4(z, x, w, y);
        }
        dvec4 zwyx() {
            return dvec4(z, w, y, x);
        }
        dvec4 zwxy() {
            return dvec4(z, w, x, y);
        }
        dvec4 wyzx() {
            return dvec4(w, y, z, x);
        }
        dvec4 wyxz() {
            return dvec4(w, y, x, z);
        }
        dvec4 wzyx() {
            return dvec4(w, z, y, x);
        }
        dvec4 wzxy() {
            return dvec4(w, z, x, y);
        }
        dvec4 wxyz() {
            return dvec4(w, x, y, z);
        }
        dvec4 wxzy() {
            return dvec4(w, x, z, y);
        }
        
        void xy(dvec2 value) {
            x = value.x, y = value.y;
        }
        void yx(dvec2 value) {
            y = value.x, x = value.y;
        }
        void yz(dvec2 value) {
            y = value.x, z = value.y;
        }
        void zy(dvec2 value) {
            z = value.x, y = value.y;
        }
        void zw(dvec2 value) {
            z = value.x, w = value.y;
        }
        void wz(dvec2 value) {
            w = value.x, z = value.y;
        }
        void xz(dvec2 value) {
            x = value.x, z = value.y;
        }
        void zx(dvec2 value) {
            z = value.x, x = value.y;
        }
        void xw(dvec2 value) {
            x = value.x, w = value.y;
        }
        void wx(dvec2 value) {
            w = value.x, x = value.y;
        }
        void yw(dvec2 value) {
            y = value.x, w = value.y;
        }
        void wy(dvec2 value) {
            w = value.x, y = value.y;
        }
        void xyz(dvec3 value) {
            x = value.x, y = value.y, z = value.z;
        }
        void xzy(dvec3 value) {
            x = value.x, z = value.y, y = value.z;
        }
        void yxz(dvec3 value) {
            y = value.x, x = value.y, z = value.z;
        }
        void yzx(dvec3 value) {
            y = value.x, z = value.y, x = value.z;
        }
        void zxy(dvec3 value) {
            z = value.x, x = value.y, y = value.z;
        }
        void zyx(dvec3 value) {
            z = value.x, y = value.y, x = value.z;
        }
        void xyw(dvec3 value) {
            x = value.x, y = value.y, w = value.z;
        }
        void xwy(dvec3 value) {
            x = value.x, w = value.y, y = value.z;
        }
        void yxw(dvec3 value) {
            y = value.x, x = value.y, w = value.z;
        }
        void ywx(dvec3 value) {
            y = value.x, w = value.y, x = value.z;
        }
        void wxy(dvec3 value) {
            w = value.x, x = value.y, y = value.z;
        }
        void wyx(dvec3 value) {
            w = value.x, y = value.y, x = value.z;
        }
        void xzw(dvec3 value) {
            x = value.x, z = value.y, w = value.z;
        }
        void xwz(dvec3 value) {
            x = value.x, w = value.y, z = value.z;
        }
        void zxw(dvec3 value) {
            z = value.x, x = value.y, w = value.z;
        }
        void zwx(dvec3 value) {
            z = value.x, w = value.y, x = value.z;
        }
        void wxz(dvec3 value) {
            w = value.x, x = value.y, z = value.z;
        }
        void wzx(dvec3 value) {
            w = value.x, z = value.y, x = value.z;
        }
        void zyw(dvec3 value) {
            z = value.x, y = value.y, w = value.z;
        }
        void zwy(dvec3 value) {
            z = value.x, w = value.y, y = value.z;
        }
        void yzw(dvec3 value) {
            y = value.x, z = value.y, w = value.z;
        }
        void ywz(dvec3 value) {
            y = value.x, w = value.y, z = value.z;
        }
        void wzy(dvec3 value) {
            w = value.x, z = value.y, y = value.z;
        }
        void wyz(dvec3 value) {
            w = value.x, y = value.y, z = value.z;
        }
        void xyzw(dvec4 value) {
            x = value.x, y = value.y, z = value.z, w = value.w;
        }
        void xywz(dvec4 value) {
            x = value.x, y = value.y, w = value.z, z = value.w;
        }
        void xzyw(dvec4 value) {
            x = value.x, z = value.y, y = value.z, w = value.w;
        }
        void xzwy(dvec4 value) {
            x = value.x, z = value.y, w = value.z, y = value.w;
        }
        void xwyz(dvec4 value) {
            x = value.x, w = value.y, y = value.z, z = value.w;
        }
        void xwzy(dvec4 value) {
            x = value.x, w = value.y, z = value.z, y = value.w;
        }
        void yxzw(dvec4 value) {
            y = value.x, x = value.y, z = value.z, w = value.w;
        }
        void yxwz(dvec4 value) {
            y = value.x, x = value.y, w = value.z, z = value.w;
        }
        void yzxw(dvec4 value) {
            y = value.x, z = value.y, x = value.z, w = value.w;
        }
        void yzwx(dvec4 value) {
            y = value.x, z = value.y, w = value.z, x = value.w;
        }
        void ywxz(dvec4 value) {
            y = value.x, w = value.y, x = value.z, z = value.w;
        }
        void ywzx(dvec4 value) {
            y = value.x, w = value.y, z = value.z, x = value.w;
        }
        void zyxw(dvec4 value) {
            z = value.x, y = value.y, x = value.z, w = value.w;
        }
        void zywx(dvec4 value) {
            z = value.x, y = value.y, w = value.z, x = value.w;
        }
        void zxyw(dvec4 value) {
            z = value.x, x = value.y, y = value.z, w = value.w;
        }
        void zxwy(dvec4 value) {
            z = value.x, x = value.y, w = value.z, y = value.w;
        }
        void zwyx(dvec4 value) {
            z = value.x, w = value.y, y = value.z, x = value.w;
        }
        void zwxy(dvec4 value) {
            z = value.x, w = value.y, x = value.z, y = value.w;
        }
        void wyzx(dvec4 value) {
            w = value.x, y = value.y, z = value.z, x = value.w;
        }
        void wyxz(dvec4 value) {
            w = value.x, y = value.y, x = value.z, z = value.w;
        }
        void wzyx(dvec4 value) {
            w = value.x, z = value.y, y = value.z, x = value.w;
        }
        void wzxy(dvec4 value) {
            w = value.x, z = value.y, x = value.z, y = value.w;
        }
        void wxyz(dvec4 value) {
            w = value.x, x = value.y, y = value.z, z = value.w;
        }
        void wxzy(dvec4 value) {
            w = value.x, x = value.y, z = value.z, y = value.w;
        }
        
        double length2() {
            return x*x+y*y+z*z+w*w;
        }
        double length() {
            return std::sqrt(x*x+y*y+z*z+w*w);
        }
        
        dvec4 normalize() {
            double len = length();
            
            if (len < 1e-13) return dvec4(0.0);
            
            return dvec4(x/len, y/len, z/len, w/len);
        }
        
        dvec4 operator-() {
            return dvec4(-x, -y, -z, -w);
        }
        dvec4 operator~() {
            return normalize();
        }
        
        double operator[](int i) {
            switch (i) {
                case 0: return x;
                case 1: return y;
                case 2: return z;
                case 3: return w;
                default: return 0.0;
            }
        }
        
        dvec4 operator+(dvec4 other) {
            return dvec4(x+other.x, y+other.y, z+other.z, w+other.w);
        }
        dvec4 operator-(dvec4 other) {
            return dvec4(x-other.x, y-other.y, z-other.z, w-other.w);
        }
        dvec4 operator*(dvec4 other) {
            return dvec4(x*other.x, y*other.y, z*other.z, w*other.w);
        }
        dvec4 operator/(dvec4 other) {
            return dvec4(x/other.x, y/other.y, z/other.z, w/other.w);
        }
        
        void operator+=(dvec4 other) {
            x += other.x, y += other.y, z += other.z, w += other.w;
        }
        void operator-=(dvec4 other) {
            x -= other.x, y -= other.y, z -= other.z, w -= other.w;
        }
        void operator*=(dvec4 other) {
            x *= other.x, y *= other.y, z *= other.z, w *= other.w;
        }
        void operator/=(dvec4 other) {
            x /= other.x, y /= other.y, z /= other.z, w /= other.w;
        }

        dvec4 operator+(float other) {
            return dvec4(x+other, y+other, z+other, w+other);
        }
        dvec4 operator-(float other) {
            return dvec4(x-other, y-other, z-other, w-other);
        }
        dvec4 operator*(float other) {
            return dvec4(x*other, y*other, z*other, w*other);
        }
        dvec4 operator/(float other) {
            return dvec4(x/other, y/other, z/other, w/other);
        }
        
        void operator+=(float other) {
            x += other, y += other, z += other, w += other;
        }
        void operator-=(float other) {
            x -= other, y -= other, z -= other, w -= other;
        }
        void operator*=(float other) {
            x *= other, y *= other, z *= other, w *= other;
        }
        void operator/=(float other) {
            x /= other, y /= other, z /= other, w /= other;
        }

        dvec4 operator+(double other) {
            return dvec4(x+other, y+other, z+other, w+other);
        }
        dvec4 operator-(double other) {
            return dvec4(x-other, y-other, z-other, w-other);
        }
        dvec4 operator*(double other) {
            return dvec4(x*other, y*other, z*other, w*other);
        }
        dvec4 operator/(double other) {
            return dvec4(x/other, y/other, z/other, w/other);
        }
        
        void operator+=(double other) {
            x += other, y += other, z += other, w += other;
        }
        void operator-=(double other) {
            x -= other, y -= other, z -= other, w -= other;
        }
        void operator*=(double other) {
            x *= other, y *= other, z *= other, w *= other;
        }
        void operator/=(double other) {
            x /= other, y /= other, z /= other, w /= other;
        }
        
        bvec4 operator==(dvec4 other) {
            return bvec4(x == other.x, y == other.y, z == other.z, w == other.w);
        }
        bvec4 operator!=(dvec4 other) {
            return bvec4(x != other.x, y != other.y, z != other.z, w != other.w);
        }
        bvec4 operator>(dvec4 other) {
            return bvec4(x > other.x, y > other.y, z > other.z, w > other.w);
        }
        bvec4 operator<(dvec4 other) {
            return bvec4(x < other.x, y < other.y, z < other.z, w < other.w);
        }
        bvec4 operator<=(dvec4 other) {
            return bvec4(x <= other.x, y <= other.y, z <= other.z, w <= other.w);
        }
        bvec4 operator>=(dvec4 other) {
            return bvec4(x >= other.x, y >= other.y, z >= other.z, w >= other.w);
        }

        bvec4 operator==(float other) {
            return bvec4(x == other, y == other, z == other, w == other);
        }
        bvec4 operator!=(float other) {
            return bvec4(x != other, y != other, z != other, w != other);
        }
        bvec4 operator>(float other) {
            return bvec4(x > other, y > other, z > other, w > other);
        }
        bvec4 operator<(float other) {
            return bvec4(x < other, y < other, z < other, w < other);
        }
        bvec4 operator<=(float other) {
            return bvec4(x <= other, y <= other, z <= other, w <= other);
        }
        bvec4 operator>=(float other) {
            return bvec4(x >= other, y >= other, z >= other, w >= other);
        }
        
        bvec4 operator==(double other) {
            return bvec4(x == other, y == other, z == other, w == other);
        }
        bvec4 operator!=(double other) {
            return bvec4(x != other, y != other, z != other, w != other);
        }
        bvec4 operator>(double other) {
            return bvec4(x > other, y > other, z > other, w > other);
        }
        bvec4 operator<(double other) {
            return bvec4(x < other, y < other, z < other, w < other);
        }
        bvec4 operator<=(double other) {
            return bvec4(x <= other, y <= other, z <= other, w <= other);
        }
        bvec4 operator>=(double other) {
            return bvec4(x >= other, y >= other, z >= other, w >= other);
        }
    };

    bool any(bvec2 v) {
        return v.any();
    }
    bool any(bvec3 v) {
        return v.any();
    }
    bool any(bvec4 v) {
        return v.any();
    }

    bool all(bvec2 v) {
        return v.all();
    }
    bool all(bvec3 v) {
        return v.all();
    }
    bool all(bvec4 v) {
        return v.all();
    }
}