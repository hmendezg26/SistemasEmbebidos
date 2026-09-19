# 🌡️ Práctica: Medición de temperatura con DS18B20 y LCD 16×2 I2C

![ESP32](https://img.shields.io/badge/ESP32-Microcontroller-blue)
![Arduino](https://img.shields.io/badge/Arduino-C%2FC%2B%2B-00979D)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulation-purple)

## 📋 Descripción

En esta práctica se desarrolla un sistema embebido basado en **ESP32** capaz de medir temperatura mediante un sensor digital **DS18B20** y mostrar el resultado en una pantalla **LCD 16×2 con interfaz I2C**.

La práctica integra:

* 🌡️ Adquisición de temperatura.
* 🔌 Comunicación digital **OneWire**.
* 📟 Comunicación **I2C**.
* 🖥️ Visualización de datos en LCD.
* 🖥️ Monitor Serial.
* ⚙️ Programación de ESP32 utilizando C/C++.
* 🧪 Simulación mediante Wokwi.

---

## 🎯 Objetivo

Implementar un sistema de adquisición y visualización de temperatura utilizando un ESP32, un sensor DS18B20 y una pantalla LCD 16×2 con interfaz I2C.

Al finalizar la práctica, el estudiante será capaz de:

1. Conectar un sensor DS18B20 al ESP32.
2. Utilizar el protocolo **OneWire**.
3. Obtener una medición de temperatura mediante software.
4. Configurar una pantalla LCD mediante I2C.
5. Mostrar información en el LCD.
6. Visualizar datos mediante el Monitor Serial.
7. Identificar errores de conexión o comunicación con los dispositivos.

---

# 🧰 Material requerido

## Hardware

| Componente         | Cantidad |
| ------------------ | -------: |
| ESP32 DevKit       |        1 |
| DS18B20            |        1 |
| LCD 16×2 I2C       |        1 |
| Resistencia 4.7 kΩ |        1 |
| Protoboard         |        1 |
| Cables Dupont      |   Varios |
| Cable USB          |        1 |

---

# 🔌 Diagrama de conexión

## DS18B20

El DS18B20 utiliza el protocolo **OneWire**, por lo que solamente requiere una línea de datos para comunicarse con el ESP32.

| DS18B20 | ESP32  |
| ------- | ------ |
| VCC     | 3.3 V  |
| DATA    | GPIO 4 |
| GND     | GND    |

Se debe colocar una resistencia de **4.7 kΩ entre DATA y VCC**.

```text
                  3.3 V
                    │
                  4.7 kΩ
                    │
                    ├──────── DATA
                    │          │
ESP32 GPIO 4 ───────┘       DS18B20
                               │
ESP32 3.3 V ───────────────── VCC
ESP32 GND ─────────────────── GND
```

---

# 📟 LCD 16×2 I2C

El LCD utiliza el protocolo **I2C**.

En el ESP32 se utilizarán:

* **SDA → GPIO 21**
* **SCL → GPIO 22**

| LCD I2C | ESP32     |
| ------- | --------- |
| GND     | GND       |
| VCC     | VIN / 5 V |
| SDA     | GPIO 21   |
| SCL     | GPIO 22   |

> ⚠️ **Nota:** La alimentación del LCD I2C depende del módulo utilizado. Muchos módulos funcionan con 5 V. Verifique que los niveles lógicos de SDA/SCL sean compatibles con el ESP32 antes de realizar la conexión física.

---

# 🔗 Conexión completa

```text
                         ESP32
                 ┌─────────────────┐
                 │                 │
                 │            3.3V ├───────┐
                 │                 │       │
                 │         GPIO 4  ├───────┼──── DATA
                 │                 │      [4.7kΩ]
                 │                 │       │
                 │            GND  ├───────┼──── GND
                 │                 │       │
                 │                 │    DS18B20
                 │                 │
                 │        GPIO 21  ├──────────── SDA
                 │        GPIO 22  ├──────────── SCL
                 │                 │
                 │            GND  ├──────────── GND
                 │                 │
                 │            VIN  ├──────────── VCC
                 │                 │
                 └─────────────────┘
                                          
                                      LCD 16×2 I2C
```

---

# 📚 Librerías

## PlatformIO

En el archivo `platformio.ini`:

```ini
lib_deps =
    paulstoffregen/OneWire
    milesburton/DallasTemperature
    marcoschwartz/LiquidCrystal_I2C
```

Ejemplo completo:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
    paulstoffregen/OneWire
    milesburton/DallasTemperature
    marcoschwartz/LiquidCrystal_I2C
```

---

# 💻 Código

Archivo:

```text
src/main.cpp
```

```cpp
#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>

// ==========================================
// CONFIGURACIÓN DS18B20
// ==========================================

#define DS18B20_PIN 4

OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// ==========================================
// CONFIGURACIÓN LCD I2C
// ==========================================

#define SDA_PIN 21
#define SCL_PIN 22

#define LCD_ADDRESS 0x27

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);


// ==========================================
// SETUP
// ==========================================

void setup()
{
    Serial.begin(115200);

    // Inicializar comunicación I2C
    Wire.begin(SDA_PIN, SCL_PIN);

    // Inicializar sensor DS18B20
    sensors.begin();

    // Inicializar LCD
    lcd.init();
    lcd.backlight();

    // Mensaje inicial
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Temperatura");

    lcd.setCursor(0, 1);
    lcd.print("Iniciando...");

    delay(2000);
}


// ==========================================
// LOOP
// ==========================================

void loop()
{
    // Solicitar medición
    sensors.requestTemperatures();

    // Obtener temperatura
    float temperatura = sensors.getTempCByIndex(0);

    // ======================================
    // MONITOR SERIAL
    // ======================================

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

    // ======================================
    // LCD
    // ======================================

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
        lcd.print((char)223);
        lcd.print("C");
    }

    delay(1000);
}
```

---

# 🖥️ Resultado esperado

## LCD

```text
┌────────────────┐
│Temperatura:    │
│25.6 °C         │
└────────────────┘
```

## Monitor Serial

```text
Temperatura: 25.6 °C
Temperatura: 25.7 °C
Temperatura: 25.7 °C
Temperatura: 25.8 °C
```

La temperatura dependerá de la configuración del sensor o de la simulación.

---

# 🧪 Simulación en Wokwi

La práctica puede simularse utilizando:

* ESP32 DevKit
* DS18B20
* LCD 16×2 I2C
* Resistencia de 4.7 kΩ

Archivos recomendados:

```text
proyecto/
│
├── include/
│
├── lib/
│
├── src/
│   └── main.cpp
│
├── diagram.json
│
├── platformio.ini
│
└── README.md
```

El archivo `diagram.json` contiene la descripción de los componentes y sus conexiones dentro de Wokwi.

---

# 🔎 Dirección I2C del LCD

La dirección más común de los módulos LCD I2C es:

```cpp
0x27
```

Sin embargo, algunos módulos pueden utilizar:

```cpp
0x3F
```

Si el LCD está correctamente conectado pero no muestra información, pruebe cambiar:

```cpp
#define LCD_ADDRESS 0x27
```

por:

```cpp
#define LCD_ADDRESS 0x3F
```

---

# 🔍 Escáner I2C

Para identificar automáticamente la dirección del LCD se puede utilizar el siguiente programa:

```cpp
#include <Arduino.h>
#include <Wire.h>

