#pragma once

#include <string>
#include <filesystem>
#include <fstream>
#include <cstdint>
#include <boost/log/trivial.hpp>
#include <boost/format.hpp>
#include <memory.hpp>

class BinaryFile
{
public:
    BinaryFile(std::string filename);
    ~BinaryFile();
    uint8_t* getBuffer() { return mpBuffer; }
    size_t getSize() { return mSize; }

private:
    uint8_t *mpBuffer;
    size_t mSize = 0;
};
