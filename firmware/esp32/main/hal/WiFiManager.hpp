#pragma once 

#include <string> 

/** 
 * @brief Manages WiFi connection lifecycle for the ESP32. 
 * 
 * Handles initialization, connection, and blocking until 
 * an IP address is assigned. Must be initialized before 
 * any network operations. 
 */

 class WiFiManager {
public: 
    /** 
     * @brief Connects to the given network and blocks until ready. 
     * @param ssid      Network name. 
     * @param password  Network password. 
     * @throws std::runtime_error if connection fails. 
     */
    static void connect(const std::string& ssid, const std::string& password);
 }; 