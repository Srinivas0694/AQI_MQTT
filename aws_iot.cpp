#include "aws_iot.hpp"
#include "config.hpp"
#include <WiFi.h>
String deviceToken;
#include <WiFiClientSecure.h>   // ✅ REQUIRED
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClientSecure net;
PubSubClient client(net);
extern const char AWS_CERT_CA[];
extern const char AWS_CERT_CRT[];
extern const char AWS_CERT_PRIVATE[];
/* Paste your certificates here */
const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUYK/bzoS3FQju9bCKg9UnQ4d8ua4wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MTIxODEwMDQz
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAPF/3cuRRFMfIXUjDkK5
EoDHH2UFxfwdEvlI2wH/ESMC9BGbNdAZvlKT4KmFVwob3eyuF0IYU2oc5EJRv2Nd
7EYm9EUAscFIL0Otf8QEY8JIhWHTqg5rXTdG7jrMsNRmADFxTWoTsPflOD+xU5Io
UjoLTbJcmFjqaGnV8gPKN0OSatWhjc0dcI3iPR9KflTm3MkuHmPP04NdoB4787CS
qPmnijqE3jy3A2m63U11ZDRkipIFm9e9iUKIYBrgQOS8TbHKOUeA3+3QqiI+PcNq
H+eQnoTjSt69p3gawJiXC1oWloHvjgqHjxE68GDCDXnK3xveRat9+qR5Gc0bdHjZ
bg8CAwEAAaNgMF4wHwYDVR0jBBgwFoAUNG/4sMT3TlCw6IjeWmcXNqtDMFcwHQYD
VR0OBBYEFB7unHnDANh0kxJD8rDv/5UPXIkvMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQA8G4kTyy/8L+RrazAWNr+DK0dC
xYpsPg+pmMPmzYOPD6fO9NnBK8dkQtGc/nXZAaXAsK/1CMTXJmCynB+KMhuf+LSO
f7oYH3bbCOwUJlONfA3Ql3U0x7bCN2CO6QKUmD8EAX+sqobhKCeuPt4cXmkykMCH
pp2p/j6S4jYf88ifFBQTtYiMDMW/pqAYGL9J/ViGV4PD/kc9Ejy1U/5p5dw4iJrX
Kv5SMXqVi7UfEQtgDk7Bza0wFN+pEEm0oDzexJR+dGo298pYkAwjNvqktNKpA4jF
B/HJHFmIdOrpb4c4y4jIw4rowpNj8cAlhZPSf7t78A4rUjf8tXdFgz71BA3v
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA8X/dy5FEUx8hdSMOQrkSgMcfZQXF/B0S+UjbAf8RIwL0EZs1
0Bm+UpPgqYVXChvd7K4XQhhTahzkQlG/Y13sRib0RQCxwUgvQ61/xARjwkiFYdOq
DmtdN0buOsyw1GYAMXFNahOw9+U4P7FTkihSOgtNslyYWOpoadXyA8o3Q5Jq1aGN
zR1wjeI9H0p+VObcyS4eY8/Tg12gHjvzsJKo+aeKOoTePLcDabrdTXVkNGSKkgWb
172JQohgGuBA5LxNsco5R4Df7dCqIj49w2of55CehONK3r2neBrAmJcLWhaWge+O
CoePETrwYMINecrfG95Fq336pHkZzRt0eNluDwIDAQABAoIBACR2YN+GfGFsdtm/
xDxwwwlshyHyoDTzktTOmjqP719w57bsz1AvQtwm9anCtySQlo5QrrRNBfMkj5Yv
z4zKNo1U/laYxz3ejzxRqtPGseU4m+LsWWW58iYRcJCyLRS0ndzZNY4JkROsqTR8
qpiLu/aFlGKUtm/eXIt2QQcvde6elqjv86inHNUVmob+zLRj7iJIw/YaEdFnsNJd
cNlIA1gohWFJASeaSNEV6vPZ/tWwCiEx5wqQcxMzm+R8j+LFHBNWo6nU90GDykqU
KyYW9qW7ozakAgmBENY+xHBUrSOpxxvFQicfbH3ov6NTglMTys7GMKfoWzuZk6Ex
XR+nJgkCgYEA/LVl6qdirJVI2wEPqRz6cID+RRc2Mg2+AC+Q8ZFqH5TNm8obE0Mj
3F7WPL1k6bzO627/NTh3LwuEmZ1UU4+QOdHzNV/N+tc+J8dzfV/NbuzQ/svegfZE
hVRG+XyLZWkedpDSIoapYbSj7cqTp9jQsfIuzDUKVx62eclt8qceRusCgYEA9KUY
DGCrzJTNCHuyFUWRPNqLopWIEOBbV/S3Fba30tbRxJVzljuWgUX3BV1bdmnZkLhh
l6MKFK5RLk+WNuCRmhxcb3D7v0b6GrQJjI+/B6GqQVyS1Bjm+b8KokQKQ80jnvUd
k8L0NDWEeMrThNc6IlV12N/0vBNpmEJC7v9ItG0CgYBCt0k+2A4O7iKb3v3ZcdMU
XJnEd8pREJu2xNgJTpCr4cceeA8J2NHg3hDFXGMF6ljegyFRVaTxgKLzQzv+C4rS
GQGSd8aTkLvSGK/+y4oa3N6YRg5qVS/l20gZma3bihMGzlkL0G1rZBtbLf4pc+40
7HE6bE5cjbkzEeC7DS/LHQKBgQCyOohvlAn1LD7HPF570sfBnrH1y5xqNxk01eqA
HjKDns8JuZuQym6WVWNl/CKC/RBst3cZ4sSYVnp8E60q46YPsTPCWHx/WHUi+SCv
z5VrOOLxZUDu1gmHzx8vIgScapnV11sp5/DDDG4rFhDNCYOnubz2OApy7m2SaEud
FExibQKBgFF9kGdzbJjWrAQApY/ZMpgO8mSxpEy9pa4cPlGqxz0QqtLE8dgcK9iE
9BxzKlhMQddu7tI7/ihdelKwyEwZM2R2//oBiKxZWF2RbmRya7MC3Mh0WSyTJbVR
vUlNuBQ0+9sf24xoHegI2542zWmHp8tX+D2lpN1E90PTH6WuJuTY
-----END RSA PRIVATE KEY-----
)EOF";

