/**
 * @file mmio-6551.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief 
 * @version 0.1.0
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cstdint>
#include <cstdlib>

#include <libyardland/mmio/mmio-class.hpp>
#include <libyardland/utils/buffers/fifo.hpp>

class MMIO_6551 : MMIOClass
{
public:

    void access(std::uint32_t address, std::uint8_t* data, bool get);

    fifo_buffer input_fifo, output_fifo;
};
