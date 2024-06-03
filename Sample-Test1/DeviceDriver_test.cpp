#include "../DeviceDriver/DeviceDriver.cpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class FlashFixture : public testing::Test {
public:
	FlashMock fMock;
	DeviceDriver dd{ &fMock };
};

TEST_F(FlashFixture, TestName) {
	EXPECT_CALL(fMock, read)
		.Times(5);

	dd.read(0x0A);
}

TEST_F(FlashFixture, TestName2) {
	EXPECT_CALL(fMock, read)
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xF));


	EXPECT_THROW(dd.read(0x0A), std::exception);
}

TEST_F(FlashFixture, TestName3) {
	EXPECT_CALL(fMock, read)
		.Times(1)
		.WillOnce(Return((unsigned char)0xFF));

	EXPECT_CALL(fMock, write);
	dd.write(0x0A, 0xAB);
}

TEST_F(FlashFixture, TestName4) {
	EXPECT_CALL(fMock, read)
		.WillOnce(Return((unsigned char)0xA));

	EXPECT_THROW(dd.write(0x0A, 0xAB), std::exception);
}