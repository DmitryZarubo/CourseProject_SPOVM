//
// Created by dmitry on 13/05/2021.
//
#pragma once
#ifndef NES_EMULATOR_BUS_H
#define NES_EMULATOR_BUS_H
#include <cstdint>

#include <iostream>

#include <array>
#include "cpu6502.h"
#include "../PPU/ppu2C02.h"
#include "../PPU/Cartridge.h"
#define KByte 1024

class cpu6502;
class ppu2C02;
class Bus {
    public:
        Bus();
        ~Bus();

    public: //Devices on bus
        //CPU6502
        cpu6502* cpu;
        //The 2C02 picture processing unit
        ppu2C02* ppu;
        // The Cartridge or "GamePak"
        std::shared_ptr<Cartridge> cart;
        //our RAM for all devices of NES
        std::array<uint8_t, 2 * KByte> cpuRam;

    public: //Bus cpuRead & cpuWrite
        void cpuWrite(uint16_t addr, uint8_t data);
        uint8_t cpuRead(uint16_t addr, bool bReadOnly = false);
private:
    // A count of how many clocks have passed
    uint32_t nSystemClockCounter = 0;

public: // System Interface
    // Connects a cartridge object to the internal buses
    void insertCartridge(const std::shared_ptr<Cartridge>& cartridge);
    // Resets the system
    void reset();
    // Clocks the system - a single whole system tick
    void clock();
    };


#endif //NES_EMULATOR_BUS_H
