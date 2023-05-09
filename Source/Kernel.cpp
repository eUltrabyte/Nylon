#include "Nylon/IO.hpp"
#include "Nylon/Allocator.hpp"

NLAPI nl::i32 NlMain(void* multiboot, nl::u32 magicNumber) {
    nl::u32* memory = (nl::u32*)(((nl::size_t)multiboot) + 8);
    nl::size_t size = 10 * 1024 * 1024;
    *nl::Allocator::Get() = nl::Allocator(size, *memory * 1024 - size - 10 * 1024);

    nl::IO io;
    io.Clear();
    io.Out((nl::i32)nl::Allocator::Get()->Allocate(1024), nl::text::Type::Hex, nl::text::Color::Red);
    io.Endl();
    io.Out((nl::i8*)"test\n");
    io.Out((nl::i8*)"test2\n");
    io.Out((nl::i8*)"test3\n");
    io.Out((nl::i8*)"test4\n");

    return 0;
}