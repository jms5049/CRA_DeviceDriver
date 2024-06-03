#include "DeviceDriver.h"

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

void DeviceDriver::checkRealValue(int result, long address) {
    for (int i = 0; i < 4; i++) {
        int testValue = (int)(m_hardware->read(address));
        if (result != testValue) {
            throw ReadFailException();
        }
    }
}

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));

    checkRealValue(result, address);
    return result;
}

void DeviceDriver::write(long address, int data)
{
    checkBlankPage(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::checkBlankPage(long address) {
    int result = (int)(m_hardware->read(address));
    if (result != 0xFF) {
        throw std::exception("NO");
    }
}

class Application {
public:
    Application(DeviceDriver* dd) : dd{ dd } {
    }

    void readAndPrint(long startAddr, long endAddr) {
        for (long addr = startAddr; addr <= endAddr; addr++) {
            dd->read(addr);
        }
    }

    void writeAll(unsigned char value) {
        for (int addr = 0x00; addr <= 0x04; addr++) {
            dd->write(addr, value);
        }
    }

private:
    DeviceDriver* dd;
};