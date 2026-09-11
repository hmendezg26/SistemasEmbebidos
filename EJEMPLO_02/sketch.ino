#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ==========================================
// DEFINICIÓN DE PINES
// ==========================================

// Sensor ultrasónico HC-SR04
#define TRIG_PIN 5
#define ECHO_PIN 18

// Comunicación I2C del LCD
#define SDA_PIN 21
#define SCL_PIN 22

// Activación de bombas
#define BOMBA_LLENA 17
#define BOMBA_VACIA 16

// Botones de Ajuste
#define SW_MODE 34
#define SW_UP 32
#define SW_DOWN 33


// ==========================================
// CONFIGURACIÓN DEL LCD
// ==========================================

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

// ==========================================
// VARIABLES
// ==========================================

long tiempo;
float distancia;

// ==========================================
// CONFIGURACIÓN INICIAL
// ==========================================

void setup() {

  // Monitor serial
  Serial.begin(115200);

  // Configuración del sensor ultrasónico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Configuración de comunicación I2C
  Wire.begin(SDA_PIN, SCL_PIN);

  // Inicialización del LCD
  lcd.init();
  lcd.backlight();

  // Mensaje inicial
  lcd.setCursor(0, 0);
  lcd.print("Sensor HC-SR04");

  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");

  delay(2000);

  lcd.clear();
}

// ==========================================
// PROGRAMA PRINCIPAL
// ==========================================

void loop() {

  // ------------------------------------------
  // Generar pulso de disparo
  // ------------------------------------------

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // ------------------------------------------
  // Medir tiempo de respuesta del ECHO
  // ------------------------------------------

  tiempo = pulseIn(ECHO_PIN, HIGH, 30000);

  // ------------------------------------------
  // Calcular distancia en centímetros
  // ------------------------------------------

  distancia = (tiempo * 0.0343) / 2.0;

  // ------------------------------------------
  // Mostrar distancia en LCD
  // ------------------------------------------

  lcd.setCursor(0, 0);
  lcd.print("Distancia:");

  lcd.setCursor(0, 1);
  lcd.print("                ");

  lcd.setCursor(0, 1);

  if (tiempo == 0) {

    lcd.print("Fuera de rango");

  } 
  else {

    lcd.print(distancia, 1);
    lcd.print(" cm");
  }

  // ------------------------------------------
  // Mostrar distancia en monitor serial
  // ------------------------------------------

  Serial.print("Distancia: ");

  if (tiempo == 0) {

    Serial.println("Fuera de rango");

  } 
  else {

    Serial.print(distancia, 1);
    Serial.println(" cm");
  }

  // Actualización cada 500 ms
  delay(500);
}
