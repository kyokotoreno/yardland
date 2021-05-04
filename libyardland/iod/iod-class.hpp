/**
 * @file iod-class.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @date 2021-03-28
 */

#pragma once

#include <cstdint>

/**
 * @brief Input Output device parent class.
 *
 * An I/O device retrieved from the interface/wrapper program.
 *
 * @version v0.1.0
 */
class IODClass
{
public:
    /**
     * @brief Puts a character into the device buffer.
     * @details Puts an 8-bit character (a byte) into the device buffer.
     * @todo Add a 16-bit variant of this function.
     *
     * @param[in] data The character to put into the buffer.
     */
    virtual void put(uint8_t* data) { return; } // TODO: Add a 16-bit variant of this function.

    /**
     * @brief Retrieves a character from the device buffer.
     * @details Retrieves an 8-bit character (a byte) from the device buffer.
     * @todo Add a 16-bit variant of this function.
     *
     * @param[out] data The character retrieved from the buffer.
     */
    virtual void get(uint8_t* data) { return; } // TODO: Add a 16-bit variant of this function.

    /**
     * @brief Gets the size of the device buffer.
     *
     *  @return This device's buffer size.
     */
    virtual int GetBufferSize() { return 0; }

protected:
    /**
     * @brief The data buffer of the device.
     */
    uint8_t* buffer;
};
