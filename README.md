# 🚀 Sistemas Embebidos – Instalación y configuración del entorno

![ESP32](https://img.shields.io/badge/ESP32-DevKit%20V1-blue?logo=espressif)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange?logo=platformio)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulation-purple)
![Arduino](https://img.shields.io/badge/Framework-Arduino-teal?logo=arduino)
![VS Code](https://img.shields.io/badge/Visual%20Studio%20Code-IDE-blue?logo=visualstudiocode)
![GitHub](https://img.shields.io/badge/GitHub-Version%20Control-black?logo=github)

---

## 📚 1. Introducción

En esta guía se describe el procedimiento para instalar y configurar el entorno de desarrollo utilizado en la asignatura de **Sistemas Embebidos**.

El entorno permitirá desarrollar, compilar, simular y posteriormente programar sistemas basados en **ESP32** utilizando:

* **Visual Studio Code**
* **PlatformIO IDE**
* **Arduino Framework**
* **Wokwi**
* **Git y GitHub**

El flujo general de trabajo será:

```text
                 SISTEMAS EMBEBIDOS
                         │
                         ▼
                Visual Studio Code
                         │
                ┌────────┴────────┐
                │                 │
                ▼                 ▼
           PlatformIO           Wokwi
                │                 │
             Compilar          Simular
                │                 │
                └────────┬────────┘
                         ▼
                       ESP32
                         │
                         ▼
                      GitHub
```

---

# 🎯 2. Objetivo

Configurar un entorno de desarrollo que permita al estudiante:

1. Crear proyectos para ESP32.
2. Programar utilizando Arduino/C++.
3. Compilar programas mediante PlatformIO.
4. Simular circuitos mediante Wokwi.
5. Utilizar sensores y periféricos virtuales.
6. Posteriormente transferir el programa a un ESP32 físico.
7. Documentar las prácticas.
8. Respaldar los proyectos mediante GitHub.

---

# 🧰 3. Software requerido

| Software           | Función                    |
| ------------------ | -------------------------- |
| Visual Studio Code | Entorno de desarrollo      |
| PlatformIO IDE     | Compilación y programación |
| Arduino Framework  | Framework para ESP32       |
| Wokwi for VS Code  | Simulación                 |
| Git                | Control de versiones       |
| GitHub             | Respaldo y colaboración    |

> **Nota:** Para las prácticas desarrolladas con **PlatformIO + Arduino Framework** no es necesario instalar **ESP-IDF Explorer**.

---

# 💻 4. Instalación de Visual Studio Code

Descargar Visual Studio Code desde:

👉 https://code.visualstudio.com/

Instalar utilizando las opciones recomendadas.

Una vez instalado, ejecutar:

```text
Visual Studio Code
```

---

# 🔧 5. Instalación de PlatformIO

Dentro de Visual Studio Code:

```text
Extensions
```

Buscar:

```text
PlatformIO IDE
```

Instalar la extensión.

PlatformIO permite administrar:

* Placas de desarrollo.
* Frameworks.
* Librerías.
* Compilación.
* Monitor serial.
* Programación del microcontrolador.

Después de la instalación se recomienda reiniciar Visual Studio Code.

En la barra lateral aparecerá el icono:

```text
PlatformIO
```

---

# 🧪 6. Crear un proyecto ESP32

Abrir:

```text
PlatformIO → Home
```

Seleccionar:

```text
New Project
```

Configurar:

| Parámetro | Valor                  |
| --------- | ---------------------- |
| Name      | `ESP32_Prueba`         |
| Board     | `DOIT ESP32 DEVKIT V1` |
| Framework | `Arduino`              |
| Location  | Carpeta de trabajo     |

Presionar:

```text
Finish
```

PlatformIO generará una estructura similar a:

```text
ESP32_Prueba/
│
├── include/
├── lib/
├── src/
│   └── main.cpp
├── test/
└── platformio.ini
```

---

# 📝 7. Crear el primer programa

Abrir:

```text
src/main.cpp
```

Colocar:

```cpp
#include <Arduino.h>

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Serial.println("ESP32 funcionando");
    delay(1000);
}
```

Guardar el archivo:

```text
Ctrl + S
```

---

# 🔨 8. Compilar el proyecto

Desde PlatformIO seleccionar:

```text
Build
```

También se puede utilizar la terminal:

```bash
pio run
```

Si la compilación fue correcta deberá aparecer:

```text
========================= [SUCCESS] =========================
```

PlatformIO generará automáticamente los archivos de compilación dentro de:

```text
.pio/
```

> **Importante:** La carpeta `.pio` no debe subirse a GitHub.

---

# 🌐 9. Instalar Wokwi para Visual Studio Code

Wokwi permite simular microcontroladores y componentes electrónicos directamente desde Visual Studio Code.

En VS Code abrir:

```text
Extensions
```

Buscar:

```text
Wokwi
```

Instalar:

```text
Wokwi for VS Code
```

La extensión permite trabajar con proyectos de PlatformIO y ejecutar simulaciones directamente desde VS Code.

---

# 👤 10. Crear una cuenta Wokwi

Ingresar a:

👉 https://wokwi.com/

Seleccionar:

```text
Sign Up
```

Crear una cuenta utilizando el método de autenticación disponible.

> Cada estudiante deberá utilizar su propia cuenta. No se deben compartir contraseñas, tokens o credenciales.

---

# 🔑 11. Activar la licencia de Wokwi para VS Code

Después de instalar la extensión:

1. Abrir Visual Studio Code.
2. Presionar:

```text
F1
```

3. Buscar:

```text
Wokwi: Request a new License
```

4. Ejecutar la opción.
5. Se abrirá el navegador.
6. Iniciar sesión en Wokwi.
7. Autorizar la licencia para VS Code.
8. Regresar a Visual Studio Code.

La licencia deberá quedar asociada a la cuenta utilizada.

> Wokwi ofrece actualmente una modalidad gratuita para uso personal. Los planes comerciales/profesionales tienen características adicionales.

---

# 🧩 12. Crear el circuito de Wokwi

Dentro del proyecto de PlatformIO crear:

```text
diagram.json
```

La estructura será:

```text
ESP32_Prueba/
│
├── platformio.ini
├── diagram.json
│
├── src/
│   └── main.cpp
│
├── include/
├── lib/
└── test/
```

Ejemplo básico:

```json
{
  "version": 1,
  "author": "Sistemas Embebidos",
  "editor": "wokwi",

  "parts": [
    {
      "type": "board-esp32-devkit-v1",
      "id": "esp",
      "top": 0,
      "left": 0,
      "attrs": {}
    }
  ],

  "connections": []
}
```

El archivo `diagram.json` contiene la representación del circuito que será utilizado durante la simulación.

---

# ⚙️ 13. Crear `wokwi.toml`

En la raíz del proyecto crear:

```text
wokwi.toml
```

Contenido:

```toml
[wokwi]
version = 1
firmware = '.pio/build/esp32dev/firmware.bin'
elf = '.pio/build/esp32dev/firmware.elf'
```

Este archivo indica a Wokwi dónde encontrar el firmware generado por PlatformIO.

La relación será:

```text
src/main.cpp
      │
      ▼
   PlatformIO
      │
      ▼
.pio/build/esp32dev/
      │
      ├── firmware.bin
      └── firmware.elf
              │
              ▼
            Wokwi
```

---

# 📁 14. Estructura completa del proyecto

Después de configurar PlatformIO y Wokwi:

```text
ESP32_Prueba/
│
├── platformio.ini
├── wokwi.toml
├── diagram.json
│
├── src/
│   └── main.cpp
│
├── include/
├── lib/
├── test/
│
└── .pio/
```

### Función de cada archivo

| Archivo          | Función                            |
| ---------------- | ---------------------------------- |
| `main.cpp`       | Programa principal                 |
| `platformio.ini` | Configuración de PlatformIO        |
| `diagram.json`   | Circuito de Wokwi                  |
| `wokwi.toml`     | Configuración de Wokwi             |
| `README.md`      | Documentación                      |
| `.pio/`          | Archivos generados automáticamente |

---

# 🔄 15. Flujo de trabajo

El flujo de trabajo recomendado para las prácticas será:

```text
             main.cpp
                 │
                 ▼
          ┌─────────────┐
          │  PlatformIO │
          └──────┬──────┘
                 │
              BUILD
                 │
                 ▼
        firmware.bin / ELF
                 │
                 ▼
          ┌─────────────┐
          │    Wokwi    │
          └──────┬──────┘
                 │
             SIMULATE
                 │
                 ▼
               ESP32
```

Por lo tanto:

### Paso 1

Modificar:

```text
src/main.cpp
```

### Paso 2

Guardar:

```text
Ctrl + S
```

### Paso 3

Compilar:

```text
PlatformIO → Build
```

### Paso 4

Abrir:

```text
diagram.json
```

### Paso 5

Iniciar:

```text
▶ Start Simulation
```

---

# ▶️ 16. Iniciar la simulación

Abrir:

```text
diagram.json
```

Wokwi mostrará el circuito.

También puede iniciarse desde la paleta de comandos:

```text
F1
```

Buscar:

```text
Wokwi: Start Simulator
```

Seleccionar la opción.

---

# 🔌 17. Ejemplo de práctica: HC-SR04 + LCD 16×2

Una vez configurado el entorno se puede desarrollar una práctica como:

```text
ESP32
 │
 ├── HC-SR04
 │
 └── LCD 16×2 I2C
```

Configuración:

### HC-SR04

| HC-SR04 | ESP32   |
| ------- | ------- |
| VCC     | 5V      |
| GND     | GND     |
| TRIG    | GPIO 5  |
| ECHO    | GPIO 18 |

### LCD I2C

| LCD | ESP32   |
| --- | ------- |
| VCC | 5V      |
| GND | GND     |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

> ⚠️ En un montaje físico, el pin ECHO del HC-SR04 puede entregar aproximadamente 5 V. Debido a que el ESP32 utiliza lógica de 3.3 V, se recomienda utilizar un divisor de tensión antes de conectar ECHO al GPIO.

---

# 📦 18. Configuración de PlatformIO

Para la práctica HC-SR04 + LCD:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
    marcoschwartz/LiquidCrystal_I2C
```

La sección `lib_deps` permite declarar las librerías necesarias para el proyecto.

Cuando otro usuario clone el proyecto, PlatformIO podrá instalar las dependencias especificadas.

---

# 🧪 19. Simulación y hardware físico

Una de las ventajas de este entorno es que el mismo código puede utilizarse inicialmente en Wokwi y posteriormente en el ESP32 físico.

```text
              MISMO PROGRAMA
                     │
          ┌──────────┴──────────┐
          │                     │
          ▼                     ▼
        Wokwi                ESP32 físico
          │                     │
       Simulación             Hardware
```

Esto permite validar inicialmente:

* Código.
* Pines.
* Periféricos.
* Lógica de control.
* Comunicación.
* Visualización.

Antes de realizar el montaje físico.

---

# 📡 20. Monitor serial

Los proyectos podrán utilizar el monitor serial de PlatformIO.

Por ejemplo:

```cpp
Serial.begin(115200);
```

y:

```cpp
Serial.println("ESP32 funcionando");
```

La velocidad deberá configurarse a:

```text
115200 baudios
```

---

# 🐙 21. Git y GitHub

GitHub será utilizado para:

* Respaldar los proyectos.
* Llevar control de versiones.
* Compartir prácticas.
* Documentar proyectos.
* Facilitar la revisión de actividades.
* Mantener un historial de modificaciones.

---

# 📂 22. Archivos que deben subirse a GitHub

Se recomienda subir:

```text
README.md
platformio.ini
wokwi.toml
diagram.json
src/main.cpp
.gitignore
```

No se deben subir:

```text
.pio/
.vscode/
*.bin
*.elf
*.hex
```

---

# 🚫 23. Archivo `.gitignore`

Crear en la raíz del proyecto:

```text
.gitignore
```

Contenido recomendado:

```gitignore
# PlatformIO
.pio/
.piolibdeps/

# Visual Studio Code
.vscode/

# Archivos compilados
*.bin
*.elf
*.hex

# Sistema operativo
.DS_Store
Thumbs.db
```

De esta manera Git ignorará los archivos generados automáticamente.

---

# 🗂️ 24. Estructura recomendada para la materia

Se recomienda utilizar un repositorio general para **Sistemas Embebidos**:

```text
Sistemas_Embebidos/
│
├── README.md
├── .gitignore
│
├── 00_Instalacion_Entorno/
│   └── README.md
│
├── 01_GPIO/
│   ├── README.md
│   ├── platformio.ini
│   ├── wokwi.toml
│   ├── diagram.json
│   └── src/
│       └── main.cpp
│
├── 02_ADC/
│   ├── README.md
│   ├── platformio.ini
│   ├── wokwi.toml
│   ├── diagram.json
│   └── src/
│       └── main.cpp
│
├── 03_PWM/
│   ├── README.md
│   ├── platformio.ini
│   ├── wokwi.toml
│   ├── diagram.json
│   └── src/
│       └── main.cpp
│
├── 04_HCSR04_LCD/
│   ├── README.md
│   ├── platformio.ini
│   ├── wokwi.toml
│   ├── diagram.json
│   └── src/
│       └── main.cpp
│
└── 05_I2C/
    ├── README.md
    ├── platformio.ini
    ├── wokwi.toml
    ├── diagram.json
    └── src/
        └── main.cpp
```

---

# 📋 25. Checklist de instalación

Antes de comenzar las prácticas, verificar:

* [ ] Visual Studio Code instalado.
* [ ] PlatformIO IDE instalado.
* [ ] ESP32 reconocido por PlatformIO.
* [ ] Arduino Framework seleccionado.
* [ ] Wokwi for VS Code instalado.
* [ ] Cuenta Wokwi creada.
* [ ] Licencia Wokwi activada.
* [ ] Proyecto ESP32 creado.
* [ ] `main.cpp` funcionando.
* [ ] Proyecto compilado correctamente.
* [ ] `diagram.json` creado.
* [ ] `wokwi.toml` configurado.
* [ ] Simulación Wokwi funcionando.
* [ ] Git instalado.
* [ ] Cuenta GitHub disponible.
* [ ] `.gitignore` configurado.
* [ ] Proyecto respaldado en GitHub.

---

# ⚠️ 26. Problemas frecuentes

## PlatformIO no aparece

Verificar que la extensión:

```text
PlatformIO IDE
```

esté instalada y reiniciar VS Code.

---

## No compila el proyecto

Verificar:

```text
Board → DOIT ESP32 DEVKIT V1
Framework → Arduino
```

También revisar el archivo:

```text
platformio.ini
```

---

## Wokwi no inicia

Verificar:

1. Que la licencia esté activada.
2. Que exista `diagram.json`.
3. Que exista `wokwi.toml`.
4. Que el proyecto haya sido compilado previamente.
5. Que exista:

```text
.pio/build/esp32dev/firmware.bin
```

---

## Wokwi indica que no encuentra el firmware

Ejecutar nuevamente:

```bash
pio run
```

y comprobar que exista:

```text
.pio/build/esp32dev/firmware.bin
```

---

## La simulación utiliza un programa anterior

Volver a compilar:

```text
PlatformIO → Build
```

y posteriormente reiniciar la simulación.

---

# 🧠 27. Regla fundamental del curso

Durante el desarrollo de las prácticas se utilizará la siguiente filosofía:

> **PlatformIO administra el código y la compilación.**
>
> **Wokwi administra la simulación.**
>
> **GitHub administra el respaldo y control de versiones.**

De esta manera, cada práctica tendrá todos los elementos necesarios para ser:

```text
DESARROLLADA
      ↓
COMPILADA
      ↓
SIMULADA
      ↓
DOCUMENTADA
      ↓
RESPALDADA
      ↓
IMPLEMENTADA EN HARDWARE
```

---

# 🔗 28. Recursos oficiales

### Visual Studio Code

https://code.visualstudio.com/

### PlatformIO

https://platformio.org/

### Documentación PlatformIO

https://docs.platformio.org/

### Wokwi

https://wokwi.com/

### Wokwi para VS Code

https://docs.wokwi.com/vscode/

### GitHub

https://github.com/

---

# 🎓 29. Competencia desarrollada

Al finalizar esta etapa, el estudiante será capaz de:

> **Configurar un entorno de desarrollo para sistemas embebidos basado en ESP32, utilizando herramientas de programación, compilación, simulación, documentación y control de versiones, para desarrollar y validar aplicaciones antes de su implementación en hardware físico.**

---

## 👨‍🏫 Sistemas Embebidos

**ESP32 · PlatformIO · Arduino · Wokwi · GitHub**

**Desarrollo → Simulación → Validación → Implementación**
