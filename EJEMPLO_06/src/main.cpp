#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// -------- LCD I2C 16x2 --------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// -------- DS18B20 --------
// DATA del DS18B20 conectado a GPIO 27
const uint8_t DS18B20_PIN = 27;
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// -------- KEYPAD 4x4 --------
const byte FILAS = 4;
const byte COLUMNAS = 4;

char teclas[FILAS][COLUMNAS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte pinesFilas[FILAS] = {13, 14, 16, 17};
byte pinesColumnas[COLUMNAS] = {18, 19, 23, 25};

Keypad teclado = Keypad(
  makeKeymap(teclas),
  pinesFilas,
  pinesColumnas,
  FILAS,
  COLUMNAS
);

// -------- ENTRADA DEL KEYPAD --------
String entrada = "";
const size_t MAX_CARACTERES = 16;

// -------- TIEMPO DE ACTUALIZACION DEL SENSOR --------
unsigned long ultimoMuestreo = 0;
const unsigned long INTERVALO_SENSOR_MS = 1000;
float temperaturaC = NAN;

void actualizarLCD() {
  // Linea 1: temperatura; deja espacio para limpiar caracteres viejos
  lcd.setCursor(0, 0);
  if (isnan(temperaturaC)) {
    lcd.print("Temp: --.- C    ");
  } else {
    char tempTexto[17];
    snprintf(tempTexto, sizeof(tempTexto), "Temp: %5.1f C", temperaturaC);
    lcd.print(tempTexto);
    int longitud = strlen(tempTexto);
    while (longitud++ < 16) lcd.print(' ');
  }

  // Linea 2: entrada del teclado
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(entrada);
}

void confirmarEntrada() {
  Serial.print("Entrada confirmada: ");
  if (entrada.length() > 0) {
    Serial.println(entrada);
  } else {
    Serial.println("(vacia)");
  }

  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print("OK: ");
  lcd.print(entrada);
  delay(1200);

  entrada = "";
  actualizarLCD();
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();

  sensors.begin();
  sensors.setResolution(10); // resolución suficiente para mostrar 0.1 °C

  lcd.setCursor(0, 0);
  lcd.print("Keypad + DS18B20");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(1500);

  sensors.requestTemperatures();
  temperaturaC = sensors.getTempCByIndex(0);

  if (temperaturaC == DEVICE_DISCONNECTED_C) {
    temperaturaC = NAN;
    Serial.println("Error: DS18B20 no detectado. Revisa DATA y pull-up.");
  }

  actualizarLCD();
}

void loop() {
  // Actualizar temperatura cada segundo sin bloquear el teclado
  unsigned long ahora = millis();
  if (ahora - ultimoMuestreo >= INTERVALO_SENSOR_MS) {
    ultimoMuestreo = ahora;

    sensors.requestTemperatures();
    float nuevaTemperatura = sensors.getTempCByIndex(0);

    if (nuevaTemperatura == DEVICE_DISCONNECTED_C) {
      temperaturaC = NAN;
      Serial.println("DS18B20 desconectado o sin lectura.");
    } else {
      temperaturaC = nuevaTemperatura;
      Serial.print("Temperatura: ");
      Serial.print(temperaturaC, 1);
      Serial.println(" °C");
    }

    actualizarLCD();
  }

  char tecla = teclado.getKey();
  if (tecla == NO_KEY) return;

  Serial.print("Tecla: ");
  Serial.println(tecla);

  if (tecla == '*') {
    entrada = "";
    actualizarLCD();
  } else if (tecla == '#') {
    confirmarEntrada();
  } else if (entrada.length() < MAX_CARACTERES) {
    entrada += tecla;
    actualizarLCD();
  }
}