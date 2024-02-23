#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <ThingSpeak.h>

const char* ssid = "ssid";
const char* password = "password";
const char* apiKey = "api_key";
const unsigned long channelID = "channel_id";

WiFiClient client;

// URL Endpoint for OpenWeather
String URL = "http://api.openweathermap.org/data/2.5/weather?";
String ApiKey = "bac384cc030370ed3e9bb383b4ef940b";

String lat = "41.015137";
String lon = "28.979530";
const int lm35Pin = 34;  // Analog input pin for LM35

void setup()
{
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("#");
  }

  Serial.println("");
  Serial.print("WiFi connected to: ");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop()
{
  delay(20000);
  int sensorValue = analogRead(lm35Pin);  
  float voltage = sensorValue * 0.0008058608;  // Convert to voltage (3.3V ESP32) (* 3.3 / 4095)
  float temperatureC = voltage * 100 ;  // Convert to Celsius
  
  Serial.print("Temperature (LM35): ");
  Serial.print(temperatureC);
  Serial.print(" °C");

  if (WiFi.status() == WL_CONNECTED)
  {

    HTTPClient http;

    //Set HTTP Request Final URL with Location and API key information
    http.begin(URL + "lat=" + lat + "&lon=" + lon + "&units=metric&appid=" + ApiKey);

    // start connection and send HTTP Request
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
      //Read Data as a JSON string
      String JSON_Data = http.getString();
      // Serial.println(JSON_Data);

      // Retrieve some information about the weather from the JSON format
      DynamicJsonDocument doc(2048);
      deserializeJson(doc, JSON_Data);
      JsonObject obj = doc.as<JsonObject>();

      // Display the Current Weather Info
      const char* description = obj["weather"][0]["description"].as<const char*>();
      const float temp = obj["main"]["temp"].as<float>();
      const float humidity = obj["main"]["humidity"].as<float>();

      // Print values to monitor
      Serial.print(" || Temperature (API): ");
      Serial.print(temp);
      Serial.print(" °C"); 

      Serial.print(" || Difference: ");
      Serial.print(temperatureC - temp);
      Serial.println(" °C");
      
      ThingSpeak.setField(1, temperatureC);
      ThingSpeak.setField(2, temp);
      ThingSpeak.setField(3, temperatureC - temp);
      
      int result = ThingSpeak.writeFields(channelID, apiKey);
      if (result == 200)
      {
        Serial.println("Channel update successful.");
      }
      else
      {
        Serial.println("Problem updating channel. HTTP error code " + String(result));
      }
    }
    else
    {
      Serial.println("Error from API!");
    }
    http.end();
  }

  delay(3000);
}
