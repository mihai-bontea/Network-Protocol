#include <gtest/gtest.h>

#include "TCPSegment.h"

TEST(TcpSegmentTest, DeserializeValidSegment)
{
    uint8_t buffer[] = {
            0x12, 0x34,             // source_port = 0x1234
            0xAB, 0xCD,             // destination_port = 0xABCD
            0x11, 0x22, 0x33, 0x44, // sequence_number = 0x11223344
            0x55, 0x66, 0x77, 0x88, // acknowledgment_number = 0x55667788
            0x50,                   // data_offset = 5(first half) reserved = 0
            0x18,                   // flags (ACK & PSH)
            0x40, 0x00,             // window_size = 0x4000
            0xBE, 0xEF,             // checksum = 0xBEEF
            0x00, 0x00,             // urgent_pointer

            // payload
            'T', 'E', 'S', 'T'
    };

    TCPSegment segment;
    segment.deserialize(buffer, sizeof(buffer));

    const auto header = segment.header;
    EXPECT_EQ(header.source_port, 0x1234);
    EXPECT_EQ(header.destination_port, 0xABCD);
    EXPECT_EQ(header.sequence_number, 0x11223344);
    EXPECT_EQ(header.acknowledgment_number, 0x55667788);
    EXPECT_EQ(header.data_offset, 5);
    EXPECT_EQ(header.reserved, 0);
    EXPECT_EQ(header.flags, 0x18);
    EXPECT_EQ(header.window_size, 0x4000);
    EXPECT_EQ(header.checksum, 0xBEEF);
    EXPECT_EQ(header.urgent_pointer, 0x0000);

    std::vector<uint8_t> expected_payload = {'T', 'E', 'S', 'T'};
    EXPECT_EQ(expected_payload, segment.payload);
}

TEST(TcpSegmentTest, DeserializeThrowIfBufferTooShort)
{
    uint8_t buffer[5] = {};

    TCPSegment segment;
    EXPECT_THROW(segment.deserialize(buffer, sizeof(buffer)), std::runtime_error);
}