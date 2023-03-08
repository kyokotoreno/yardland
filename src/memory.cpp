#include <memory.hpp>

uint8_t *Memory::pMemoryBuffer = new uint8_t[MEMORY_BUFFER_SIZE];
std::vector<Port> *Memory::mPorts = new std::vector<Port>;
std::vector<Region> *Memory::mRegions = new std::vector<Region>;

size_t Memory::addPort(Port port) {
    Memory::mPorts->push_back(port);
    return Memory::mPorts->size() - 1;
}

void Memory::removePort(size_t id) {
    Memory::mPorts->erase(Memory::mPorts->begin() + id);
}

size_t Memory::addRegion(Region region) {
    Memory::mRegions->push_back(region);
    return Memory::mRegions->size() - 1;
}

void Memory::removeRegion(size_t id) {
    Memory::mRegions->erase(Memory::mRegions->begin() + id);
}

void Memory::populate(uint8_t *src, size_t size) {
    memcpy(Memory::pMemoryBuffer, src, size);
}
