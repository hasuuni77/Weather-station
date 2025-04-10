#include <WiFiS3.h>
#include <Arduino_JSON.h>

// Wi-Fi-uppgifter
const char* ssid = "H.F";
const char* password = "stockholM";
const String apiKey = "5d6726eb0c6eb4691f015d7ed6260147"; // Api nyckel
const String city = "Borlänge";
const String country = "SE";
const char* server = "api.openweathermap.org";

// Konfiguration av LED-pinnar
const int redLED = 8;    // Röd LED
const int greenLED = 9;  // Grön LED

void setup() {
  Serial.begin(115200);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  Serial.print("Ansluter till Wi-Fi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi anslutet!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    if (client.connect(server, 80)) {
      String url = "/data/2.5/weather?q=" + city + "," + country + "&appid=" + apiKey;
      Serial.println("Begär: " + url);

      client.println("GET " + url + " HTTP/1.1");
      client.println("Host: api.openweathermap.org");
      client.println("Connection: close");
      client.println();

      while (client.available() == 0) {
        delay(100);
      }

      String response = "";
      while (client.available()) {
        response += client.readString();
      }

      int jsonStart = response.indexOf("\r\n\r\n") + 4;
      String jsonData = response.substring(jsonStart);

      Serial.println("API-svar:");
      Serial.println(jsonData);

      JSONVar data = JSON.parse(jsonData);
      if (JSON.typeof(data) == "undefined") {
        Serial.println("JSON-parsning misslyckades!");
        return;
      }

      String weather = (const char*)data["weather"][0]["main"];
      Serial.println("Väder: " + weather);

      if (weather == "Clear" || weather == "Clouds") {
        digitalWrite(greenLED, HIGH);
        digitalWrite(redLED, LOW);
      } else {
        digitalWrite(redLED, HIGH);
        digitalWrite(greenLED, LOW);
      }
    } else {
      Serial.println("Kunde inte ansluta till servern.");
    }
    client.stop();
  } else {
    Serial.println("Wi-Fi är inte anslutet!");
  }
  delay(60000);
}