void setup()
{
    Serial.begin(115200);

    Wire.begin(21, 22);

    Serial.println("Escaner I2C");

    for (byte address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);

        byte error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.print("Dispositivo encontrado en 0x");

            if (address < 16)
                Serial.print("0");

            Serial.println(address, HEX);
        }
    }
}

void loop()
{
}
```

Ejemplo de resultado:

```text
Escaner I2C

Dispositivo encontrado en 0x27
```

---

# ⚠️ Problemas frecuentes

| Problema                     | Posible solución                           |
| ---------------------------- | ------------------------------------------ |
| LCD no muestra nada          | Verificar alimentación                     |
| LCD iluminado pero sin texto | Revisar dirección I2C                      |
| LCD muestra cuadros          | Ajustar el contraste                       |
| Aparece `Error sensor`       | Revisar DATA del DS18B20                   |
| Temperatura `-127 °C`        | Sensor no detectado                        |
| Monitor Serial vacío         | Revisar `monitor_speed`                    |
| Caracteres incorrectos       | Revisar configuración del LCD              |
| Wokwi no muestra Serial      | Verificar configuración del Monitor Serial |

---

# 🧠 Conceptos aprendidos

Esta práctica integra dos protocolos de comunicación diferentes:

### DS18B20 → OneWire

```text
ESP32
  │
  │ OneWire
  ▼
