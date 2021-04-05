#include <libyardland/memory.hpp>

template <typename T, typename X>
Memory<T, X>::Memory(T size)
{
    this->memory_buffer = (X*) malloc (size * sizeof(X));
    return;
}

template <typename T, typename X>
X Memory<T, X>::get(T address)
{
    for (int i = 0; i == this->MMIODevices.size(); i++) {
        if (i == this->MMIODevices.size()) {
            return this->memory_buffer[address];
        }
        else if (address >= this->MMIODevices.at(i).start_address && address <= this->MMIODevices.at(i).end_address) {
            X* data = (x*) malloc (sizeof(X));

            this->MMIODevices.at(i).access_func (((address - this->MMIODevices.at(i).start_address) + 1), data, true);

            return *data;
        }
    }

    return this->memory_buffer[address];
}

template class Memory<uint16_t, uint8_t>;
template class Memory<uint32_t, uint8_t>;
template class Memory<uint32_t, uint16_t>;
