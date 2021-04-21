#include <libyardland/mmio/mmio-6551.hpp>

void MMIO_6551::access(uint32_t address, uint8_t* data, bool get)
{
    switch (address)
    {

    // RS1 RS0
    //  0   0
    //
    // Write: Transmit Data Register
    // Read: Receiver Data Register
    //
    case 0b00:
        if (get) {
            *data = input_fifo.pop();
        }
        else {
            output_fifo.push(*data);
        }
        break;
    
    default:
        break;
    }

    return;
}
