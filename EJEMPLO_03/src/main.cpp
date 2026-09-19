#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// -------------------------
// Configuración DS18B20
// -------------------------
#define DS18B20_PIN 4

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// -------------------------
// Configuración LCD I2C
// -------------------------
#define SDA_PIN 21
#define SCL_PIN 22

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(115200);

    // Inicializar I2C
    Wire.begin(SDA_PIN, SCL_PIN);

    // Inicializar sensor
    sensors.begin();

    // Inicializar LCD
    lcd.init();
    lcd.backlight();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperatura");
    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");

    delay(2000);
}

void loop()
{
    // Solicitar medición
    sensors.requestTemperatures();

    // Obtener temperatura en Celsius
    float temperatura = sensors.getTempCByIndex(0);

    // Mostrar por monitor serial
    Serial.print("Temperatura: ");

    if (temperatura == DEVICE_DISCONNECTED_C)
    {
        Serial.println("Sensor desconectado");
    }
    else
    {
        Serial.print(temperatura);
        Serial.println(" °C");
    }

    // Mostrar en LCD
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temperatura:");

    lcd.setCursor(0, 1);

    if (temperatura == DEVICE_DISCONNECTED_C)
    {
        lcd.print("Error sensor");
    }
    else
    {
        lcd.print(temperatura, 1);
        lcd.print((char)223);  // Simbolo °
        lcd.print("C");
    }

    delay(1000);
}
