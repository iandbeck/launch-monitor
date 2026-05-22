#pragma once

class SerialReader {
public: 
    SerialReader() = default;
    ~SerialReader();

    /**
     * @brief Test reader to output serial data directly.
     * without the use of ESP32 Microcontroller. This will 
     * block until the file is closed. 
     */
    void start(std::string file);

private:
    int fd;
};