void aws_init() {
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  deviceToken = "ESP32_" + mac;

  Serial.print("Device Token: ");
  Serial.println(deviceToken);


  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  client.setServer(AWS_ENDPOINT, AWS_PORT);
  if (!client.connected()) {
    Serial.println("MQTT not connected");
    return;
}
}

void aws_publish(const SensorData &d) {
  StaticJsonDocument<256> doc;

  doc["device_token"] = deviceToken;
  doc["timestamp"]  = millis() / 1000;
  doc["pm1_0"]       = d.pm1_0;
  doc["pm2_5"]       = d.pm2_5;
  doc["pm4_0"]       = d.pm4_0;
  doc["pm10"]        = d.pm10;
  doc["temperature"] = d.temperature;
  doc["humidity"]    = d.humidity;
  doc["co2"]         = d.co2;
  doc["voc"]         = d.voc;
  doc["nox"]         = d.nox;

  char buffer[256];                 // ✅ define buffer
  serializeJson(doc, buffer);        // ✅ serialize into buffer
  client.publish(MQTT_TOPIC, buffer);
}
void aws_loop() {
    if (!client.connected()) {
        Serial.println("Connecting to AWS IoT...");

        if (client.connect(DEVICE_TOKEN)) {
            Serial.println("AWS IoT connected");
        } else {
            Serial.print("AWS IoT connect failed, rc=");
            Serial.println(client.state());
            delay(3000);
            return;
        }
    }

    client.loop();
}

