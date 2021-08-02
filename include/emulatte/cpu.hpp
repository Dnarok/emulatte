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
        } mode = addressing_mode::Implicit;
    };

    // By using a vector sorted by opcode value, we
    // can effectively index each opcode directly,
    // simply given a byte.
    std::vector<instruction> instruction_set =
    {
        { 0, "BRK", instruction::addressing_mode::Implicit },
        { 1, "ORA", instruction::addressing_mode::IndirectX },
        { 2, "JAM", instruction::addressing_mode::Implicit },
        { 3, "SLO", instruction::addressing_mode::IndirectX },
        { 4, "NOP", instruction::addressing_mode::ZeroPage },
        { 5, "ORA", instruction::addressing_mode::ZeroPage },
        { 6, "ASL", instruction::addressing_mode::ZeroPage },
        { 7, "SLO", instruction::addressing_mode::ZeroPage },
        { 8, "PHP", instruction::addressing_mode::Implicit },
        { 9, "ORA", instruction::addressing_mode::Immediate },
        { 10, "ASL", instruction::addressing_mode::Accumulator },
        { 11, "ANC", instruction::addressing_mode::Immediate },
        { 12, "NOP", instruction::addressing_mode::Absolute },
        { 13, "ORA", instruction::addressing_mode::Absolute },
        { 14, "ASL", instruction::addressing_mode::Absolute },
        { 15, "SLO", instruction::addressing_mode::Absolute },
        { 16, "BPL", instruction::addressing_mode::Relative },
        { 17, "ORA", instruction::addressing_mode::IndirectY },
        { 18, "JAM", instruction::addressing_mode::Implicit },
        { 19, "SLO", instruction::addressing_mode::IndirectY },
        { 20, "NOP", instruction::addressing_mode::ZeroPageX },
        { 21, "ORA", instruction::addressing_mode::ZeroPageX },
        { 22, "ASL", instruction::addressing_mode::ZeroPageX },
        { 23, "SLO", instruction::addressing_mode::ZeroPageX },
        { 24, "CLC", instruction::addressing_mode::Implicit },
        { 25, "ORA", instruction::addressing_mode::AbsoluteY },
        { 26, "NOP", instruction::addressing_mode::Implicit },
        { 27, "SLO", instruction::addressing_mode::AbsoluteY },
        { 28, "NOP", instruction::addressing_mode::AbsoluteX },
        { 29, "ORA", instruction::addressing_mode::AbsoluteX },
        { 30, "ASL", instruction::addressing_mode::AbsoluteX },
        { 31, "SLO", instruction::addressing_mode::AbsoluteX },
        { 32, "JSR", instruction::addressing_mode::Absolute },
        { 33, "AND", instruction::addressing_mode::IndirectX },
        { 34, "JAM", instruction::addressing_mode::Implicit },
        { 35, "RLA", instruction::addressing_mode::IndirectX },
        { 36, "BIT", instruction::addressing_mode::ZeroPage },
        { 37, "AND", instruction::addressing_mode::ZeroPage },
        { 38, "ROL", instruction::addressing_mode::ZeroPage },
        { 39, "RLA", instruction::addressing_mode::ZeroPage },
        { 40, "PLP", instruction::addressing_mode::Implicit },
        { 41, "AND", instruction::addressing_mode::Immediate },
        { 42, "ROL", instruction::addressing_mode::Accumulator },
        { 43, "ANC", instruction::addressing_mode::Immediate },
        { 44, "BIT", instruction::addressing_mode::Absolute },
        { 45, "AND", instruction::addressing_mode::Absolute },
        { 46, "ROL", instruction::addressing_mode::Absolute },
        { 47, "RLA", instruction::addressing_mode::Absolute },
        { 48, "BMI", instruction::addressing_mode::Relative },
        { 49, "AND", instruction::addressing_mode::IndirectY },
        { 50, "JAM", instruction::addressing_mode::Implicit },
        { 51, "RLA", instruction::addressing_mode::IndirectY },
        { 52, "NOP", instruction::addressing_mode::ZeroPageX },
        { 53, "AND", instruction::addressing_mode::ZeroPageX },
        { 54, "ROL", instruction::addressing_mode::ZeroPageX },
        { 55, "RLA", instruction::addressing_mode::ZeroPageX },
        { 56, "SEC", instruction::addressing_mode::Implicit },
        { 57, "AND", instruction::addressing_mode::AbsoluteY },
        { 58, "NOP", instruction::addressing_mode::Implicit },
        { 59, "RLA", instruction::addressing_mode::AbsoluteY },
        { 60, "NOP", instruction::addressing_mode::AbsoluteX },
        { 61, "AND", instruction::addressing_mode::AbsoluteX },
        { 62, "ROL", instruction::addressing_mode::AbsoluteX },
        { 63, "RLA", instruction::addressing_mode::AbsoluteX },
        { 64, "RTI", instruction::addressing_mode::Implicit },
        { 65, "EOR", instruction::addressing_mode::IndirectX },
        { 66, "JAM", instruction::addressing_mode::Implicit },
        { 67, "SRE", instruction::addressing_mode::IndirectX },
        { 68, "NOP", instruction::addressing_mode::ZeroPage },
        { 69, "EOR", instruction::addressing_mode::ZeroPage },
        { 70, "LSR", instruction::addressing_mode::ZeroPage },
        { 71, "SRE", instruction::addressing_mode::ZeroPage },
        { 72, "PHA", instruction::addressing_mode::Implicit },
        { 73, "EOR", instruction::addressing_mode::Immediate },
        { 74, "LSR", instruction::addressing_mode::Accumulator },
        { 75, "ALR", instruction::addressing_mode::Immediate },
        { 76, "JMP", instruction::addressing_mode::Absolute },
        { 77, "EOR", instruction::addressing_mode::Absolute },
        { 78, "LSR", instruction::addressing_mode::Absolute },
        { 79, "SRE", instruction::addressing_mode::Absolute },
        { 80, "BVC", instruction::addressing_mode::Relative },
        { 81, "EOR", instruction::addressing_mode::IndirectY },
        { 82, "JAM", instruction::addressing_mode::Implicit },
        { 83, "SRE", instruction::addressing_mode::IndirectY },
        { 84, "NOP", instruction::addressing_mode::ZeroPageX },
        { 85, "EOR", instruction::addressing_mode::ZeroPageX },
        { 86, "LSR", instruction::addressing_mode::ZeroPageX },
        { 87, "SRE", instruction::addressing_mode::ZeroPageX },
        { 88, "CLI", instruction::addressing_mode::Implicit },
        { 89, "EOR", instruction::addressing_mode::AbsoluteY },
        { 90, "NOP", instruction::addressing_mode::Implicit },
        { 91, "SRE", instruction::addressing_mode::AbsoluteY },
        { 92, "NOP", instruction::addressing_mode::AbsoluteX },
        { 93, "EOR", instruction::addressing_mode::AbsoluteX },
        { 94, "LSR", instruction::addressing_mode::AbsoluteX },
        { 95, "SRE", instruction::addressing_mode::AbsoluteX },
        { 96, "RTS", instruction::addressing_mode::Implicit },
        { 97, "ADC", instruction::addressing_mode::IndirectX },
        { 98, "JAM", instruction::addressing_mode::Implicit },
        { 99, "RRA", instruction::addressing_mode::IndirectX },
        { 100, "NOP", instruction::addressing_mode::ZeroPage },
        { 101, "ADC", instruction::addressing_mode::ZeroPage },
        { 102, "ROR", instruction::addressing_mode::ZeroPage },
        { 103, "RRA", instruction::addressing_mode::ZeroPage },
        { 104, "PLA", instruction::addressing_mode::Implicit },
        { 105, "ADC", instruction::addressing_mode::Immediate },
        { 106, "ROR", instruction::addressing_mode::Accumulator },
        { 107, "ARR", instruction::addressing_mode::Immediate },
        { 108, "JMP", instruction::addressing_mode::Indirect },
        { 109, "ADC", instruction::addressing_mode::Absolute },
        { 110, "ROR", instruction::addressing_mode::Absolute },
        { 111, "RRA", instruction::addressing_mode::Absolute },
        { 112, "BVS", instruction::addressing_mode::Relative },
        { 113, "ADC", instruction::addressing_mode::IndirectY },
        { 114, "JAM", instruction::addressing_mode::Implicit },
        { 115, "RRA", instruction::addressing_mode::IndirectY },
        { 116, "NOP", instruction::addressing_mode::ZeroPageX },
        { 117, "ADC", instruction::addressing_mode::ZeroPageX },
        { 118, "ROR", instruction::addressing_mode::ZeroPageX },
        { 119, "RRA", instruction::addressing_mode::ZeroPageX },
        { 120, "SEI", instruction::addressing_mode::Implicit },
        { 121, "ADC", instruction::addressing_mode::AbsoluteY },
        { 122, "NOP", instruction::addressing_mode::Implicit },
        { 123, "RRA", instruction::addressing_mode::AbsoluteY },
        { 124, "NOP", instruction::addressing_mode::AbsoluteX },
        { 125, "ADC", instruction::addressing_mode::AbsoluteX },
        { 126, "ROR", instruction::addressing_mode::AbsoluteX },
        { 127, "RRA", instruction::addressing_mode::AbsoluteX },
        { 128, "NOP", instruction::addressing_mode::Immediate },
        { 129, "STA", instruction::addressing_mode::IndirectX },
        { 130, "NOP", instruction::addressing_mode::Immediate },
        { 131, "SAX", instruction::addressing_mode::IndirectX },
        { 132, "STY", instruction::addressing_mode::ZeroPage },
        { 133, "STA", instruction::addressing_mode::ZeroPage },
        { 134, "STX", instruction::addressing_mode::ZeroPage },
        { 135, "SAX", instruction::addressing_mode::ZeroPage },
        { 136, "DEY", instruction::addressing_mode::Implicit },
        { 137, "NOP", instruction::addressing_mode::Immediate },
        { 138, "TXA", instruction::addressing_mode::Implicit },
        { 139, "ANE", instruction::addressing_mode::Immediate },
        { 140, "STY", instruction::addressing_mode::Absolute },
        { 141, "STA", instruction::addressing_mode::Absolute },
        { 142, "STX", instruction::addressing_mode::Absolute },
        { 143, "SAX", instruction::addressing_mode::Absolute },
        { 144, "BCC", instruction::addressing_mode::Relative },
        { 145, "STA", instruction::addressing_mode::IndirectY },
        { 146, "JAM", instruction::addressing_mode::Implicit },
        { 147, "SHA", instruction::addressing_mode::IndirectY },
        { 148, "STY", instruction::addressing_mode::ZeroPageX },
        { 149, "STA", instruction::addressing_mode::ZeroPageX },
        { 150, "STX", instruction::addressing_mode::ZeroPageY },
        { 151, "SAX", instruction::addressing_mode::ZeroPageY },
        { 152, "TYA", instruction::addressing_mode::Implicit },
        { 153, "STA", instruction::addressing_mode::AbsoluteY },
        { 154, "TXS", instruction::addressing_mode::Implicit },
        { 155, "TAS", instruction::addressing_mode::AbsoluteY },
        { 156, "SHY", instruction::addressing_mode::AbsoluteX },
        { 157, "STA", instruction::addressing_mode::AbsoluteX },
        { 158, "SHX", instruction::addressing_mode::AbsoluteY },
        { 159, "SHA", instruction::addressing_mode::AbsoluteY },
        { 160, "LDY", instruction::addressing_mode::Immediate },
        { 161, "LDA", instruction::addressing_mode::IndirectX },
        { 162, "LDX", instruction::addressing_mode::Immediate },
        { 163, "LAX", instruction::addressing_mode::IndirectX },
        { 164, "LDY", instruction::addressing_mode::ZeroPage },
        { 165, "LDA", instruction::addressing_mode::ZeroPage },
        { 166, "LDX", instruction::addressing_mode::ZeroPage },
        { 167, "LAX", instruction::addressing_mode::ZeroPage },
        { 168, "TAY", instruction::addressing_mode::Implicit },
        { 169, "LDA", instruction::addressing_mode::Immediate },
        { 170, "TAX", instruction::addressing_mode::Implicit },
        { 171, "LXA", instruction::addressing_mode::Immediate },
        { 172, "LDY", instruction::addressing_mode::Absolute },
        { 173, "LDA", instruction::addressing_mode::Absolute },
        { 174, "LDX", instruction::addressing_mode::Absolute },
        { 175, "LAX", instruction::addressing_mode::Absolute },
        { 176, "BCS", instruction::addressing_mode::Relative },
        { 177, "LDA", instruction::addressing_mode::IndirectY },
        { 178, "JAM", instruction::addressing_mode::Implicit },
        { 179, "LAX", instruction::addressing_mode::IndirectY },
        { 180, "LDY", instruction::addressing_mode::ZeroPageX },
        { 181, "LDA", instruction::addressing_mode::ZeroPageX },
        { 182, "LDX", instruction::addressing_mode::ZeroPageY },
        { 183, "LAX", instruction::addressing_mode::ZeroPageY },
        { 184, "CLV", instruction::addressing_mode::Implicit },
        { 185, "LDA", instruction::addressing_mode::AbsoluteY },
        { 186, "TSX", instruction::addressing_mode::Implicit },
        { 187, "LAS", instruction::addressing_mode::AbsoluteY },
        { 188, "LDY", instruction::addressing_mode::AbsoluteX },
        { 189, "LDA", instruction::addressing_mode::AbsoluteX },
        { 190, "LDX", instruction::addressing_mode::AbsoluteY },
        { 191, "LAX", instruction::addressing_mode::AbsoluteY },
        { 192, "CPY", instruction::addressing_mode::Immediate },
        { 193, "CMP", instruction::addressing_mode::IndirectX },
        { 194, "NOP", instruction::addressing_mode::Immediate },
        { 195, "DCP", instruction::addressing_mode::IndirectX },
        { 196, "CPY", instruction::addressing_mode::ZeroPage },
        { 197, "CMP", instruction::addressing_mode::ZeroPage },
        { 198, "DEC", instruction::addressing_mode::ZeroPage },
        { 199, "DCP", instruction::addressing_mode::ZeroPage },
        { 200, "INY", instruction::addressing_mode::Implicit },
        { 201, "CMP", instruction::addressing_mode::Immediate },
        { 202, "DEX", instruction::addressing_mode::Implicit },
        { 203, "SBX", instruction::addressing_mode::Immediate },
        { 204, "CPY", instruction::addressing_mode::Absolute },
        { 205, "CMP", instruction::addressing_mode::Absolute },
        { 206, "DEC", instruction::addressing_mode::Absolute },
        { 207, "DCP", instruction::addressing_mode::Absolute },
        { 208, "BNE", instruction::addressing_mode::Relative },
        { 209, "CMP", instruction::addressing_mode::IndirectY },
        { 210, "JAM", instruction::addressing_mode::Implicit },
        { 211, "DCP", instruction::addressing_mode::IndirectY },
        { 212, "NOP", instruction::addressing_mode::ZeroPageX },
        { 213, "CMP", instruction::addressing_mode::ZeroPageX },
        { 214, "DEC", instruction::addressing_mode::ZeroPageX },
        { 215, "DCP", instruction::addressing_mode::ZeroPageX },
        { 216, "CLD", instruction::addressing_mode::Implicit },
        { 217, "CMP", instruction::addressing_mode::AbsoluteY },
        { 218, "NOP", instruction::addressing_mode::Implicit },
        { 219, "DCP", instruction::addressing_mode::AbsoluteY },
        { 220, "NOP", instruction::addressing_mode::AbsoluteX },
        { 221, "CMP", instruction::addressing_mode::AbsoluteX },
        { 222, "DEC", instruction::addressing_mode::AbsoluteX },
        { 223, "DCP", instruction::addressing_mode::AbsoluteX },
        { 224, "CPX", instruction::addressing_mode::Immediate },
        { 225, "SBC", instruction::addressing_mode::IndirectX },
        { 226, "NOP", instruction::addressing_mode::Immediate },
        { 227, "ISC", instruction::addressing_mode::IndirectX },
        { 228, "CPX", instruction::addressing_mode::ZeroPage },
        { 229, "SBC", instruction::addressing_mode::ZeroPage },
        { 230, "INC", instruction::addressing_mode::ZeroPage },
        { 231, "ISC", instruction::addressing_mode::ZeroPage },
        { 232, "INX", instruction::addressing_mode::Implicit },
        { 233, "SBC", instruction::addressing_mode::Immediate },
        { 234, "NOP", instruction::addressing_mode::Implicit },
        { 235, "USBC", instruction::addressing_mode::Immediate },
        { 236, "CPX", instruction::addressing_mode::Absolute },
        { 237, "SBC", instruction::addressing_mode::Absolute },
        { 238, "INC", instruction::addressing_mode::Absolute },
        { 239, "ISC", instruction::addressing_mode::Absolute },
        { 240, "BEQ", instruction::addressing_mode::Relative },
        { 241, "SBC", instruction::addressing_mode::IndirectY },
        { 242, "JAM", instruction::addressing_mode::Implicit },
        { 243, "ISC", instruction::addressing_mode::IndirectY },
        { 244, "NOP", instruction::addressing_mode::ZeroPageX },
        { 245, "SBC", instruction::addressing_mode::ZeroPageX },
        { 246, "INC", instruction::addressing_mode::ZeroPageX },
        { 247, "ISC", instruction::addressing_mode::ZeroPageX },
        { 248, "SED", instruction::addressing_mode::Implicit },
        { 249, "SBC", instruction::addressing_mode::AbsoluteY },
        { 250, "NOP", instruction::addressing_mode::Implicit },
        { 251, "ISC", instruction::addressing_mode::AbsoluteY },
        { 252, "NOP", instruction::addressing_mode::AbsoluteX },
        { 253, "SBC", instruction::addressing_mode::AbsoluteX },
        { 254, "INC", instruction::addressing_mode::AbsoluteX },
        { 255, "ISC", instruction::addressing_mode::AbsoluteX }
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

        address PC = 0x0000;
        byte A = 0x00;
        byte X = 0x00;
        byte Y = 0x00;
        byte S = 0xFF;
        union
        {
            byte value = 0;
            struct
            {
                byte C : 1;
                byte Z : 1;
                byte I : 1;
                byte b3 : 1;
                byte b4 : 1;
                byte b5 : 1;
                byte V : 1;
                byte N : 1;
            };
        } P;

        void push(byte value)
        {
            memory.write(S-- + 0x100, value);
        };

        void push(address value)
        {
            memory.write(S-- + 0x100, value.value >> 8);
            memory.write(S-- + 0x100, value.value & 0b1111'1111);
        };

        byte pull()
        {
            return memory.read(++S);
        };

        address pull_address()
        {
            return address{ memory.read(++S), memory.read(++S) };
        };

        byte& get_desired_byte(instruction::addressing_mode mode, std::pair<byte, byte>& operands)
        {
            using enum instruction::addressing_mode;
            switch (mode)
            {
            case Relative:
            case Immediate:
                return operands.first;
            case Implicit:
            case Accumulator:
                return A;
            case ZeroPage:
                return memory.read(operands.first);
            case ZeroPageX:
                return memory.read(operands.first + X);
            case ZeroPageY:
                return memory.read(operands.first + Y);
            case Absolute:
                return memory.read(address{ operands.first, operands.second });
            case AbsoluteX:
                return memory.read(address{ address{ operands.first, operands.second } + X });
            case AbsoluteY:
                return memory.read(address{ address{ operands.first, operands.second } + Y });
            case Indirect:
                return memory.read(address{ memory.read(address{ operands.first, operands.second }),
                                            memory.read(address{ operands.first, operands.second } + 1) });
            case IndirectX:
                return memory.read(address{ memory.read(operands.first + X), memory.read(operands.first + X + 1) });
            case IndirectY:
                return memory.read(address{ memory.read(operands.first), memory.read(operands.first + 1) } + Y);
            }
        };

        void handle_instruction(instruction inst)
        {
            std::pair<byte, byte> operands = {};
            byte bytes_consumed = 1;
            byte cycles_taken = 2;

            using enum instruction::addressing_mode;
            switch (inst.mode)
            {
            case Immediate:
            case ZeroPage:
            case ZeroPageX:
            case ZeroPageY:
            case Relative:
            case IndirectX:
            case IndirectY:
                operands.first = memory.read(PC.value + 1);
                bytes_consumed = 2;
                break;
            case Indirect:
            case Absolute:
            case AbsoluteX:
            case AbsoluteY:
                operands.first = memory.read(PC.value + 1);
                operands.second = memory.read(PC.value + 2);
                bytes_consumed = 3;
                break;
            default:
                break;
            }

            byte& operand = get_desired_byte(inst.mode, operands);

            switch (inst.value)
            {
            case 0x69:
            case 0x65:
            case 0x75:
            case 0x6D:
            case 0x7D:
            case 0x79:
            case 0x61:
            case 0x71: // ADC
            {
                word result = A + operand + P.C;
                P.V = bool((A ^ byte(result >> 1)) & (operand ^ byte(result >> 1)) & 0b0100'0000);
                P.C = bool(result & 0b1'0000'0000);
                A = result >> 1;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            }
            case 0xE9:
            case 0xE5:
            case 0xF5:
            case 0xED:
            case 0xFD:
            case 0xF9:
            case 0xE1:
            case 0xF1: // SBC
            {
                word result = A + ~operand + P.C;
                P.V = bool((A ^ byte(result >> 1)) & (operand ^ byte(result >> 1)) & 0b0100'0000);
                P.C = bool(result & 0b1'0000'0000);
                A = result >> 1;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            }
            case 0x29:
            case 0x25:
            case 0x35:
            case 0x2D:
            case 0x3D:
            case 0x39:
            case 0x21:
            case 0x31: // AND
                A &= operand;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0x09:
            case 0x05:
            case 0x15:
            case 0x0D:
            case 0x1D:
            case 0x19:
            case 0x01:
            case 0x11: // ORA
                A |= operand;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0x49:
            case 0x45:
            case 0x55:
            case 0x4D:
            case 0x5D:
            case 0x59:
            case 0x41:
            case 0x51: // EOR
                A ^= operand;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0x0A:
            case 0x06:
            case 0x16:
            case 0x0E:
            case 0x1E: // ASL
                P.C = bool(operand & 0b1000'0000);
                operand <<= 1;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            case 0x4A:
            case 0x46:
            case 0x56:
            case 0x4E:
            case 0x5E: // LSR
                P.C = bool(operand & 0b0000'0001);
                operand >>= 1;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            case 0x2A:
            case 0x26:
            case 0x36:
            case 0x2E:
            case 0x3E: // ROL
            {
                word result = operand << 1;
                result &= P.C;
                P.C = bool(result & 0b1'0000'0000);
                operand = result & 0b1111'1111;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            }
            case 0x6A:
            case 0x66:
            case 0x76:
            case 0x6E:
            case 0x7E: // ROR
            {
                word result = operand;
                result &= word(P.C) << 8;
                P.C = result & 0b0000'0001;
                operand = result >> 1;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            }
            case 0xA9:
            case 0xA5:
            case 0xB5:
            case 0xAD:
            case 0xBD:
            case 0xB9:
            case 0xA1:
            case 0xB1: // LDA
                A = operand;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0xA2:
            case 0xA6:
            case 0xB6:
            case 0xAE:
            case 0xBE: // LDX
                X = operand;
                P.N = bool(X & 0b1000'0000);
                P.Z = X == 0;
                break;
            case 0xA0:
            case 0xA4:
            case 0xB4:
            case 0xAC:
            case 0xBC: // LDY
                Y = operand;
                P.N = bool(Y & 0b1000'0000);
                P.Z = Y == 0;
                break;
            case 0x85:
            case 0x95:
            case 0x8D:
            case 0x9D:
            case 0x99:
            case 0x81:
            case 0x91: // STA
                operand = A;
                break;
            case 0x86:
            case 0x96:
            case 0x8E: // STX
                operand = X;
                break;
            case 0x84:
            case 0x94:
            case 0x8C: // STY
                operand = Y;
                break;
            case 0xC6:
            case 0xD6:
            case 0xCE:
            case 0xDE: // DEC
                --operand;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            case 0xCA: // DEX
                --X;
                P.N = bool(X & 0b1000'0000);
                P.Z = X == 0;
                break;
            case 0x88: // DEY
                --Y;
                P.N = bool(Y & 0b1000'0000);
                P.Z = Y == 0;
                break;
            case 0xE6:
            case 0xF6:
            case 0xEE:
            case 0xFE: // INC
                ++operand;
                P.N = bool(operand & 0b1000'0000);
                P.Z = operand == 0;
                break;
            case 0xE8: // INX
                ++X;
                P.N = bool(X & 0b1000'0000);
                P.Z = X == 0;
                break;
            case 0xC8: // INY
                ++Y;
                P.N = bool(Y & 0b1000'0000);
                P.Z = Y == 0;
                break;
            case 0xC9:
            case 0xC5:
            case 0xD5:
            case 0xCD:
            case 0xDD:
            case 0xD9:
            case 0xC1:
            case 0xD1: // CMP
                if (A < operand)
                {
                    P.N = bool((A - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 0;
                }
                else if (A > operand)
                {
                    P.N = bool((A - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 1;
                }
                else if (A == operand)
                {
                    P.N = 0;
                    P.Z = 1;
                    P.C = 1;
                }
                break;
            case 0xE0:
            case 0xE4:
            case 0xEC: // CPX
                if (X < operand)
                {
                    P.N = bool((X - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 0;
                }
                else if (X > operand)
                {
                    P.N = bool((X - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 1;
                }
                else if (X == operand)
                {
                    P.N = 0;
                    P.Z = 1;
                    P.C = 1;
                }
                break;
            case 0xC0:
            case 0xC4:
            case 0xCC: // CPY
                if (Y < operand)
                {
                    P.N = bool((Y - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 0;
                }
                else if (Y > operand)
                {
                    P.N = bool((Y - operand) & 0b1000'0000);
                    P.Z = 0;
                    P.C = 1;
                }
                else if (Y == operand)
                {
                    P.N = 0;
                    P.Z = 1;
                    P.C = 1;
                }
                break;
            case 0x90: // BCC
                if (P.C == 0)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0xB0: // BCS
                if (P.C == 1)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0xD0: // BNE
                if (P.Z == 0)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0xF0: // BEQ
                if (P.Z == 1)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0x10: // BPL
                if (P.N == 0)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0x30: // BMI
                if (P.N == 1)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0x50: // BVC
                if (P.V == 0)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0x70: // BVS
                if (P.V == 1)
                {
                    PC.value += std::bit_cast<int8_t, byte>(operand);
                }
                break;
            case 0x18: // CLC
                P.C = 0;
                break;
            case 0x38: // SEC
                P.C = 1;
                break;
            case 0xD8: // CLD
                P.b3 = 0;
                break;
            case 0xF8: // SED
                P.b3 = 1;
                break;
            case 0x58: // CLI
                P.I = 0;
                break;
            case 0x78: // SEI
                P.I = 1;
                break;
            case 0xB8: // CLV
                P.V = 0;
                break;
            case 0x24:
            case 0x2C: // BIT
                P.N = bool(operand & 0b1000'0000);
                P.V = bool(operand & 0b0100'0000);
                P.Z = (A & operand) == 0;
                break;
            case 0x00: // BRK
                P.I = 1;
                push(address{ PC + 2 });
                push(P.value);
                break;
            case 0x4C: // JMP absolute
                PC = address{ operands.first, operands.second };
                break;
            case 0x6C: // JMP indirect
                PC = address{ memory.read(address{ operands.first, operands.second }),
                              memory.read(address{ operands.first, operands.second } + 1) };
                break;
            case 0x20: // JSR
                push(address{ PC + 2 });
                PC = address{ operands.first, operands.second };
                break;
            case 0xEA: // NOP
                break;
            case 0x48: // PHA
                push(A);
                break;
            case 0x08: // PHP
                push(P.value);
                break;
            case 0x68: // PLA
                A = pull();
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0x28: // PLP
                P.value = pull();
                P.I = 0;
                break;
            case 0x40: // RTI
                P.value = pull();
                P.I = 0;
                PC = pull_address();
                break;
            case 0x60: // RTS
                PC = pull_address();
                break;
            case 0xAA: // TAX
                X = A;
                P.N = bool(X & 0b1000'0000);
                P.Z = X == 0;
                break;
            case 0xA8: // TAY
                Y = A;
                P.N = bool(Y & 0b1000'0000);
                P.Z = Y == 0;
                break;
            case 0x8A: // TXA
                A = X;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0x98: // TYA
                A = Y;
                P.N = bool(A & 0b1000'0000);
                P.Z = A == 0;
                break;
            case 0xBA: // TSX
                X = S;
                P.N = bool(X & 0b1000'0000);
                P.Z = X == 0;
                break;
            case 0x9A: // TXS
                S = X;
                break;
            default: // Later "illegal" opcodes.
                break;
            }


        };
    };
};