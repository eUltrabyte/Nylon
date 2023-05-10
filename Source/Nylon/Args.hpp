#pragma once
#ifndef NYLON_ARGS_HPP
#define NYLON_ARGS_HPP

#include "Types.hpp"
#include "Allocator.hpp"

namespace nl {
    class Args {
    public:
        Args() = default;
        virtual ~Args() = default;

        template<typename T>
        void Start(T value) {
            m_args = (i8*)&value + sizeof(value);
        }
        
        template<typename T>
        i8* Next(T value) {
            T next = *((T*)m_args);
            m_args += sizeof(T);
            return m_args;
        }

        virtual void End() {
            m_args = nullptr;
        }

    private:
        i8* m_args;

    };
};

#endif