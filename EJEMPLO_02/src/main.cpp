#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -----------------------------
// Pines
// -----------------------------
#define TRIG_PIN 5
#define ECHO_PIN 18

#define SDA_PIN 21
#define SCL_PIN 22

// -----------------------------
// LCD
// -----------------------------
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(
    LCD_ADDRESS,
    LCD_COLUMNS,
    LCD_ROWS
);

void setup()
{
    Serial.begin(115200);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    Wire.begin(SDA_PIN, SCL_PIN);

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Sensor HC-SR04");

    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");

    delay(2000);

    lcd.clear();
}

void loop()
{
    // Generar pulso ultrasónico
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIG_PIN, LOW);

    // Medir tiempo del eco
    long tiempo = pulseIn(
        ECHO_PIN,
        HIGH,
        30000
    );

    // Calcular distancia
    if (tiempo == 0)
    {
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Distancia:");

        lcd.setCursor(0, 1);
        lcd.print("Fuera de rango");

        Serial.println("Fuera de rango");
    }
    else
    {
        float distancia = tiempo * 0.0343 / 2.0;

        // LCD
        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Distancia:");

        lcd.setCursor(0, 1);
        lcd.print(distancia, 1);
        lcd.print(" cm");

        // Monitor serial
        Serial.print("Distancia: ");
        Serial.print(distancia, 1);
        Serial.println(" cm");
    }

    delay(500);
}