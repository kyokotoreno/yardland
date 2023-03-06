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

#define MEMORY_BUFFER_SIZE 65536

//typedef void (*MemoryAccessFunc)(uint32_t, uint8_t*, bool);

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
 * @brief Memory Bank Class.
 * @version v0.1.0
 */
class Memory :
    public wdc816
{
public:
    /**
     * @brief Construct a new `Memory` object.
     *
     */
    Memory();

    /**
     * @brief Get an element from this memory bank.
     *
     * @param address The address of the element.
     * @return The element.
     */
	uint8_t get(uint32_t address);

    /**
     * @brief Puts an element onto this memory bank.
     *
     * @param address The destination address of the element.
     * @param data The element.
     */
	void put(uint32_t address, uint8_t data);

    /**
     * @brief Provides access to both 'get' and 'put' functions of this memory bank (used to chain memory banks).
     *
     * @param address The destination/source address of the element.
     * @param data The element.
     * @param get Calls `Memory::get()` if True, if False calls `Memory::put()`
     */
    void access(uint32_t address, uint8_t *data, bool get);

    /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     *
     * @param address address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	size_t addPort(Port port);

    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     *
     * @param id The integer returned from `Memory::addPort()`
     */
    void removePort(size_t id);

        /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     *
     * @param region address for the Memory of the device.
     * @return An integer used to identify the MMIOD.
     */
	size_t addRegion(Region region);

    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     *
     * @param id The integer returned from `Memory::addRegion()`
     */
    void removeRegion(size_t id);

    void populate(uint8_t *src, size_t size);

    //==============================================================================

    // The mem816 class defines a set of standard methods for defining and accessing
    // the emulated memory area.

    // Define the memory areas and sizes
	static void setMemory(Memory *memory);

	// Fetch a byte from memory (Modified to forward accesses to yardland's memory interface).
	INLINE static Byte getByte(Addr ea)
	{
        return pMemory->get(ea);
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
	INLINE static void setByte(Addr ea, Byte data)
	{
		pMemory->put(ea, data);
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
	uint8_t *pMemoryBuffer;

    static Memory *pMemory;

    /** @brief Ports.
     */
    std::vector<Port> mPorts;

    /** @brief Regions.
     */
    std::vector<Region> mRegions;
};
