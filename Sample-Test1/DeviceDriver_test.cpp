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

class AppFixture : public testing::Test {
public:
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

TEST_F(AppFixture, App1) {

	FlashMock fMock;
	DeviceDriver dd{ &fMock };
	Application app{ &dd };

	//5개 address 읽고,
	//한 address read 5번씩
	//총 25회 read
	EXPECT_CALL(fMock, read)
		.Times(25);

	app.readAndPrint(0x00, 0x04);
}

TEST_F(AppFixture, App2) {

	FlashMock fMock;
	DeviceDriver dd{ &fMock };
	Application app{ &dd };

	//5개 address 읽고,
	//한 address read 5번씩
	//총 25회 read
	EXPECT_CALL(fMock, read)
		.Times(5)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(fMock, write(_, 0xFA)).
		Times(5);

	app.writeAll(0xFA);
}
