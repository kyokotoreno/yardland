#include <devices/nvram.hpp>

uint8_t *NVRam::pNVRamBuffer;

NVRam::NVRam() {
    NVRam::pNVRamBuffer = new uint8_t[256];
}

Region NVRam::getRegion()
{
    return {
        0xef00,
        0xefff,
        nullptr
    };
}
