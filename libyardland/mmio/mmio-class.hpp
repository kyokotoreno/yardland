/**
 * @file mmio-class.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief Memory Mapped IO Device Class.
 * @version v0.3.0
 * @since v0.3.0
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstdint>

/**
 * @brief Memory Mapped IO Device Class.
 * @version v0.3.0
 * @since v0.3.0
 */
class MMIOClass
{
public:
    /**
     * @brief Access this Device's registers.
     * 
     * @param address The address of the register.
     * @param data The data to put/get.
     * @param get Gets the data from the register if True, Puts data onto the register if False.
     */
    void access(uint32_t address, uint8_t* data, bool get);
};
