#include <memory.hpp>

Memory::Memory() : mpMemoryBuffer((uint8_t*)malloc(65536 * sizeof(uint8_t))) {}

uint8_t Memory::get(uint16_t address) {
    for (size_t i = 0; i < mPorts.size(); i++) {
        if (address == mPorts.at(i).address) {
            uint8_t data = 0;
            mPorts.at(i).access_func(address, &data, true);
            return data;
        }
    }

    return mpMemoryBuffer[address];
}

void Memory::put(uint16_t address, uint8_t data) {
    for (size_t i = 0; i < mPorts.size(); i++) {
        if (address == mPorts.at(i).address) {
            mPorts.at(i).access_func(address, &data, false);
            return;
        }
    }

    mpMemoryBuffer[address] = data;
}

size_t Memory::addPort(uint16_t address, void (*access_func)(uint16_t, uint8_t *, bool)) {
    Port port = {address, access_func};
    mPorts.push_back(port);
    return mPorts.size() - 1;
}

void Memory::removePort(size_t id) {
    mPorts.erase(mPorts.begin() + id);
}

void Memory::populate(uint8_t *src, size_t size)
{
    memcpy(mpMemoryBuffer, src, size);
}
