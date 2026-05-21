#pragma once

class SerialReader {
public: 
    SerialReader() = default;
    ~SerialReader();

    /**
     * @brief Opens the serial port and starts reading data. 
     * This will block until the port is closed. 
     */
    void start(std::string file);

private:
    int fd;
};