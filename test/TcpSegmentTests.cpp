#include <gtest/gtest.h>

#include "TCPSegment.h"

TEST(TcpSegmentTest, SerializeSegment)
{
    TCPHeader header;
    header.source_port = 0x1234;
    header.destination_port = 0xABCD;
    header.sequence_number = 0x11223344;
    header.acknowledgment_number = 0x55667788;
    header.data_offset = 5;
    header.reserved = 0;
    header.flags = 0x18;
    header.window_size = 0x4000;
    header.checksum = 0xBEEF;
    header.urgent_pointer = 0x0000;

    TCPSegment segment;
    segment.header = header;
    segment.payload = {'T', 'E', 'S', 'T'};

    const size_t segment_size = 24;
    ASSERT_EQ(segment.size(), segment_size);

    const auto buffer = segment.serialize();

    EXPECT_EQ(buffer[0], 0x12);
    EXPECT_EQ(buffer[1], 0x34);
    EXPECT_EQ(buffer[2], 0xAB);
    EXPECT_EQ(buffer[3], 0xCD);
    EXPECT_EQ(buffer[4], 0x11);
    EXPECT_EQ(buffer[5], 0x22);
    EXPECT_EQ(buffer[6], 0x33);
    EXPECT_EQ(buffer[7], 0x44);
    EXPECT_EQ(buffer[8], 0x55);
    EXPECT_EQ(buffer[9], 0x66);
    EXPECT_EQ(buffer[10], 0x77);
    EXPECT_EQ(buffer[11], 0x88);
    EXPECT_EQ(buffer[12], 0x50);
    EXPECT_EQ(buffer[13], 0x18);
    EXPECT_EQ(buffer[14], 0x40);
    EXPECT_EQ(buffer[15], 0x00);
    EXPECT_EQ(buffer[16], 0xBE);
    EXPECT_EQ(buffer[17], 0xEF);
    EXPECT_EQ(buffer[18], 0x00);
    EXPECT_EQ(buffer[19], 0x00);

    EXPECT_EQ(buffer[20], 'T');
    EXPECT_EQ(buffer[21], 'E');
    EXPECT_EQ(buffer[22], 'S');
    EXPECT_EQ(buffer[23], 'T');
}

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