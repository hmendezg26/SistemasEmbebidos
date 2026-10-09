
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

// LCD I2C: direccion 0x27, 16 columnas y 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Entradas analogicas de la ESP32
int POT1_PIN = 34;
int POT2_PIN = 35;
int NTC_PIN  = 32;

// Parametros del termistor NTC
float R_FIXED = 10000.0; // Resistencia fija: 10 kohm
float R0 = 10000.0;      // NTC: 10 kohm a 25 grados C
float BETA = 3950.0;     // Beta tipica del NTC
float T_0 = 298.15;       // 25 grados C en Kelvin
float VCC = 3.3;
float ADC_MAX = 4095.0;

void setup() {
  Serial.begin(115200);

  analogReadResolution(12);
  analogSetPinAttenuation(POT1_PIN, ADC_11db);
  analogSetPinAttenuation(POT2_PIN, ADC_11db);
  analogSetPinAttenuation(NTC_PIN, ADC_11db);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("ESP32 + NTC");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(1500);
  lcd.clear();
}

float leerVoltaje(int pin) {
  int lectura = analogRead(pin);
  return lectura * VCC / ADC_MAX;
}

float leerTemperaturaNTC() {
  int adc = analogRead(NTC_PIN);

  // Evitar division entre cero
  if (adc <= 0 || adc >= 4095) {
    return NAN;
  }

  // Conexion:
  // 3.3 V -- NTC -- GPIO32 -- R_FIXED -- GND
  float resistenciaNTC =
      R_FIXED * (ADC_MAX / (float)adc - 1.0);

  // Ecuacion Beta: temperatura en Kelvin
  float temperaturaK =
      1.0 / (1.0 / T_0 +
      (1.0 / BETA) * log(resistenciaNTC / R0));

  // Convertir Kelvin a grados Celsius
  return temperaturaK - 273.15;
}

void loop() {
  float v1 = leerVoltaje(POT1_PIN);
  float v2 = leerVoltaje(POT2_PIN);
  float temp = leerTemperaturaNTC();

  // Mostrar los voltajes en la primera fila
  lcd.setCursor(0, 0);
  lcd.print("P1:");
  lcd.print(v1, 2);
  lcd.print(" P2:");
  lcd.print(v2, 2);

  // Mostrar la temperatura en la segunda fila
  lcd.setCursor(0, 1);
  lcd.print("NTC: ");

  if (isnan(temp)) {
    lcd.print("Error lectura ");
  } else {
    lcd.print(temp, 1);
    lcd.print((char)223); // Simbolo de grados
    lcd.print("C       ");
  }

  // Monitor serie
  Serial.print("Potenciometro 1: ");
  Serial.print(v1, 3);
  Serial.print(" V | Potenciometro 2: ");
  Serial.print(v2, 3);
  Serial.print(" V | Temperatura NTC: ");
  Serial.print(temp, 2);
  Serial.println(" C");

  delay(500);
}