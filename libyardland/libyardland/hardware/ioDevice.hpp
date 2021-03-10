#pragma once

#include <cstdint>

namespace libyardland
{
    /**
     * \brief An I/O device retrieved from the interface/wrapper program.
     * 
     * \warning Shouldn't be instantiated from inside the library.
     * \author  Joseph Hans Diaz <josephhansdiaz30@gmail.com>
     * \version v1.0.0-alpha.1
     * \since   v1.0.0-alpha.1
     */
    class ioDevice
    {
    public:
        /**
         * \brief Puts a character into the device buffer.
         * \details Puts an 8-bit character (a byte) into the device buffer.
         * TODO: Add a 16-bit variant of this function.
         * 
         * \param[in]  data The character to put into the buffer.
         */ 
        virtual void put(uint8_t* data);

        /**
         * \brief Retrieves a character into the device buffer.
         * \details Retrieves an 8-bit character (a byte) into the device buffer.
         * TODO: Add a 16-bit variant of this function.
         * 
         * \param[out] data The character retrieved from the buffer.
         */ 
        virtual void get(uint8_t* data);

        /**
         * \brief Gets the size of the device buffer.
         * 
         * 
         * TODO: Add a 16-bit variant of this function.
         * 
         * \param[out] data The character retrieved from the buffer.
         */ 
        virtual int getBufferSize();

    protected:
        /**
         * \brief The data buffer of the device.
         */
        uint8_t* buffer;
    };
}
