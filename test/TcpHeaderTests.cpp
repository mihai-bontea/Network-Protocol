#include <gtest/gtest.h>

#include "TCPHeader.h"

TEST(TCPHeaderTest, SerializeBasicHeader)
{
    TCPHeader tcp_header;

    tcp_header.source_port = 0x1234;

    uint8_t buffer[20] = {0};
    tcp_header.serialize(buffer);

    // Verify the byte values in big-endian
    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
}