#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_BME280.h>
#include <Wire.h>
#include <ArduinoJson.h>
#define IP "http://192.168.43.251:3001/api/newreading"

Adafruit_BME280 sensor;
ESP8266WiFiMulti WiFiMulti;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  Wire.begin();
  if(!sensor.begin(0x76)){
    Serial.println("Error: Sensor not found");
  }
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Pixel_3", "88888888");
  
 }

void loop() {
  // put your main code here, to run repeatedly:
  //float temperature = sensor.readTemperature();
  StaticJsonBuffer<JSON_OBJECT_SIZE(4)> jbuffer;
  String output = "";
  JsonObject& data = jbuffer.createObject();
  data["name"] = "MeriAnna";
  data["temperature"] = sensor.readTemperature();
  data["pressure"] = sensor.readPressure();
  data["humidity"] = sensor.readHumidity();
  data.prettyPrintTo(Serial);
  data.printTo(output);
  
  if(WiFiMulti.run() == WL_CONNECTED){
    Serial.println("Connection established, local IP: ");
    Serial.println(WiFi.localIP());
    HTTPClient http;
    http.begin(IP);
    http.addHeader("Content-type", "application/json");
    int httpcode = http.POST(output);
    if(httpcode == HTTP_CODE_OK){
      Serial.println("It works");
    }else{
      Serial.println("Doesn't work");
      Serial.println(httpcode);
    }
    delay(5000);
  }
  Serial.println("...");
  delay(1000);
}