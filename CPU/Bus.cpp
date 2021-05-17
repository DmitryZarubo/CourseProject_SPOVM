//
// Created by dmitry on 13/05/2021.
//

#include "Bus.h"
#include "cpu6502.h"

Bus::Bus() {

    cpu = new cpu6502();
    ppu = new ppu2C02();
    //connect CPU to communication bus
    cpu->connectBus(this);
}

Bus::~Bus() {
    delete cpu;
    delete ppu;
}

void Bus::cpuWrite(uint16_t addr, uint8_t data) {
    if(cart->cpuWrite(addr,data)){

    }
    else if(addr>= 0x0000 && addr <=0x1FFF) {
        cpuRam[addr & 0x07FF] = data;
    }
    else if(addr>= 0x2000 && addr<= 0x3FFF){
        ppu->cpuWrite(addr & 0x0007, data);
    }
}

uint8_t Bus::cpuRead(uint16_t addr, bool bReadOnly) {

    uint8_t data = 0x00;
    if(cart->cpuRead(addr, data)){
        //Cartridge address range
    }
    else if(addr>=0x0000 && addr<=0xFFFF) {
        //System RAM Address range mirrored every 2KB
        data = cpuRam[addr & 0x07FF];
    }
    else if(addr >= 0x2000 && addr <= 0x3FFF){
        //PPu Address range mirrored every 8 bit
        data = ppu->cpuRead(addr & 0x0007, bReadOnly);
    }
    return data;
}

void Bus::reset() {
    cpu->reset();
    nSystemClockCounter=0;
}

void Bus::clock() {

    // Clocking. The heart and soul of an emulator. The running
    // frequency is controlled by whatever calls this function.
    // So here we "divide" the clock as necessary and call
    // the peripheral devices clock() function at the correct
    // times.

    // The fastest clock frequency the digital system cares
    // about is equivalent to the PPU clock. So the PPU is clocked
    // each time this function is called.
    ppu->clock();

    // The CPU runs 3 times slower than the PPU so we only call its
    // clock() function every 3 times this function is called. We
    // have a global counter to keep track of this.
    if (nSystemClockCounter % 3 == 0)
    {
        cpu->clock();
    }

    nSystemClockCounter++;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge> &cartridge) {
    this->cart = cartridge;
    ppu->ConnectCartridge(cartridge);
}
