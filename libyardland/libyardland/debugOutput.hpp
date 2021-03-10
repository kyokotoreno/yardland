#pragma once

#include <string>

namespace yardland
{
    /**
     * \brief Debugging Output Class
     * \details A Debugging Output Class that supports arbitrary placement of text in the terminal window, among other features.
     * 
     * \author  Joseph Hans Diaz <josephhansdiaz30 @ gmail.com>
     * \version v1.0.0-alpha.1
     * \since   v1.0.0-alpha.1
     */
    class debugOutput
    {
    public:
        /**
         * \brief Stop the execution of the emulator and print an error message.
         * \details Stops the execution of the emulator and prints an error message alongside an associated error code.
         * \param[in] message The error message to display.
         * \param[in] code    The error code associated with the message.
         */
        virtual void die(std::string message, int code);

        /**
         * \brief Print a logging message.
         * 
         * \param[in] message The message to log.
         */
        virtual void log(std::string message);

        /**
         * \brief Put a message at an arbitrary point in the terminal.
         * 
         * \param[in] message The message to display.
         * \param[in] x       The x coordinate of the point in the terminal where the message should be displayed.
         * \param[in] y       The y coordinate of the point in the terminal where the message should be displayed.
         */
        virtual void put(std::string message, int x, int y);
    };
}
