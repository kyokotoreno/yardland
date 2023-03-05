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

/**
 * @brief A port.
 *
 */
struct Port
{
    uint16_t address;
    void (*access_func)(uint16_t, uint8_t*, bool);
};

/**
 * @brief Memory Bank Class.
 * @version v0.1.0
 */
class Memory
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
	uint8_t get(uint16_t address);

    /**
     * @brief Puts an element onto this memory bank.
     *
     * @param address The destination address of the element.
     * @param data The element.
     */
	void put(uint16_t address, uint8_t data);

    /**
     * @brief Provides access to both 'get' and 'put' functions of this memory bank (used to chain memory banks).
     *
     * @param address The destination/source address of the element.
     * @param data The element.
     * @param get Calls `Memory::get()` if True, if False calls `Memory::put()`
     */
    void access(uint16_t address, uint8_t *data, bool get);

    /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     *
     * @param address address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	size_t addPort(uint16_t address, void (*access_func)(uint16_t, uint8_t*, bool));

    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     *
     * @param id The integer returned from `Memory::addPort()`
     */
    void removePort(size_t id);

    void populate(uint8_t *src, size_t size);

private:
    /**
     * @brief Memory Buffer.
     *
     */
	uint8_t *mpMemoryBuffer;

    /**
     * @brief Ports.
     *
     */
    std::vector<Port> mPorts;
};
