**ESP32 Air Quality Monitoring System**
- ESP32 + SEN55 + BME688 + OLED + AWS IoT Core + DynamoDB

**Project Overview**
- This project implements a real-time air quality monitoring system using ESP32, Sensirion SEN55, and Bosch BME688 sensors.
- The measured environmental data is:
  - Displayed locally on an OLED display
  - Published securely to AWS IoT Core using MQTT
  - Stored in AWS DynamoDB for long-term storage and analysis

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
<img width="711" height="453" alt="image" src="https://github.com/user-attachments/assets/b75d4ba4-f4c3-41a2-aaec-1d1da3f42b72" />

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
- Create a Thing in AWS IoT Core
- Download certificates:
- Device Certificate
- Private Key
- Amazon Root CA
- Attach policy allowing:
  iot:Connect
  iot:Publish
  iot:Receive
  iot:Subscribe

**MQTT Topic**
  - #define MQTT_TOPIC "esp32/airquality"
Subscribe in AWS Console:
  - AWS IoT Core → MQTT test client → Subscribe

**IoT Rule → DynamoDB**
SQL Query:
    - SELECT * FROM 'esp32/airquality'
Action:
    - Insert message into DynamoDB table
    
**Data Format (JSON Payload)**
<img width="711" height="400" alt="image" src="https://github.com/user-attachments/assets/9a887e9e-d20b-4bc7-9884-cc95c158add6" />


**OLED Display Output**
<img width="716" height="354" alt="image" src="https://github.com/user-attachments/assets/49034a01-a20a-4b8e-86e6-da23cc8e2303" />


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

**Output in MQTT Client**

<img width="1125" height="676" alt="Screenshot 2025-12-19 214317" src="https://github.com/user-attachments/assets/7a1aef4d-c752-4f4a-baba-d01fd038dcd2" />

**Table data in DynamoDB**

<img width="1384" height="708" alt="Screenshot 2025-12-19 214341" src="https://github.com/user-attachments/assets/746bcae5-8ba2-448d-ac61-bf634c3f7bfb" />


