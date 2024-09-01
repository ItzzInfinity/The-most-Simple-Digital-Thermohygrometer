#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <DHT.h>

                                                                              // Pin definitions
#define DHTPIN 1                                                              // GPIO1
#define DHTTYPE DHT11
#define OLED_RESET -1
#define SH110X_I2C_ADDRESS 0x3c
                                                                              // Create DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

                                                                              // Create OLED display object
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, OLED_RESET);

void setup() {
                                                                              // Initialize DHT sensor
  Serial.begin(9600);
  dht.begin();

                                                                              // Initialize I2C for the display with custom pins
  Wire.begin(2, 0);

                                                                              // Initialize the display
  display.begin(SH110X_I2C_ADDRESS, OLED_RESET);
  display.display();
  delay(2000                                                                  // Pause for 2 seconds

                                                                              // Clear the buffer
  display.clearDisplay();
}

void loop() {
                                                                              // Read temperature as Celsius
  float tempC = dht.readTemperature();
                                                                              // Read humidity
  float humidity = dht.readHumidity();
                                                                              // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(tempC, humidity, false);
                                                                              // Check if any reads failed and exit early (to try again)
  if (isnan(tempC) || isnan(humidity)) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.println(F("Failed to read from DHT sensor!"));
    display.display();
    return;
  }

                                                                              // Clear the display
  display.clearDisplay();

                                                                              // Display temperature
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  Serial.println(F("Temp: "));
  display.setTextSize(2);
  Serial.println(tempC, 1);
  display.print(tempC,1);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print(F("C"));

                                                                              // Display humidity
  display.setCursor(0, 20);
  display.setTextSize(1);
  display.print(F("Humidity: "));
  Serial.println(F("Humidity: "));
  display.setTextSize(2);
  Serial.println(humidity, 0);
  display.print(int(humidity));
  display.print(F("%"));

                                                                              // Display humidity
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.print(F("Feels like: "));
  Serial.println(F("Feels like: "));
  display.setTextSize(2);
  Serial.println(hic,1);
  display.print(hic,1);
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.display();

                                                                              // Delay for a second before the next reading
  delay(1000);
}
