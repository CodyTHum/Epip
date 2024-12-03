#include <MCUFRIEND_kbv.h>
#include <DHT.h>
#include <TinyGPS++.h>

#define DHTPIN1 22     // Pin connected to the first DHT11 sensor
#define DHTTYPE DHT11  // DHT 11

MCUFRIEND_kbv tft;
DHT dht1(DHTPIN1, DHTTYPE);
TinyGPSPlus gps;

int sensorPin = A6; // Pin connected to the MQ135 sensor's analog output
int sensorValue = 0; // Variable to store the sensor value

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600); // Use Serial1 for GPS
  pinMode(sensorPin, INPUT); // Set the sensor pin as input
  dht1.begin();
  tft.begin(tft.readID());
  tft.setRotation(1); // Adjust rotation as needed
  tft.fillScreen(0x0000); // Clear screen with black color
  tft.setTextColor(0xFFFF); // Set text color to white
  tft.setTextSize(2); // Set text size
}

void loop() {
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }

  float temperature1 = dht1.readTemperature(); // Read temperature from first sensor

  if (isnan(temperature1)) {
    Serial.println("Failed to read from DHT sensor!");
    tft.setCursor(10, 10);
    tft.print("Sensor error");
  } else {

    Serial.print("Temperature 1: ");
    Serial.print(temperature1);
    Serial.println(" *C");

    tft.fillScreen(0x0000); // Clear screen with black color
    tft.setCursor(10, 10);
    tft.print("Temp 1: ");
    tft.print(temperature1);
    tft.print(" *C");
  }
  Serial.print(gps.location.isUpdated()); //Remove !
  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);

    tft.setCursor(10, 130);
    tft.print("Lat: ");
    tft.print(gps.location.lat(), 6);
    tft.setCursor(10, 160);
    tft.print("Lng: ");
    tft.print(gps.location.lng(), 6);
  }
  else{
    tft.setCursor(10, 130);
    tft.print("No GPS Signal");
  }
  sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  Serial.print("Air Quality: ");
  Serial.print(sensorValue); // Print the sensor value to the serial monitor
  Serial.println(" PPM"); // Print the unit (PPM - Parts Per Million)
  tft.setCursor(10, 190);
  tft.print("Air Quality: ");
  tft.print(sensorValue);
  tft.print(" PPM");
  

  delay(2000); // Wait for 2 seconds before the next reading
}