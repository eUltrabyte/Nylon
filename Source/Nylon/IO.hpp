#pragma once
#ifndef NYLON_IO_HPP
#define NYLON_IO_HPP

#define NLAPI extern "C"

#include "Types.hpp"
#include "Allocator.hpp"

namespace nl {
    namespace text {
        enum class Type : i8 {
            Dec = 0,
            Bin,
            Oct,
            Hex,
        };

        enum Color : i8 {
            None = 0,
            Blue,
            Green,
            Cyan,
            Red,
            Purple,
            Brown,
            Gray,
            DarkGray,
            LightBlue,
            LightGreen,
            LightCyan,
            LightRed,
            LightPurple,
            Yellow,
            White,
        };
    };

    class IO {
    public:
        IO();
        virtual ~IO();

        virtual void Out(i8* data, text::Color color = text::Color::Gray);
        virtual void Out(i32 data, text::Type type, text::Color color = text::Color::Gray);
        virtual void Endl();
        virtual void Clear();

    private:
        i8* m_symbols;
        vec2u m_position;
        i32 m_size;
        i8* m_vram;

    };
};

#endif