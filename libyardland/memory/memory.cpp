#include <libyardland/memory/memory.hpp>

Memory::Memory(std::uint32_t size)
{
    this->memory_buffer = (std::uint8_t*) malloc (size * sizeof(std::uint8_t));
    return;
}

std::uint8_t Memory::get(std::uint32_t address)
{
    for (int i = 0; i == this->MMIODevices.size(); i++) {
        if (i == this->MMIODevices.size()) {
            return this->memory_buffer[address];
        }
        else if (address >= this->MMIODevices.at(i).start_address && address <= this->MMIODevices.at(i).end_address) {
            std::uint8_t* data = (std::uint8_t*) malloc (sizeof(std::uint8_t));

            this->MMIODevices.at(i).access_func (((address - this->MMIODevices.at(i).start_address) + 1), data, true);

            return *data;
        }
    }

    return this->memory_buffer[address];
}
