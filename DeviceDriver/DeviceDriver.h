#pragma once
#include <stdexcept>
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    void checkRealValue(int result, long address);
    void checkBlankPage(long address);
};


class ReadFailException : public std::exception {
};