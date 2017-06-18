#include "gtest/gtest.h"

#include "SerialFiller/SerialFiller.hpp"

using namespace mn;

namespace {

    class AddAndVerifyCrcTests : public ::testing::Test {
    protected:

        AddAndVerifyCrcTests() {
        }

        virtual ~AddAndVerifyCrcTests() {
        }
    };

    TEST_F(AddAndVerifyCrcTests, BasicTest) {
        ByteArray packet({ 0x01, 0x02, 0x03});
        SerialFiller::AddCrc(packet);
        EXPECT_EQ(ByteArray({ 0x01, 0x02, 0x03, 0xAD, 0xAD }), packet);
        EXPECT_EQ(true, SerialFiller::VerifyCrc(packet));
    }

    TEST_F(AddAndVerifyCrcTests, StandardCrcValTest) {
        ByteArray packet({ '1', '2', '3', '4', '5', '6', '7', '8', '9'});
        SerialFiller::AddCrc(packet);
        EXPECT_EQ(ByteArray({ '1', '2', '3', '4', '5', '6', '7', '8', '9', 0x29, 0xB1 }), packet);
        EXPECT_EQ(true, SerialFiller::VerifyCrc(packet));
    }

    TEST_F(AddAndVerifyCrcTests, BadCrcTest) {
        EXPECT_THROW(SerialFiller::VerifyCrc(ByteArray({0x01, 0x02, 0x03, 0xAD, 0xAE})), std::runtime_error);
    }

}  // namespace