/**
 * @file fifo.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief 
 * @version v0.3.0-alpha.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstdint>
#include <cstdlib>

/**
 * @brief 
 * 
 */
class fifo_buffer
{
public:
    /**
     * @brief Construct a new fifo buffer object.
     * 
     */
    fifo_buffer(int size = 256);

    /**
     * @brief 
     * 
     * @return uint8_t 
     */
    std::uint8_t pop();
    /**
     * @brief 
     * 
     * @param data 
     */
    void push(std::uint8_t data);
private:
    /**
     * @brief Buffer.
     * 
     */
    std::uint8_t* buf;
    /**
     * @brief Head Pointer.
     * 
     */
    int head;
    /**
     * @brief Tail Pointer.
     * 
     */
    int tail;
    /**
     * @brief Size of the buffer.
     * 
     */
    int size;
};
