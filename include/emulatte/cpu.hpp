#pragma once

#include <vector>

#include "fundamentals.hpp"

namespace emulatte
{
    // A representation of a 6502 opcode. Each
    // opcode is a byte, and is structured in such
    // a way that you can deduce multiple things
    // about it just by its value. However, I will
    // just be creating a vector of every opcode
    // (all 255 of them!)
    // The default instruction will be "BRK".
    struct instruction
    {
        byte value = 0x00;
        const char* name = "BRK";
        // This is a simple enum to represent the
        // different addressing modes of the opcodes.
        // Each will be briefly described within.
        enum class addressing_mode
        {
            // The behavior of this opcode is sort
            // of "implicit" to it - BRK, for example,
            // doesn't take any operands, so it does
            // not have an addressing mode.
            Implicit,
            // This opcode references the Accumulator
            // implicitly - very slightly different
            // from the Implicit tag.
            Accumulator,
            // This opcode takes the byte following it
            // and uses that as a value directly.
            Immediate,
            // This opcode does the same as Immediate,
            // but treats the byte as signed. This is
            // only used by branch instructions.
            Relative,
            // This opcode references zero page memory,
            // pulling from the first 255 bytes of our
            // internal memory.
            ZeroPage,
            // This opcode references zero page memory,
            // offset by the X register's value.
            ZeroPageX,
            // This opcode references zero page memory,
            // offset by the Y register's value.
            ZeroPageY,
            // This opcode takes the next two bytes,
            // constructs an address (lo-hi order),
            // and grabs the byte at that place in
            // memory.
            Absolute,
            // This opcode functions like Absolute and
            // offsets it by the X register. If this
            // offset causes the address to pass a
            // page boundary (the higher 8 bits change),
            // it takes an extra CPU cycle to complete.
            AbsoluteX,
            // This opcode functions like Absolute and
            // offsets it by the Y register. If this
            // offset causes the address to pass a
            // page boundary (the higher 8 bits change),
            // it takes an extra CPU cycle to complete.
            AbsoluteY,
            // This opcode takes the next two bytes,
            // constructs an address (lo-hi order),
            // then grabs the two bytes at that spot
            // in memory, and constructs ANOTHER
            // address, finally grabbing the byte at
            // THAT location. This is ONLY used by JMP.
            Indirect,
            // This opcode functions similar to
            // Indirect, but instead takes only one
            // byte and looks in zero page memory for
            // the desired byte, with the initial zpg
            // address being offset by the X register.
            IndirectX,
            // This opcode functions similarly to
            // IndirectX, but instead offsets the
            // second address by the Y register.
            IndirectY,
        } mode;
        // This is how many CPU cycles it takes to
        // execute this instruction. Every opcode
        // takes at least 2 cycles, with the
        // addressing mode altering that number as
        // necessary.
        byte cycles = 7;
    };

    // This is effectively going to be a 6502,
    // just in code.
    struct cpu
    {
        // A simple structure to make memory read
        // and writes easier.
        struct
        {
            // We use a vector because we want to
            // put the 64KB on the heap, it's too
            // much to just have on the stack at
            // all times.
            std::vector<byte> internal_memory = std::vector<byte>(0x10000);

            // We return by reference so that memory
            // can be modified after a read call.
            // This will also allow us to access the
            // PPU and APU via the registers in CPU
            // memory.
            byte& read(address addy)
            {
                if ((addy >= 0x2000 && addy <= 0x2007) || addy == 0x4014)
                {
                    // ppu registers. for now, we'll
                    // make a runtime crash.
                    return internal_memory[0x10000];
                }
                else if (addy >= 0x4000 && addy <= 0x4019)
                {
                    // apu registers. this will also
                    // be a runtime crash for now.
                    return internal_memory[0x10000];
                }
                else
                {
                    return internal_memory[addy];
                }
            };

            // The inverse of the read operation,
            // just a simple write.
            void write(address addy, byte value)
            {
                if ((addy >= 0x2000 && addy <= 0x2007) || addy == 0x4014)
                {
                    // ppu registers. for now, we'll
                    // make a runtime crash.
                    internal_memory[0x10000] = value;
                }
                else if (addy >= 0x4000 && addy <= 0x4019)
                {
                    // apu registers. this will also
                    // be a runtime crash for now.
                    internal_memory[0x10000] = value;
                }
                else
                {
                    internal_memory[addy] = value;
                }
            };
        } memory;


    };
};