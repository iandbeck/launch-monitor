### Rolling Buffer Commands
* GC : Initiates rolling buffer. Needs trigger to output IQ data. 
* GS : Resumes normal operation.
* S! : Sends software trigger over UART. Use only for testing.

### Useful API Commands
* Os : Stop speed reporting
* OS : Start speed reporting 
* I? : Check baud rate
* ?? : Current module configuration

### Modifying Network Configuration 
Run the command: 
`idf.py menuconfig` and modify the **WiFi SSID** and **WiFi Password** variables. 