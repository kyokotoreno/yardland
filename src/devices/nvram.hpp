#pragma once

#include <cstdint>
#include <cstdlib>
#include <memory.hpp>

class NVRam
{
private:
    static uint8_t *pNVRamBuffer;
public:
    NVRam();
    ~NVRam() {}

    static Region getRegion();
};
