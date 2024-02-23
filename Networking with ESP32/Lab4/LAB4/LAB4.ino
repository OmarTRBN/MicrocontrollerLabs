#include <WiFi.h>
#include <WiFiClient.h>

const char* ssid = ""; // SSID
const char* password = ""; // Password

WiFiServer server(80);

#define RIGHTr 25
#define LEFTl 33
#define ACTIVE 32

void setup()
{
  Serial.begin(115200);

  pinMode(RIGHTr, OUTPUT);
  pinMode(LEFTl, OUTPUT);
  pinMode(ACTIVE, OUTPUT);

  digitalWrite(RIGHTr, LOW);
  digitalWrite(LEFTl, LOW);
  digitalWrite(ACTIVE, LOW);

  Serial.print("Bağlantı kuruluyor.. ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi bağlandı.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        if (c == '\n')
        {
          if (currentLine.length() == 0) {

            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            client.println("<body><h1>DENEYAP KART Servo Kontrol</h1>");

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");


            client.println("<table align='center'><tr><td>&nbps;</td>");
            client.println("<td><a href=\"/F\"><button style='background-color: #55555; color:white; width:300px; font-size:50px; text-align:center;'>forward</button></a></td>");
            client.println("<td>&nbsp;</td></tr></body>");

            client.println("<td><a href=\"/L\"><button style='background-color: #55555; color:white; width:300px; font-size:50px; text-align:center;'>left</button></a></td>");
            client.println("<td><a href=\"/S\"><button style='background-color: #55555; color:white; width:300px; font-size:50px; text-align:center;'>stop</button></a></td>");
            client.println("<td><a href=\"/R\"><button style='background-color: #55555; color:white; width:300px; font-size:50px; text-align:center;'>right</button></a></td>");

            client.println("<tr><td>&nbsp;</td>");
            client.println("<td><a href=\"/B\"><button style='background-color: #55555; color:white; width:300px; font-size:50px; text-align:center;'>back</button></a></td>");
            client.println("<td>&nbsp;</td></tr></body>");

            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }

        if (currentLine.endsWith("GET /F"))
        {
          digitalWrite(RIGHTr, HIGH);
          digitalWrite(LEFTl, HIGH);
          digitalWrite(ACTIVE, HIGH);
        }
        if (currentLine.endsWith("GET /R"))
        {
          digitalWrite(RIGHTr, HIGH);
          digitalWrite(LEFTl, LOW);
          digitalWrite(ACTIVE, HIGH);
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(RIGHTr, LOW);
          digitalWrite(LEFTl, HIGH);
          digitalWrite(ACTIVE, HIGH);
        }
        if (currentLine.endsWith("GET /B"))
        {
          digitalWrite(RIGHTr, LOW);
          digitalWrite(LEFTl, LOW);
          digitalWrite(ACTIVE, HIGH);
        }
        if (currentLine.endsWith("GET /S"))
        {
          digitalWrite(RIGHTr, LOW);
          digitalWrite(LEFTl, LOW);
          digitalWrite(ACTIVE, LOW);
        }
      }
    }
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
