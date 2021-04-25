# IoT App - NodeMCU Azure IoT Central

> Sending sensor data to Azure IoT central using NodeMCU

![screenshot](https://github.com/subhansanjaya/iot-app/blob/main/image.jpeg)

Libraries Used: 
- AzureIoTHub 1.0.45
- AzureIoTUtility 1.0.45
- AzureIoTProtocol_MQTT 1.0.45
- ArduinoJson 5.13.4
- DHT sensor library 1.3.4
- Adafruit Unified Sensor 1.1.4
- Dallas Temperature 3.9.0
- OneWire 2.3.5

Note: use the package versions to avoide compilation issues. 

Sensors Used:
- Turbidity Sensor MD0591
- PH Sensor
- Temperature and Humidity Sensor (DHT11/DHT22)
- Gas Sensor (MQ 135)
- Waterproof Temperature Sensor  DS18B20



## Build Setup

``` bash
# Connect the sensors to NodeMCU

# Install the required libraries (Arduino IDE used version 1.8.8)

# Change the configurations on config.h

# Now connect the NodeMCU to your Laptop/PC and select the appropriate port in the Arduino IDE.

# Upload the app.ino to the board.

# Open the Serial Monitor of Arduino IDE, Select 115200 as the baud rate and No line ending.

#Enter the following information through the Serial Terminal:

SSID of your WiFI network.
Password of your WiFi network.
Connection String-Primary Key of your Device. e.g. HostName=xxx.azure-devices.net;DeviceId=xxx;SharedAccessKey=xxxxxxxxxxxxx
