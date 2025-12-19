#include "aws_iot.hpp"
#include "config.hpp"
#include <WiFi.h>
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

MIIDWTCCAkGgAwIBAgIUXh0pzBSQ3ny3sxHHWX4g8vIpQsowDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI1MTIxOTExMDIx
MloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANACSlvhcA2TYJ2YMAMk
XI2BLq4e3Cp5vQP1le6wBDmX2nGwQpLCuM8wah6KXUlBWAOg6+t0hrDyhUyMUeWC
3/HYmsUmKWjP8U9GaJwwcz5adS0wPwEG7unbzGqQiZHr32lK+rdX1nH5/WxXpKsV
M3IBPqP89VrcOErfS5ZSsyQ5yynNEChf4JdHWehn61BdcAkdUwYK6YtbKAcuQokX
28ytEHGBIYu5tXmaCMtDVyJ7La+UiCWsqQGj/ANR9b6mRxB8Ru60D65ets8uyAVs
Cq6NY0KUCUOdZMa/mzqFOJkt9f98Pt4CRxcblaZCR1qWB0FqxeOchP2BwEtl5iGu
SD0CAwEAAaNgMF4wHwYDVR0jBBgwFoAU7dENQ31vIR48c6bk5YEDhjaX9dgwHQYD
VR0OBBYEFM5STZW2/baSQf39ez27qXQ+tQFmMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQC+h8qKcdqGN3oyu9fjE3r2Xa4B
sDQIDSFmcRCkBCPpZED/hYnpnePC4LYI/59SAKsLLYeKZ6QbHkjjzyPNXTAsdgwO
1JO3YJXfJOIJ7r6dl9Ddv1qtKXa614IItw//0ubGuPfi1YZ2hDxaLtrH9QbpSr/h
NMDr2oxWDvRZBY3+a/XVDs600LWwWsGp2lDsDRGS/QrJPzwmoAgegrQ2FNWQS5Cd
dcx3pm4/eT41igJl2X2q8M90azSVFvfLbz/K2SaVBcNPuDcWaZzslyg5wWctUjRS
IJy+wp6XadrADz64TML83IObg9ma9G8aJDGAnyMWxbbAsCLoWhxL3PL+CDp/
-----END CERTIFICATE-----
)EOF";

const char AWS_CERT_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA0AJKW+FwDZNgnZgwAyRcjYEurh7cKnm9A/WV7rAEOZfacbBC
ksK4zzBqHopdSUFYA6Dr63SGsPKFTIxR5YLf8diaxSYpaM/xT0ZonDBzPlp1LTA/
AQbu6dvMapCJkevfaUr6t1fWcfn9bFekqxUzcgE+o/z1Wtw4St9LllKzJDnLKc0Q
KF/gl0dZ6GfrUF1wCR1TBgrpi1soBy5CiRfbzK0QcYEhi7m1eZoIy0NXInstr5SI
JaypAaP8A1H1vqZHEHxG7rQPrl62zy7IBWwKro1jQpQJQ51kxr+bOoU4mS31/3w+
3gJHFxuVpkJHWpYHQWrF45yE/YHAS2XmIa5IPQIDAQABAoIBAQCeJ/+t2L1ANTyS
1vI6kV0l4oFBtwkj6qhC6Gn1sDOmLsXTB3e26wNl1aP6UK4ZUuu+5o462sDGrb+Y
smBap6Xq1wzmtdtqbCFIa3qCt3wIfvL1RufAuirR+WN16ywOnU+jWXVEDi9pPfDo
fcMgqeAR4MxmF6HeUe8jTqDETWEUOtT1zozTx9zv8movT/EI9Hm3ArYMY6W6O0T8
IqXrSSSmnlmaULl5NSGMkd4RGu/QYEE/MvWBQhzGds82g6QE5nCkA+EO/j+hGyRc
E8RDdYeQ67M3Ahk9JpgQXA+lZhkzZSJwo7xfV7KmDsmbQc46brxu0zm92AYy9quW
86vfCiHpAoGBAPu/IloKyR4o8XLw6j8f9hP/P10YFEVHXqnpBOMJ8v/44Lmb1V17
q0J5mW9K6mLlT9ZEgNZwdiBNF+bNk38hhhwrbF5sNn5VsQ2GrzRJmxFq5+9srq37
l5xiOlXina3BYJ5+o24jRJnRjZjZnpkLoAs8a1kzdAhrh2YfMiOlnoVTAoGBANOF
+uoNvczxd7TBKqt+/SzGx6C2v1ymX7tj64cl4VJmvCJt10/nqZ4Ns6r7+wlTnqNy
AE0/q3PK9X68q4i/CnV/rTuG1yGUN7fQ4x5wYPi855IsfH/lEMfvh4/pTm62epFa
M7ZmR9VqyJuT5NjgU2EQw6miL3kspv/Glj2gRTovAoGASfq6IpHG1mkbwzZO8Cv5
SZkZysa3tkAp7m5+tCWJVnWRvJmx0t3zzv4i+9SdGmDe3E2XOu0jmYxuOLIy5Qo5
+e880makgO23sQziUdBLlIvBCtf6YUBtJlSrZe/JfHU2an02k7gjgbxWCxPwinMj
HgosVbNMJulKidUjC9ywv+cCgYBNM+mQ49MSqk92ucpJLeBaJ3NVRV4zAsaOLroY
acsDuFuSdWTQ1U0jUvzwu2e0z8BnB4T0rPh3GuzfhR1Wm+PFXwRrZZu/tclgXe2H
fpzmLIyY3YPTalfloZdo/06ROikiRDn7qPku+/qcTi6Iude05dmEYJ3TLGkHkgPk
GksqIQKBgQC5F9iXJKswtkm9T5bhzcn6VgoNf2DEeUl51d/o6HMUC6jAOqRl8TGb
MEkaWVvHIWDKf/c88jGqa1/0tSNFgwOindtM+DpXSal59zSRY+pDFgzABUiWEPm1
S8CRq9SGqwplb43dsD9b/S2aYYANXsaYXg6TL7u5Z2kq7Tk/gkrVbQ==
-----END RSA PRIVATE KEY-----
)EOF";

void aws_init() {
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

  doc["device_id"]  = DEVICE_ID;
  doc["timestamp"]  = millis() / 1000;
  doc["pm1_0"]       = d.pm1_0;
  doc["pm2_5"]       = d.pm2_5;
  doc["pm4_0"]       = d.pm4_0;
  doc["pm10"]        = d.pm10;
  doc["temperature"] = d.temperature;
  doc["humidity"]    = d.humidity;
  doc["voc"]         = d.voc;
  doc["nox"]         = d.nox;

  char buffer[256];                 // ✅ define buffer
  serializeJson(doc, buffer);        // ✅ serialize into buffer
  client.publish(MQTT_TOPIC, buffer);
}
void aws_loop() {

  Serial.println("AWS loop running");

  // 1️⃣ WiFi status debug
  Serial.print("WiFi status: ");
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("CONNECTED");
  } else {
    Serial.println("NOT CONNECTED");
    return;
  }

  // 2️⃣ MQTT connection debug
  Serial.print("MQTT connected: ");
  Serial.println(client.connected() ? "YES" : "NO");

  // 3️⃣ MQTT error code (MOST IMPORTANT)
  Serial.print("MQTT state code: ");
  Serial.println(client.state());

  if (!client.connected()) {
    Serial.println("Trying to reconnect MQTT...");
    client.connect(DEVICE_ID);
    return;
  }

  client.loop();
  Serial.println("MQTT loop OK");
}

