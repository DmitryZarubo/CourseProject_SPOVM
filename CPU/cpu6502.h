//
// Created by dmitry on 13/05/2021.
//
#pragma once
#ifndef NES_EMULATOR_CPU6502_H
#define NES_EMULATOR_CPU6502_H

#include <cstdint>

#include <iostream>
#include <string>
#include <vector>
#include "Bus.h"
#include <map>
class Bus;

class cpu6502 {
public:
    enum FLAGS6502{
        C = (1<<0), //carry bit
        Z = (1<<1), //zero bit
        I = (1<<2), // Disable interrupts
        D = (1<<3), // Decimal Mode
        B = (1<<4), // Break
        U = (1<<5), // Unused
        V = (1<<6), // Overflow
        N = (1<<7), // Negative
    };
    uint8_t a = 0x00; // accumulator register
    uint8_t x = 0x00; //  X indexing register
    uint8_t y = 0x00; //  Y indexing register
    uint8_t stkp = 0x00; // Stack Pointer register
    uint16_t pc = 0x0000; // Program Counter
    uint8_t status = 0x00; // Status Register
public:
    cpu6502();
    ~cpu6502();

    void connectBus(Bus* n){bus = n;}

private:

    // Addressing modes
    uint8_t IMP();
    uint8_t IMM(); //immediate
    uint8_t ZP0(); //
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t REL();
    uint8_t ABS(); // absolute addressing
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IND();
    uint8_t IZX();
    uint8_t IZY();

private:
    // Opcode functions
    // These functions return 0 normally, but some are capable of
    // requiring more clock cycles when executed under certain
    // conditions combined with certain addressing modes. If that is
    // the case, they return 1.
    //
    // I have included detailed explanations of each function in
    // the class implementation file. Note they are listed in
    // alphabetical order here for ease of finding.

    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
    uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
    uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
    uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
    uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
    uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
    uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
    uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
    uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
    uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
    uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
    uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
    uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
    uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();

    // I capture all "unofficial" opcodes with this function. It is
    // functionally identical to a NOP
    uint8_t XXX();

public:
//external events functions
    void clock();
    void reset();
    void irq(); //interrupt request signal
    void nmi(); //non-maskable interrupt request signal



private:
    uint8_t  fetch();
    uint8_t fetched = 0x00; // Represents the working input value to ALU

    uint16_t temp = 0x0000; // convenience variable, uses everywhere
    uint16_t addr_abs = 0x0000; //all used memory addresses end up here
    uint16_t addr_rel = 0x0000; // Represents absolute address following a branch
    uint8_t opcode = 0x00;      //it's an instruction byte of opcode we are working with
    uint8_t cycles = 0;      //count of cycles to perform for current instruction
    uint32_t clock_count = 0;	   // A global accumulation of the number of clocks


private:
    Bus* bus = nullptr;
    uint8_t read(uint16_t a);
    void write(uint16_t a, uint8_t d);

    //Convenience functions to access status register
    uint8_t GetFlag(FLAGS6502 flags);
    void    SetFlag(FLAGS6502 flags, bool value);

    struct INSTRUCTIONS{ //struct representating instructions for disassembler
        std::string name;
        uint8_t(cpu6502::*operate)(void) = nullptr;
        uint8_t(cpu6502::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;
    };

    std::vector<INSTRUCTIONS> lookup;
public:
    // Indicates the current instruction has completed by returning true. This is
    // a utility function to enable "step-by-step" execution, without manually
    // clocking every cycle
    bool complete();
    // Produces a map of strings, with keys equivalent to instruction start locations
    // in memory, for the specified address range
    std::map<uint16_t, std::string> disassemble(uint16_t nStart, uint16_t nStop);


};


#endif //NES_EMULATOR_CPU6502_H
