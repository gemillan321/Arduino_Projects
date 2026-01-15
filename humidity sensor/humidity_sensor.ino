#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// WiFi credentials
// const char SSID[]     = ;
// const char PASSWORD[] = ;

// Cloud variables
float Temperature;
float Humidity;

void onTemperatureChange() {}
void onHumidityChange() {}

void initProperties() {
  ArduinoCloud.addProperty(Temperature, READWRITE, ON_CHANGE, onTemperatureChange);
  ArduinoCloud.addProperty(Humidity, READWRITE, ON_CHANGE, onHumidityChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASSWORD);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Serial ready!");

  dht.begin();        // Start DHT sensor
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // Read DHT11 sensor every 5 seconds
  static unsigned long lastRead = 0;
  if (millis() - lastRead > 5000) {
    lastRead = millis();
    float t = dht.readTemperature();
    float h = dht.readHumidity();

    // Only update if sensor reading is valid
    if (!isnan(t) && !isnan(h)) {
      Temperature = t;
      Humidity = h;

      Serial.print("Temperature: ");
      Serial.println(Temperature);
      Serial.print("Humidity: ");
      Serial.println(Humidity);
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }
}
