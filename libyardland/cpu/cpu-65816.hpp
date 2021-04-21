/**
 * @file cpu-65816.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief 65816 Virtual Processor Class.
 * @version v0.3.0
 * @since v0.1.0
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <iostream>
#include <cstdint>

// #include <libyardland/utils/buffers/filo.hpp>

/**
 * @brief 65816 Virtual Processor Class.
 * @version v0.3.0
 * @since v0.1.0
 */
class cpu_65816
{
public:
    cpu_65816();

    void Step();

    std::uint16_t PCL;
    std::uint8_t  PBR, DBR;
    std::uint8_t  AL, AH;
    std::uint8_t  XL, XH;
    std::uint8_t  YL, YH;
    std::uint16_t KL, KH;
    std::uint16_t D;
    std::uint8_t  SL, SH;

    //filo_buffer stack;
};
