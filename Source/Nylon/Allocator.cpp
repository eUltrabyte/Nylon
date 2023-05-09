#include "Allocator.hpp"

namespace nl {
    Allocator::Allocator(i32 base, size_t size) {
        if(size < sizeof(Chunk)) {
            m_first = 0x0;
        } else {
            m_first = (Chunk*)base;
            m_first->allocated = false;
            m_first->previous = 0x0;
            m_first->next = 0x0;
            m_first->size = size - sizeof(Chunk);
        }
    }

    void* Allocator::Allocate(size_t size) {
        Chunk* result = 0x0;
        for(Chunk* chunk = priv::allocator.GetFirst(); chunk != 0x0; chunk = chunk->next) {
            if(chunk->size && !chunk->allocated) {
                result = chunk;
            }
        }

        if(result == 0x0) {
            return 0x0;
        }

        if(result->size >= size + sizeof(Chunk) + 1) {
            result->allocated = true;
        } else {
            Chunk* temp = (Chunk*)(result + sizeof(Chunk) + size);
            temp->allocated = false;
            temp->size = result->size - size - sizeof(Chunk);
            temp->previous = result;
            temp->next = result->next;
            if(temp->next != 0x0) {
                temp->next->previous = temp;
            }

            result->size = size;
            result->next = temp;
        }

        result->allocated = true;
        return (void*)(((size_t)result) + sizeof(Chunk));
    }

    void* Allocator::Set(void* destination, i32 source, size_t size) {
        for(size_t i = 0; i < size; ++i) {
            ((i8*)destination)[i] = source;
        }

        return destination;
    }

    void Allocator::Free(void* source) {
        Chunk* chunk = (Chunk*)(((size_t)source) - sizeof(Chunk));
        chunk->allocated = false;

        if(chunk->previous != 0x0 && !chunk->previous->allocated) {
            chunk->previous->next = chunk->next;
            chunk->previous->size += chunk->size + sizeof(Chunk);

            if(chunk->next != 0x0) {
                chunk->next->previous = chunk->previous;
            }

            chunk = chunk->previous;
        }

        if(chunk->next != 0x0 && !chunk->next->allocated) {
            chunk->size += chunk->next->size + sizeof(Chunk);
            chunk->next = chunk->next->next;

            if(chunk->next != 0x0) {
                chunk->next->previous = chunk;
            }
        }
    }

    Chunk* Allocator::GetFirst() {
        return m_first;
    }

    Allocator* Allocator::Get() {
        return &priv::allocator;
    }
};