/**
 * @file memory.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief Memory Banks template class
 * @version 0.3.0-alpha.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstdint>
#include <cstdlib>
#include <vector>

/**
 * @brief Memory Bank Class
 */
class Memory
{
public:
    /**
     * @brief Get an 'X' element from this memory bank.
     * 
     * @param address The address of the element.
     * @return The element.
     */
	static std::uint8_t get(std::uint32_t address);

    /**
     * @brief Puts and 'X' element onto this memory bank.
     * 
     * @param address The destination address of the element.
     * @param data The element.
     */
	static void put(std::uint32_t address, std::uint8_t data);

    /**
     * @brief Provides access to both 'get' and 'put' functions of this memory bank (used to chain memory banks).
     * 
     * @param address The destination/source address of the element.
     * @param data The element.
     * @param get Calls 'get' if True, if False calls 
     */
    static void access(std::uint32_t address, std::uint8_t* data, bool get);

    /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     * 
     * @param start_address Start address for the Memory of the device.
     * @param end_address End address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	static int AddMMIOD(std::uint32_t start_address, std::uint32_t end_address, void ( *access_func ) (std::uint32_t, std::uint8_t*, bool));
    
    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     * 
     * @param id The integer returned from AddMMIOD()
     */
    static void RemoveMMIOD(int id);

private:
	std::uint8_t* memory_buffer;

    struct MMIODevice
    {
        std::uint32_t start_address;
        std::uint32_t end_address;
        void ( *access_func ) (std::uint32_t, std::uint8_t*, bool);
    };

    std::vector<MMIODevice> MMIODevices;
};
