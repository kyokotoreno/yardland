#include <binary-file.hpp>

BinaryFile::BinaryFile(std::string filename): filename(filename) {}

BinaryFile::~BinaryFile()
{
    delete mpTextBuffer;
    delete mpDataBuffer;
}

int BinaryFile::load()
{
    BOOST_LOG_TRIVIAL(info) << "Loading binary file: \"" << filename << "\".";

    filehandle.open(filename, std::fstream::in | std::fstream::binary);

    std::filebuf* pbuf = filehandle.rdbuf();

    // Try to read string "YARDLANDBIN" from the start of the file.
    std::string magic_string;

    for (int i = 0; i < 11 && pbuf->sgetc() != EOF; i++) {
        magic_string.push_back(pbuf->sbumpc());
    }

    if (magic_string != "YARDLANDBIN") {
        BOOST_LOG_TRIVIAL(error) << "Couldn't read binary file, magic string not found.";
        return 1;
    }
    
    BOOST_LOG_TRIVIAL(trace) << "Binary file passed magic string validation.";

    // Currently at Offset 11 (0xB), read data offset (uint32_t, 4 bytes, big endian).
    mTextOffset  = pbuf->sbumpc() << 24;
    mTextOffset += pbuf->sbumpc() << 16;
    mTextOffset += pbuf->sbumpc() <<  8;
    mTextOffset += pbuf->sbumpc();

    // Currently at Offset 15 (0xF), read data segment size (uint16_t, 2 bytes, big endian).
    mTextSize  = pbuf->sbumpc() <<  8;
    mTextSize += pbuf->sbumpc();

    // Currently at Offset 17 (0x11), read text offset (uint32_t, 4 bytes, big endian).
    mDataOffset  = pbuf->sbumpc() << 24;
    mDataOffset += pbuf->sbumpc() << 16;
    mDataOffset += pbuf->sbumpc() <<  8;
    mDataOffset += pbuf->sbumpc();

    // Currently at Offset 21 (0x15), read text segment size (uint16_t, 2 bytes, big endian).
    this->mDataSize  = pbuf->sbumpc() <<  8;
    this->mDataSize += pbuf->sbumpc();

    BOOST_LOG_TRIVIAL(trace) << "Binary File Metadata\n" 
        << "Text Segment Offset: " << mTextOffset << ", Text Segment Size: " << mTextSize << "\n"
        << "Data Segment Offset: " << mDataOffset << ", Data Segment Size: " << mDataSize;

    // Currently at Offset 23 (0x17), read code segment.
    for (int i = 0; i < this->mTextSize && pbuf->sgetc() != EOF; i++) {
        pbuf->sbumpc();

    }

    if (pbuf->sgetc() == EOF) {
        BOOST_LOG_TRIVIAL(error) << "Couldn't read binary file, reached EOF too soon.";
        return 1;
    }

    return 0;
}

uint8_t *BinaryFile::getTextBuffer()
{
    return mpTextBuffer;
}

uint8_t *BinaryFile::getDataBuffer()
{
    return mpDataBuffer;
}

std::uint32_t BinaryFile::getTextOffset()
{
    return mTextOffset;
}

std::uint32_t BinaryFile::getDataOffset()
{
    return mDataOffset;
}

std::uint16_t BinaryFile::getTextSize()
{
    return mTextSize;
}

std::uint16_t BinaryFile::getDataSize()
{
    return mDataSize;
}