DS18B20
  │
  ▼
Temperatura
```

### LCD → I2C

```text
ESP32
  │
  │ I2C
  ├── SDA
  └── SCL
       │
       ▼
   LCD 16×2
```

Por lo tanto:

```text
       VARIABLE FÍSICA
       Temperatura
            │
            ▼
        DS18B20
            │
         OneWire
            │
            ▼
          ESP32
            │
           I2C
            │
            ▼
        LCD 16×2
```

---

# 📊 Flujo del programa

```text
        INICIO
           │
           ▼
   Inicializar Serial
           │
           ▼
    Inicializar I2C
           │
           ▼
   Inicializar DS18B20
           │
           ▼
     Inicializar LCD
           │
           ▼
     Solicitar lectura
           │
           ▼
    Obtener temperatura
           │
       ┌───┴────┐
       │        │
   ¿Sensor?     │
       │        │
      NO        SÍ
       │        │
       ▼        ▼
    Error    Temperatura
       │        │
       └───┬────┘
           ▼
      Mostrar LCD
           │
           ▼
     Monitor Serial
           │
           ▼
        1 segundo
           │
           └──────► Repetir
```

---

# 📝 Actividad para el estudiante

Modifique el programa para implementar las siguientes funciones:

### Nivel 1 — Básico

1. Mostrar la temperatura en °C.
2. Mostrar la temperatura en el Monitor Serial.
3. Cambiar el intervalo de actualización de 1 s a 500 ms.

### Nivel 2 — Intermedio

4. Mostrar dos líneas diferentes en el LCD:

```text
TEMP:
25.6 °C
```

5. Crear una condición de alarma:

```text
TEMP ALTA!
28.5 °C
```

cuando la temperatura supere un valor establecido.

### Nivel 3 — Integración

6. Agregar un LED que indique temperatura alta.
7. Agregar un buzzer para generar una alarma.
8. Implementar un límite configurable mediante una variable:

```cpp
float limite = 30.0;
```

9. Registrar las mediciones mediante el Monitor Serial.

---

# 📈 Extensión: Sistema de control

Como extensión de la práctica, el sistema puede evolucionar de un sistema de **medición** a un sistema de **control**:

```text
             DS18B20
                 │
                 ▼
             ESP32
                 │
        ┌────────┴────────┐
        │                 │
        ▼                 ▼
      LCD              Control
                         │
                  ┌──────┴──────┐
                  ▼             ▼
                Relay         PWM
                  │             │
                  ▼             ▼
               Actuador      Actuador
```

Esto permite posteriormente implementar aplicaciones de control de:

* 🌡️ Temperatura
* 💧 Humedad
* 🌀 Ventilación
* 🔥 Calentamiento
* ❄️ Refrigeración

---

# 📌 Competencias desarrolladas

* Programación de microcontroladores.
* Adquisición de variables físicas.
* Comunicación OneWire.
* Comunicación I2C.
* Manejo de sensores digitales.
* Manejo de displays.
* Programación C/C++.
* Depuración mediante Monitor Serial.
* Diseño de sistemas embebidos.
* Integración sensor–controlador–interfaz.

---

# 👨‍💻 Autor

**Sistemas Embebidos — ESP32**

Práctica orientada al desarrollo de sistemas embebidos para aplicaciones de **instrumentación, adquisición de datos y control de sistemas mecatrónicos**.
