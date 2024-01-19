#include <Adafruit_MAX31856.h>

// Pins: LaskaKit ESP32-S3,   ESP32
#define PIN_ON      47
//#define PIN_ON                 2
#define CS_PIN      10
//#define CS_PIN                15

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS_PIN, 11, 13, 12);  //LaskaKit ESP32-S3-DEVKit
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS_PIN, 13, 12, 14);  //LaskaKit ESP32-DEVKit

// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31856 maxthermo = Adafruit_MAX31856(CS_PIN);

void setup() {
  pinMode(PIN_ON, OUTPUT);
  digitalWrite(PIN_ON, HIGH);
  Serial.begin(115200);
  
  while (!Serial) delay(10);
  Serial.println("MAX31856 thermocouple test");

  if (!maxthermo.begin()) {
    Serial.println("Could not initialize thermocouple.");
    while (1) delay(10);
  }

  maxthermo.setThermocoupleType(MAX31856_TCTYPE_K);

  Serial.print("Thermocouple type: ");
  switch (maxthermo.getThermocoupleType() ) {
    case MAX31856_TCTYPE_B: Serial.println("B Type"); break;
    case MAX31856_TCTYPE_E: Serial.println("E Type"); break;
    case MAX31856_TCTYPE_J: Serial.println("J Type"); break;
    case MAX31856_TCTYPE_K: Serial.println("K Type"); break;
    case MAX31856_TCTYPE_N: Serial.println("N Type"); break;
    case MAX31856_TCTYPE_R: Serial.println("R Type"); break;
    case MAX31856_TCTYPE_S: Serial.println("S Type"); break;
    case MAX31856_TCTYPE_T: Serial.println("T Type"); break;
    case MAX31856_VMODE_G8: Serial.println("Voltage x8 Gain mode"); break;
    case MAX31856_VMODE_G32: Serial.println("Voltage x8 Gain mode"); break;
    default: Serial.println("Unknown"); break;
  }

  maxthermo.setConversionMode(MAX31856_ONESHOT_NOWAIT);
}

void loop() {
  // trigger a conversion, returns immediately
  maxthermo.triggerOneShot();

  //
  // here's where you can do other things
  //
  delay(1000); // replace this with whatever

  // check for conversion complete and read temperature
  if (maxthermo.conversionComplete()) {
    Serial.println(maxthermo.readThermocoupleTemperature());
  } else {
    Serial.println("Conversion not complete!");
  }
}
