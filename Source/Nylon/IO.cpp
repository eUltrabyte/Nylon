#include "IO.hpp"

namespace nl {
    IO::IO()
        : m_vram((i8*)0xb8000), m_position({0, 0}), m_size(80 * 25 * 2), m_symbols((i8*)"0123456789abcdef") {
    }

    IO::~IO() {
        delete m_symbols;
    }

    void IO::Out(i8* data, text::Color color) {
        for(i32 i = 0; data[i] != '\0'; ++i) {
            if(data[i] == '\n') {
                m_position.y += 1;
                m_position.x = 0;
            } else {
                m_vram[m_position.x + (m_position.y * 80 * 2)] = data[i];
                m_vram[m_position.x + (m_position.y * 80 * 2) + 1] = color;
                m_position.x += 2;
            }
        }
    }

    void IO::Out(i32 data, text::Type type, text::Color color) {
        i8 buffer[64];
        i8* string = &buffer[63];
        *string = '\0';

        i32 base = 0;
        if(type == text::Type::Dec) {
            base = 10;
        } else if(type == text::Type::Bin) {
            base = 2;
        } else if(type == text::Type::Oct) {
            base = 8;
        } else if(type == text::Type::Hex) {
            base = 16;
        }

        while(data != 0) {
            *--string = m_symbols[data % base];
            data /= base;
        }

        Out(string, color);
    }

    void IO::Endl() {
        Out((i8*)"\n");
    }
    
    void IO::Clear() {
        m_position = { 0, 0 };
        for(i32 i = 0; i < m_size; i += 2) {
            m_vram[i] = ' ';
            m_vram[i + 1] = 0;
        }

        m_vram[m_position.x + (m_position.y * 80 * 2)] = ' ';
        m_vram[m_position.x + (m_position.y * 80 * 2) + 1] = 0;
    }
};