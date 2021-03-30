/**
 * @file cpu-65816.hpp
 * @author Joseph Hans Diaz Gonzalez <eliotvonecklie@gmail.com>
 * @brief 
 * @version 0.1.0
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <cstdint>

#include <libyardland/utils/buffers/filo.hpp>

class cpu_65816
{
	public:
		cpu_65816();

		int OnUpdate();

		uint16_t PCL;
		uint8_t  PBR, DBR;
		uint8_t  AL, AH;
		uint8_t  XL, XH;
		uint8_t  YL, YH;
		uint16_t KL, KH;
		uint16_t D;
		uint8_t  SL, SH;

		filo_buffer stack;
};
