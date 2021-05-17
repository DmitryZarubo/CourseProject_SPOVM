//
// Created by dmitry on 17/05/2021.
//

#include "Mapper.h"

Mapper::Mapper(uint8_t prgBanks, uint8_t chrBanks)
{
    nPRGBanks = prgBanks;
    nCHRBanks = chrBanks;
}


Mapper::~Mapper()
{
}