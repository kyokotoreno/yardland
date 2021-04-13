#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>

class binary_file
{
public:
    binary_file();
    ~binary_file();

    int load(std::string filename);
    void save();

    std::uint8_t * get_binbuffer_ptr();

    std::uint32_t get_cload_address();
    std::uint32_t get_dload_address();

    std::uint16_t get_cbin_size();
    std::uint16_t get_dbin_size();

    void set_cbin_size(std::uint16_t cbin_size);
    void set_dbin_size(std::uint16_t dbin_size);

private:
    std::string filename;

    std::fstream filehandle;

    std::uint8_t * binbuffer;

    std::uint32_t cload_address;
    std::uint32_t dload_address;

    std::uint16_t cbin_size;
    std::uint16_t dbin_size;
};
