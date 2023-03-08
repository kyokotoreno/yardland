/**
 * @file memory.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @date 2021-03-27
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <wdc816.hpp>

#define MEMORY_BUFFER_SIZE 65536*256

/**
 * @brief A port.
 *
 */
struct Port
{
    uint32_t address;
    void (*access_func)(uint32_t, uint8_t*, bool);
};

/**
 * @brief A region.
 *
 */
struct Region
{
    uint32_t start_address;
    uint32_t end_address;
    void (*access_func)(uint32_t, uint8_t*, bool);
};

/**
 * @brief Memory Class.
 * @version v0.1.0
 */
class Memory :
    public wdc816
{
public:
    /**
     * @brief Adds a Memory Mapped IO Device to memory.
     *
     * @param address address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	static size_t addPort(Port port);

    /**
     * @brief Removes a Memory Mapped IO Device from memory.
     *
     * @param id The integer returned from `Memory::addPort()`
     */
    static void removePort(size_t id);

        /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     *
     * @param region address for the Memory of the device.
     * @return An integer used to identify the MMIOD.
     */
	static size_t addRegion(Region region);

    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     *
     * @param id The integer returned from `Memory::addRegion()`
     */
    static void removeRegion(size_t id);

    static void populate(uint8_t *src, size_t size);

	// Fetch a byte from memory (Modified to forward accesses to yardland's memory interface).
	static Byte getByte(Addr ea)
	{
        for(size_t i = 0; i < mPorts.size(); i++) {
            if(ea == mPorts.at(i).address) {
                uint8_t data = 0;
                mPorts.at(i).access_func(ea, &data, true);
                return data;
            }
        }

        for(size_t i = 0; i < mRegions.size(); i++) {
            Region region = mRegions.at(i);
            if(ea >= region.start_address && ea <= region.end_address) {
                uint8_t data = 0;
                region.access_func(ea, &data, true);
                return data;
            }
        }

        return pMemoryBuffer[ea];
	}
	// Fetch a word from memory
	INLINE static Word getWord(Addr ea)
	{
        return (join(getByte(ea + 0), getByte(ea + 1)));
	}
	// Fetch a long address from memory
	INLINE static Addr getAddr(Addr ea)
	{
		return (join(getByte(ea + 2), getWord(ea + 0)));
	}
	// Write a byte to memory (Modified to forward accesses to yardland's memory interface).
	static void setByte(Addr ea, Byte data)
	{
        for(size_t i = 0; i < Memory::mPorts.size(); i++) {
            Port port = Memory::mPorts.at(i);
            if(ea == port.address) {
                port.access_func(ea, &data, false);
                return;
            }
        }
        for(size_t i = 0; i < Memory::mRegions.size(); i++) {
            Region region = Memory::mRegions.at(i);
            if(ea >= region.start_address && ea <= region.end_address) {
                region.access_func(ea, &data, false);
                return;
            }
        }

        pMemoryBuffer[ea] = data;
	}
	// Write a word to memory
	INLINE static void setWord(Addr ea, Word data)
	{
		setByte(ea + 0, lo(data));
		setByte(ea + 1, hi(data));
	}

private:
    /** @brief Memory Buffer.
     */
	static uint8_t *pMemoryBuffer;
    /** @brief Ports.
     */
    static std::vector<Port> mPorts;
    /** @brief Regions.
     */
    static std::vector<Region> mRegions;
};
