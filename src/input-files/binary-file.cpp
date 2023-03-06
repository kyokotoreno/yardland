#include <input-files/binary-file.hpp>

BinaryFile::BinaryFile(std::string filename) {
    BOOST_LOG_TRIVIAL(info) << "Loading binary file: \"" << filename << "\".";

    std::fstream file;
    file.open(filename, std::fstream::in | std::fstream::binary);
    
    if (!file) {
        BOOST_LOG_TRIVIAL(error) << "Error loading binary file.";
        return;
    }

    mSize = std::filesystem::file_size(filename);

    mpBuffer = reinterpret_cast<uint8_t*>(calloc(MEMORY_BUFFER_SIZE, sizeof(uint8_t)));
    file.read(reinterpret_cast<char*>(mpBuffer), mSize);

    file.close();

    BOOST_LOG_TRIVIAL(debug) << "Binary File Metadata:\n" 
        << "\tFile Size: " << mSize;

    if (mSize < MEMORY_BUFFER_SIZE) {
        BOOST_LOG_TRIVIAL(warning) << "Binary file is smaller than the system's memory space: " << mSize << " < " << MEMORY_BUFFER_SIZE << ".";
        BOOST_LOG_TRIVIAL(warning) << "If a file needs offset options, use another format.";
    }

    BOOST_LOG_TRIVIAL(info) << "Loaded binary file.";
}

BinaryFile::~BinaryFile() {
    delete mpBuffer;
}
