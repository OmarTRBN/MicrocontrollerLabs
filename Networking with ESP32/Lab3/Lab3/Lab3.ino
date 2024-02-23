 #include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "";
const char *password = "";

void setup() {
  Serial.begin(115200);

  // Wi-Fi bağlantısını başlat
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Boş döngü
  sendRequest();
  delay(1000);
}

void sendRequest() {
  HTTPClient http;

  // Server'ın IP adresini ve portunu belirt
  http.begin("http://192.168.65.241:80/selaminaleykum");
  
  // GET isteği gönder
  int httpResponseCode = http.GET();

  if (httpResponseCode > 0) {
    String payload = http.getString();
    Serial.println("Server response: " + payload);

    if (payload.indexOf("naber") != -1) {
      Serial.println("İyidir senden.");
    }
  
  } 
  else {
    Serial.println("Error on HTTP request");
    Serial.println("HTTP error: " + String(http.errorToString(httpResponseCode).c_str()));
  }

  // Bağlantıyı kapat
  http.end();
}
