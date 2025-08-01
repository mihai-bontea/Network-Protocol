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

TEST(TCPHeaderTest, DeserializeValidHeader)
{
    uint8_t buffer[20] = {
            0x12, 0x34,             // source_port = 0x1234
            0xAB, 0xCD,             // destination_port = 0xABCD
            0x11, 0x22, 0x33, 0x44, // sequence_number = 0x11223344
            0x55, 0x66, 0x77, 0x88, // acknowledgment_number = 0x55667788
            0x50,                   // data_offset = 5(first half) reserved = 0
            0x18,                   // flags (ACK & PSH)
            0x40, 0x00,             // window_size = 0x4000
            0xBE, 0xEF,             // checksum = 0xBEEF
            0x00, 0x00              // urgent_pointer
    };

    TCPHeader tcp_header;
    tcp_header.deserialize(buffer);

    EXPECT_EQ(tcp_header.source_port, 0x1234);
    EXPECT_EQ(tcp_header.destination_port, 0xABCD);
    EXPECT_EQ(tcp_header.sequence_number, 0x11223344);
    EXPECT_EQ(tcp_header.acknowledgment_number, 0x55667788);
    EXPECT_EQ(tcp_header.data_offset, 5);
    EXPECT_EQ(tcp_header.reserved, 0);
    EXPECT_EQ(tcp_header.flags, 0x18);
    EXPECT_EQ(tcp_header.window_size, 0x4000);
    EXPECT_EQ(tcp_header.checksum, 0xBEEF);
    EXPECT_EQ(tcp_header.urgent_pointer, 0x0000);
}