#pragma once

#include <string>
#include <cstdint>

#include <libyardland/cpu/cpu-addressing-mode.hpp>
#include <libyardland/cpu/cpu-registers.hpp>
#include <libyardland/cpu/cpu-alu.hpp>
#include <libyardland/memory.hpp>

class CpuOperation
{
public:
    std::string name;
    void perform(CpuAlu *a, CpuRegisters *r, Memory<std::uint32_t, std::uint8_t> *m, uint8_t *v, uint8_t *rv);
};
