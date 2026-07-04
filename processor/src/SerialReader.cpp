#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <cerrno>

#include "SerialReader.hpp"

SerialReader::~SerialReader()
{
    // Destructor can be used to clean up resources if needed
    close(fd);
}

void SerialReader::start(std::string serialPort)
{
    // // Open the serial port
    // fd = open(serialPort.c_str(), O_RDONLY | O_NOCTTY | O_SYNC);
    // if (fd < 0)
    // {
    //     std::cerr << "Error opening serial port " << serialPort << ": " << strerror(errno) << std::endl;
    //     return;
    // }

    // termios tty{};
    // if (tcgetattr(fd, &tty) != 0)
    // {
    //     std::cerr << "Error getting terminal attributes for " << serialPort << std::endl;
    //     close(fd);
    //     return;
    // }

    // // Configure serial port settings
    // cfmakeraw(&tty);
    // cfsetispeed(&tty, B19200);
    // cfsetospeed(&tty, B19200);

    // tty.c_cflag &= ~PARENB; // No parity
    // tty.c_cflag &= ~CSTOPB; // 1 stop bit
    // tty.c_cflag &= ~CSIZE;
    // tty.c_cflag |= CS8;            // 8 data bits
    // tty.c_cflag |= CREAD | CLOCAL; // Enable receiver, ignore modem control lines

    // tcflush(fd, TCIOFLUSH);
    // if (tcsetattr(fd, TCSANOW, &tty) != 0)
    // {
    //     std::cerr << "Error setting terminal attributes" << std::endl;
    //     close(fd);
    //     return;
    // }

    // char buf[10];
    // while (true)
    // {
    //     ssize_t bytes = read(fd, buf, sizeof(buf));
    //     if (bytes < 0)
    //     {
    //         std::cerr << "Error reading from serial port " << serialPort << std::endl;
    //         return;
    //     }
    //     std::cout.write(buf, bytes);
    // }
}
