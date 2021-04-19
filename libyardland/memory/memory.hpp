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
 * 
 * @tparam T Address Type
 * @tparam X Data Type
 */
template <typename T, typename X>
class Memory
{
public:
    /**
     * @brief Construct a new memory object
     * 
     * @param size The size of this memory bank (Number of X elements of the memory bank).
     */
	Memory(T size);

    /**
     * @brief Get an 'X' element from this memory bank.
     * 
     * @param address The address of the element.
     * @return The element.
     */
	X get(T address);
    /**
     * @brief Puts and 'X' element onto this memory bank.
     * 
     * @param address The destination address of the element.
     * @param data The element.
     */
	void put(T address, X data);

    /**
     * @brief Provides access to both 'get' and 'put' functions of this memory bank (used to chain memory banks).
     * 
     * @param address The destination/source address of the element.
     * @param data The element.
     * @param get Calls 'get' if True, if False 
     */
    void access(T address, X* data, bool get);

    /**
     * @brief Adds a Memory Mapped IO Device to this memory bank.
     * 
     * @param start_address Start address for the Memory of the device.
     * @param end_address End address for the Memory of the device.
     * @param access_func Access funtion of the MMIOD.
     * @return An integer used to identify the MMIOD.
     */
	int AddMMIOD(T start_address, T end_address, void ( *access_func ) (T, X*, bool));
    /**
     * @brief Removes a Memory Mapped IO Device from this memory bank.
     * 
     * @param id The integer returned from AddMMIOD()
     */
    void RemoveMMIOD(int id);

private:
	X* memory_buffer;

    struct MMIODevice
    {
        T start_address;
        T end_address;
        void ( *access_func ) (T, X*, bool);
    };

    std::vector<MMIODevice> MMIODevices;
};
