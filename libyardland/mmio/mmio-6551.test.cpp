#include <gtest/gtest.h>
#include <string>

#include <yardland/mmio-6551.hpp>

MMIO_6551 t6551;

TEST(MMIO6551Test, BasicInputOutput)
{
    std::string test_str = "Hello, World!";
    std::string test_out_str;

    for (int i = 0; i < test_str.size(); i++) {
        t6551.access(0b00, (uint8_t*) & test_str.c_str()[i], false);
    }

    do {
        uint8_t cur_char;

        cur_char = t6551.pop_output();

        test_out_str.push_back((char)cur_char);

    } while(test_out_str.at(test_out_str.size() - 1) != 0); 

    EXPECT_STREQ(test_str.c_str(), test_out_str.c_str());
}
