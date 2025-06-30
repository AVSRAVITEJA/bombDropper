#include <Wifi.h>
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

const char* ssid = "DRONE_WIFI";
const char* password = "bombDropperMini";

const int stepPin = 25;
const int dirPin = 26;

WifiServer server(80);
TinyGPSPlus gps;
HardwareSerial GPS_Serial(2);

float targetLat = 0.0;
float targetLon = 0.0;
bool targetSet = false;

void setup() {
  Serial.begin(115200);
  GPS_Serial.begin(9600,Serial_8N1, 16, 17);

  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  Wifi.begin(ssid, password);
  while (Wifi.status() != WL_CONNECTED) {}
    delay(500);
    Serial.print(".");
    }
    Serial.println("\nWifi connected");
    Serial.println(Wifi.localIP());

    server.begin();
}

void loop() {
  WifiClient client = server.available();
  if(client) {
    String request = client.readStringUntil('\r');
    client.Flush();

    if (request.indexOf("/setdrop") != -1) {
      float lat = getParam(request, "lat").toFloat();
      float lon = getParam(request, "lon").toFloat();
      if (lat != 0.0 && lon != 0.0) {
        targetLat = lat;
        targetLon = lon;
        targetSet = true;
        Serial.printf("Drop Target Set: Lat=%.5f, Lon=%.5f\n", lat, lon);
      }
      client.print("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nDrop location received");
    }
    client.stop();
  }

  while (GPS_Serial.available()) {
    gps.encode(GPS_Serial.read());
  }
  if (gps.location.isValid() && targetSet) {
    float currLat = gps.location.lat();
    float currLon = gps.location.lng();
    float dist = distanceBetween(currLat, currLon, targetLat, targetLon);
    Serial.printf("Current: %.5f, %.5f | Distance to target: %.2f m\n", currLat, currLon, dist);
    if (dist < 5.0) { 
      dropBomb();
      targetSet = false;
    }
  }
}
String getParam(String req, String key) {
  int start = req.indexOf(key + "=");
  if (start == -1) return "";
  int end = req.indexOf('&', start);
  if (end == -1) end = req.length();
  return req.substring(start + key.length() + 1, end);
}
float distanceBetween(float lat1, float lon1, float lat2, float lon2) {
  const float R = 6371000; // Earth radius in meters
  float dLat = radians(lat2 - lat1);
  float dLon = radians(lon2 - lon1);
  float a = sin(dLat/2) * sin(dLat/2) +
            cos(radians(lat1)) * cos(radians(lat2)) *
            sin(dLon/2) * sin(dLon/2);
  float c = 2 * atan2(sqrt(a), sqrt(1-a));
  return R * c;
}
void dropBomb() {
  Serial.println(">>> DROP TRIGGERED <<<");
  digitalWrite(dirPin, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  }
   delay(500);
   
  digitalWrite(dirPin, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(800);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(800);
  } 
}