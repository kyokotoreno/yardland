#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <boost/log/trivial.hpp>

class BinaryFile
{
public:
    BinaryFile(std::string filename);
    ~BinaryFile();
    int load();
    void save();
    uint8_t* getTextBuffer();
    uint8_t* getDataBuffer();
    uint32_t getTextOffset();
    uint32_t getDataOffset();
    uint16_t getTextSize();
    uint16_t getDataSize();
    void setTextSize(uint16_t text_size);
    void setDataSize(uint16_t data_size);

private:
    std::string filename;
    std::fstream filehandle;
    uint8_t *mpTextBuffer = 0, *mpDataBuffer = 0;
    uint32_t mTextOffset = 0, mDataOffset = 0;
    uint16_t mTextSize = 0, mDataSize = 0;
};
