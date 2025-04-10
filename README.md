# LED Weather Display

Detta projekt visar väderstatus med hjälp av LED-lampor genom att hämta väderdata från OpenWeatherMap API.

## Funktion

- Hämtar väderdata baserat på stad och land (Borlänge, Sverige)
- Om vädret är klart eller molnigt: tänd **grön LED**
- Om det är regnigt eller annat väder: tänd **röd LED**

## Hårdvara

- Arduino med WiFi-stöd (t.ex. Uno R4 WiFi)
- Röd LED (ansluten till pin 8)
- Grön LED (ansluten till pin 9)

## Krävda bibliotek

- WiFiS3
- Arduino_JSON

## Inställningar

- SSID och lösenord måste uppdateras för ditt WiFi-nätverk
- API-nyckel från [OpenWeatherMap](https://openweathermap.org/)


