NYLON_ASSEMBLY_COMPILER = nasm
NYLON_CXX_COMPILER = g++
NYLON_LINKER = ld

NYLON_EMULATOR = qemu-system-x86_64

NYLON_ASSEMBLY_FILES = Source/*.asm
NYLON_LINKER_FILES = Build/*.o

NYLON_ASSEMBLY_FLAGS = -felf32
NYLON_CXX_FLAGS = -m32 -c -fno-use-cxa-atexit -nostdlib -fno-builtin -fno-rtti -fno-exceptions -fno-leading-underscore -fpermissive
NYLON_LINKER_FLAGS = -melf_i386

all:
	$(NYLON_ASSEMBLY_COMPILER) $(NYLON_ASSEMBLY_FILES) $(NYLON_ASSEMBLY_FLAGS) -o Build/Bootloader.o
	$(NYLON_CXX_COMPILER) Source/Kernel.cpp $(NYLON_CXX_FLAGS) -o Build/Kernel.o
	$(NYLON_LINKER) $(NYLON_LINKER_FILES) $(NYLON_LINKER_FLAGS) -T Source/Linker.ld -o Build/Nylon

Build/%.o: Source/Nylon/%.cpp
	$(NYLON_CXX_COMPILER) $< $(NYLON_CXX_FLAGS) -o $@

run:
	$(NYLON_EMULATOR) -kernel Build/Nylon

clean:
	rm -rf Build/*.o