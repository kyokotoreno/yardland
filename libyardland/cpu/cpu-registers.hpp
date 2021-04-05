#pragma once

#include <string>
#include <cstdint>

class CpuRegisters
{
public:
    void setRegister(int r, std::uint8_t *v);
    void setFlagsBasedOn(std::uint8_t *v);
};
