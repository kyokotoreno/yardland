/**
 * @file mmio-6551.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @date 2021-03-28
 */

#include <cstdint>
#include <cstdlib>

#include <libyardland/mmio/mmio-class.hpp>
#include <libyardland/utils/buffers/fifo.hpp>

/**
 * @brief MOS 6551 ACIA Class.
 * @version v0.1.0
 */
class MMIO_6551 : MMIOClass
{
public:

    void access(std::uint32_t address, std::uint8_t* data, bool get);

    fifo_buffer input_fifo, output_fifo;
};
