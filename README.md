**ESP32 Air Quality Monitoring System**
ESP32 + SEN55 + BME688 + OLED + AWS IoT Core + DynamoDB

**Project Overview**
This project implements a real-time air quality monitoring system using ESP32, Sensirion SEN55, and Bosch BME688 sensors.
The measured environmental data is:
Displayed locally on an OLED display
Published securely to AWS IoT Core using MQTT
Stored in AWS DynamoDB for long-term storage and analysis

**Features**
Real-time measurement of:
- PM1.0, PM2.5, PM4.0, PM10
- Temperature & Humidity
- VOC Index
- NOx Index
- OLED display in portrait mode
- Secure MQTT communication using AWS IoT certificates
- Cloud storage using AWS DynamoDB
- Modular, clean code structure using PlatformIO
- Easily extendable for dashboards or analytics

**Hardware Used**
| Component    | Description                   |
| ------------ | ----------------------------- |
| ESP32        | Main microcontroller          |
| SEN55        | PM, VOC, NOx sensor           |
| BME688       | Temperature & Humidity sensor |
| OLED Display | SSD1306 (128×64, I2C)         |
| Power        | USB / External 5V             |

**Pin Connections**
| ESP32     | OLED | SEN55 | BME688 |
| --------- | ---- | ----- | ------ |
| GPIO 21   | SDA  | SDA   | SDA    |
| GPIO 22   | SCL  | SCL   | SCL    |
| 3.3V / 5V | VCC  | VCC   | VCC    |
| GND       | GND  | GND   | GND    |

**Project structure**
├── include
│   ├── aws_iot.hpp
│   ├── config.hpp
│   ├── display.hpp
│   ├── sensors.hpp
│
├── src
│   ├── aws_iot.cpp
│   ├── display.cpp
│   ├── sensors.cpp
│   ├── main.cpp
│
├── platformio.ini
├── README.md

**Software & Libraries**
- PlatformIO (VS Code)
- ESP32 Arduino Framework
- Libraries used:
  - Adafruit SSD1306
  - Adafruit GFX
  - ArduinoJson
  - PubSubClient
  - Sensirion SEN5x Library
  - Adafruit BME680/BME688

**AWS Configuration**
- AWS Services Used
- AWS IoT Core
- AWS DynamoDB
- MQTT (TLS, Port 8883)

**AWS Configuration Steps (High Level)**
Create DynamoDB Table
Table name: AirQualityData
Partition key: device_id (String)
Sort key: timestamp (Number)

**Create AWS IoT Thing**
Create a Thing in AWS IoT Core
Download certificates:
Device Certificate
Private Key
Amazon Root CA
Attach policy allowing:
iot:Connect
iot:Publish
iot:Receive
iot:Subscribe

**MQTT Topic**
  #define MQTT_TOPIC "esp32/airquality"
Subscribe in AWS Console:
  AWS IoT Core → MQTT test client → Subscribe

**IoT Rule → DynamoDB**
SQL Query:
    SELECT * FROM 'esp32/airquality'
Action:
    Insert message into DynamoDB table
    
Data Format (JSON Payload)
json :
{
  "device_id": "esp32_01",
  "timestamp": 1734501234,
  "pm1_0": 7.5,
  "pm2_5": 8.1,
  "pm4_0": 8.3,
  "pm10": 8.4,
  "temperature": 25.3,
  "humidity": 39.1,
  "voc": 182,
  "nox": 1
}

**OLED Display Output**
DEVICE 1
────────────
PM1.0  7.5
PM2.5  8.1
PM4.0  8.3
PM10   8.4
Temp   25.3 C
RH     39 %
VOC    182
NOx    1

**How to Run the Project**
1.Install VS Code + PlatformIO
2.Clone this repository
3.Update config.hpp:
  - WiFi credentials
  - AWS endpoint
4.Connect ESP32
5.Upload firmware
6.Open Serial Monitor
7.Check:
  - OLED display
  - AWS MQTT Test Client
  - DynamoDB table
