#pragma once
#ifndef NYLON_TYPES_HPP
#define NYLON_TYPES_HPP

namespace nl {
    using i8 = signed char;
    using i16 = signed short;
    using i32 = signed int;
    using i64 = signed long long int;

    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long int;

    using f32 = float;

    using l32 = unsigned long;
    using l64 = unsigned long long;

    using size_t = unsigned int;

    template<typename T>
    struct vec2 {
    public:
        T x;
        T y;

        vec2() : x(0), y(0) { }
        vec2(T x) : x(x), y(0) { }
        vec2(T x, T y) : x(x), y(y) { }

    };

    using vec2i = vec2<i32>;
    using vec2f = vec2<f32>;
    using vec2u = vec2<u32>;
    using vec2l = vec2<l32>;
};

#endif