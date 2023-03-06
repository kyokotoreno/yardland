#include <memory.hpp>

Memory::Memory() : pMemoryBuffer((uint8_t*)malloc(65536 * sizeof(uint8_t))) {}

uint8_t Memory::get(uint32_t address) {
    for(size_t i = 0; i < mPorts.size(); i++) {
        if(address == mPorts.at(i).address) {
            uint8_t data = 0;
            mPorts.at(i).access_func(address, &data, true);
            return data;
        }
    }

    for(size_t i = 0; i < mRegions.size(); i++) {
        Region region = mRegions.at(i);
        if(address >= region.start_address && address <= region.end_address) {
            uint8_t data = 0;
            region.access_func(address, &data, true);
            return data;
        }
    }

    return pMemoryBuffer[address];
}

void Memory::put(uint32_t address, uint8_t data) {
    #ifdef LOG_TRACE
    BOOST_LOG_TRIVIAL(trace) << "Ports: " << mPorts.size() << ", Regions: " << mRegions.size();
    #endif
    for(size_t i = 0; i < mPorts.size(); i++) {
        Port port = mPorts.at(i);
        #ifdef LOG_TRACE
        BOOST_LOG_TRIVIAL(trace) << boost::format("Testing port %#d: %#x == %#x.") % i % port.address % address;
        #endif
        if(address == port.address) {
            //BOOST_LOG_TRIVIAL(trace) << "Port Match: " << i << ".";
            port.access_func(address, &data, false);
            return;
        }
    }

    for(size_t i = 0; i < mRegions.size(); i++) {
        Region region = mRegions.at(i);
        #ifdef LOG_TRACE
        BOOST_LOG_TRIVIAL(trace) << boost::format("Testing region %#d: %#x <= %#x <= %#x.") % i % region.start_address % address % region.end_address;
        #endif
        if(address >= region.start_address && address <= region.end_address) {
            #ifdef LOG_TRACE
            BOOST_LOG_TRIVIAL(trace) << "Region Match: " << i << ".";
            #endif
            region.access_func(address, &data, false);
            return;
        }
    }

    pMemoryBuffer[address] = data;
}

size_t Memory::addPort(Port port) {
    mPorts.push_back(port);
    return mPorts.size() - 1;
}

void Memory::removePort(size_t id) {
    mPorts.erase(mPorts.begin() + id);
}

size_t Memory::addRegion(Region region) {
    mRegions.push_back(region);
    return mRegions.size() - 1;
}

void Memory::removeRegion(size_t id) {
    mRegions.erase(mRegions.begin() + id);
}

void Memory::populate(uint8_t *src, size_t size) {
    memcpy(pMemoryBuffer, src, size);
}

//==============================================================================

Memory *Memory::pMemory;

void Memory::setMemory(Memory* memory) {
    Memory::pMemory = memory;
}
