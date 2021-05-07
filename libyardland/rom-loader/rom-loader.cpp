#include <libyardland/binary-file/binary-file.hpp>

binary_file::binary_file()
{
    this->cload_address = 0;
    this->dload_address = 0;
    this->cbin_size = 0;
    this->dbin_size = 0;
    return;
}

binary_file::~binary_file()
{
    return;
}

int binary_file::load(std::string filename)
{
    std::cout << "[libyardland/binary-file/binary-file.hpp:19] INFO Loading binary file \"" << filename << "\"" << std::endl;

    this->filehandle.open(filename, std::fstream::in | std::fstream::out | std::fstream::binary);

    std::filebuf* pbuf = this->filehandle.rdbuf();

    std::uint8_t cur; // Current byte.

    // Try to read string "YARDLANDBIN" from the start of the file.
    std::string magic_string;
    for (int i = 0; i < 11 && pbuf->sgetc() != EOF; i++) {
        cur = pbuf->sbumpc();
        magic_string.push_back(cur);
    }

    if (magic_string != "YARDLANDBIN") {
        std::cout << "[libyardland/binary-file/binary-file.hpp:35] ERROR Invalid or corrupt binary file (couldn't find magic string)" << std::endl;
        return 1;
    }

    std::cout << "[libyardland/binary-file/binary-file.hpp:39] INFO Binary file passed magic string validation" << std::endl;

    // Currently at Offset 11 (0xB), read data load address (uint32_t, 4 bytes, big endian).
    this->dload_address  = static_cast<std::uint32_t>(pbuf->sbumpc()) << 24;
    this->dload_address += static_cast<std::uint32_t>(pbuf->sbumpc()) << 16;
    this->dload_address += static_cast<std::uint32_t>(pbuf->sbumpc()) <<  8;
    this->dload_address += static_cast<std::uint32_t>(pbuf->sbumpc());

    std::cout << std::showbase;
    std::cout << "[libyardland/binary-file/binary-file.hpp:48] INFO Binary File Metadata, Data Segment Load Address: " << std::hex << this->dload_address << std::endl;
    std::cout << std::noshowbase;

    // Currently at Offset 15 (0xF), read data segment size (uint16_t, 2 bytes, big endian).
    this->dbin_size  = static_cast<std::uint32_t>(pbuf->sbumpc()) <<  8;
    this->dbin_size += static_cast<std::uint32_t>(pbuf->sbumpc());

    std::cout << std::showbase;
    std::cout << "[libyardland/binary-file/binary-file.hpp:56] INFO Binary File Metadata, Data Segment Size: " << std::hex << this->dbin_size << std::endl;
    std::cout << std::noshowbase;

    // Currently at Offset 17 (0x11), read code load address (uint32_t, 4 bytes, big endian).
    this->cload_address  = static_cast<std::uint32_t>(pbuf->sbumpc()) << 24;
    this->cload_address += static_cast<std::uint32_t>(pbuf->sbumpc()) << 16;
    this->cload_address += static_cast<std::uint32_t>(pbuf->sbumpc()) <<  8;
    this->cload_address += static_cast<std::uint32_t>(pbuf->sbumpc());

    std::cout << std::showbase;
    std::cout << "[libyardland/binary-file/binary-file.hpp:66] INFO Binary File Metadata, Code Segment Load Address: " << std::hex << this->cload_address << std::endl;
    std::cout << std::noshowbase;

    // Currently at Offset 21 (0x15), read code segment size (uint16_t, 2 bytes, big endian).
    this->cbin_size  = static_cast<std::uint32_t>(pbuf->sbumpc()) <<  8;
    this->cbin_size += static_cast<std::uint32_t>(pbuf->sbumpc());

    std::cout << std::showbase;
    std::cout << "[libyardland/binary-file/binary-file.hpp:74] INFO Binary File Metadata, Code Segment Size: " << std::hex << this->cbin_size << std::endl;
    std::cout << std::noshowbase;

    // Currently at Offset 23 (0x17), read code segment.
    for (int i = 0; i < this->cbin_size && pbuf->sgetc() != EOF; i++) {
        pbuf->sbumpc();

    }

    if (pbuf->sgetc() == EOF) {
        std::cout << "[libyardland/binary-file/binary-file.hpp:35] ERROR Invalid or corrupt binary file (reached EOF too soon)" << std::endl;
        return 1;
    }

    return 0;
}

std::uint32_t binary_file::get_cload_address()
{
    return this->cload_address;
}

std::uint32_t binary_file::get_dload_address()
{
    return this->dload_address;
}

std::uint16_t binary_file::get_cbin_size()
{
    return this->cbin_size;
}

std::uint16_t binary_file::get_dbin_size()
{
    return this->dbin_size;
}
