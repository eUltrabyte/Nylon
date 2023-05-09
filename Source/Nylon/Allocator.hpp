#pragma once
#ifndef NYLON_ALLOCATOR_HPP
#define NYLON_ALLOCATOR_HPP

#include "Types.hpp"

namespace nl {
    struct Chunk {
        Chunk* next;
        Chunk* previous;
        bool allocated;
        i32 size;
    };

    class Allocator {
    public:
        Allocator() = default;
        Allocator(i32 base, size_t size);

        static void* Allocate(size_t size);
        static void* Set(void* destination, i32 source, size_t size);
        static void Free(void* source);

        virtual Chunk* GetFirst();
        static Allocator* Get();

    private:
        Chunk* m_first;

    };

    namespace priv {
        inline Allocator allocator;
    };
};

inline void* operator new(nl::size_t, void* pointer) { return pointer; }
inline void* operator new[](nl::size_t, void* pointer) { return pointer; }
inline void* operator new(nl::size_t size) { return nl::Allocator::Get()->Allocate(size); }

inline void operator delete(void* pointer) { nl::Allocator::Get()->Free(pointer); }
inline void operator delete[](void* pointer) { nl::Allocator::Get()->Free(pointer); }
inline void operator delete(void* pointer, nl::size_t) { nl::Allocator::Get()->Free(pointer); }
inline void operator delete[](void* pointer, nl::size_t) { nl::Allocator::Get()->Free(pointer); }

#endif