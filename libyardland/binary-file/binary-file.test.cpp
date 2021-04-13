#include <gtest/gtest.h>

#include <libyardland/binary-file/binary-file.hpp>

TEST(BinaryFileTest, SimpleParsing) {
    binary_file binfile;

    binfile.load("binaryfiletest_simpleparsing.bin");

    ASSERT_EQ(binfile.get_dload_address(), 0x00002000);
    ASSERT_EQ(binfile.get_cload_address(), 0x00002100);

    ASSERT_EQ(binfile.get_dbin_size(), 0x00ff);
    ASSERT_EQ(binfile.get_cbin_size(), 0x00ff);
}
