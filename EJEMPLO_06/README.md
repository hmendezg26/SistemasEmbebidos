# 🌡️ Controlador de Temperatura ON-OFF con ESP32, Keypad 4×4, LCD I2C y DS18B20

### 🔬 Sistemas Embebidos | PlatformIO + Arduino Framework + Wokwi

![ESP32](https://img.shields.io/badge/ESP32-Microcontrolador-00979D?style=for-the-badge&logo=espressif&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Desarrollo-F5822A?style=for-the-badge&logo=platformio&logoColor=white)
![Arduino](https://img.shields.io/badge/Arduino-Framework-00878F?style=for-the-badge&logo=arduino&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulaci%C3%B3n-7B61FF?style=for-the-badge)
![DS18B20](https://img.shields.io/badge/DS18B20-Temperatura-blue?style=for-the-badge)

---

## 📌 1. Descripción del proyecto

El proyecto consiste en el desarrollo de un sistema embebido para la medición y el control de temperatura mediante un controlador de tipo **ON-OFF implementado en una tarjeta ESP32**.

El sistema utiliza un sensor digital DS18B20 para adquirir la temperatura, una pantalla LCD con interfaz I2C para visualizar las variables del proceso y un teclado matricial 4×4 para introducir los parámetros de operación.

El usuario podrá configurar la temperatura de referencia y la histéresis del controlador desde el teclado, sin necesidad de modificar el código fuente.

El controlador determina el estado de una salida digital destinada a accionar un elemento calefactor mediante una etapa de potencia adecuada.

### 🎯 Objetivo general

Desarrollar un sistema de control automático de temperatura basado en ESP32 que permita configurar los parámetros de un controlador ON-OFF mediante un keypad 4×4, medir la temperatura con un sensor DS18B20 y visualizar el estado del proceso en una pantalla LCD I2C.

### 🎯 Objetivos específicos

- 🌡️ Medir la temperatura mediante el sensor DS18B20.
- ⌨️ Configurar la temperatura de referencia desde el keypad.
- ⚙️ Establecer una banda de histéresis para evitar conmutaciones excesivas.
- 🖥️ Visualizar la temperatura medida, la referencia, la histéresis y el estado de la salida.
- 🔌 Activar o desactivar una salida digital de acuerdo con la lógica ON-OFF.
- 🧪 Simular el funcionamiento del sistema mediante Wokwi y desarrollar el código en PlatformIO.

---

## 🧰 2. Materiales y herramientas

| Elemento | Función |
|---|---|
| ESP32 DevKit V1 | Procesamiento y control |
| Keypad matricial 4×4 | Configuración de parámetros |
| LCD 16×2 con módulo I2C | Interfaz de usuario |
| Sensor DS18B20 | Medición de temperatura |
| Resistencia de 4.7 kΩ | Pull-up para la línea de datos del DS18B20 |
| LED o módulo de relevador | Representación de la salida de control |
| PlatformIO | Desarrollo y compilación |
| Wokwi | Simulación del sistema |

> ⚠️ En una implementación física, la carga de potencia debe conectarse mediante una etapa de accionamiento adecuada. No se debe alimentar directamente un calefactor desde un pin GPIO del ESP32.

---

## 🧠 3. Principio de funcionamiento

El sistema opera mediante un controlador ON-OFF con histéresis.

El usuario establece una temperatura de referencia \(T_{ref}\) y una histéresis \(H\). El programa calcula los límites de conmutación:

\[
T_{\text{inferior}}=T_{ref}-H
\]

\[
T_{\text{superior}}=T_{ref}+H
\]

Para un sistema de calefacción, la lógica de control es:

| Condición | Estado de la salida |
|---|---|
| \(T \leq T_{\text{inferior}}\) | 🔥 ON: activar calefacción |
| \(T \geq T_{\text{superior}}\) | 🛑 OFF: desactivar calefacción |
| \(T_{\text{inferior}} < T < T_{\text{superior}}\) | Mantener el estado anterior |

La histéresis genera una zona de operación en la que la salida conserva su estado, evitando cambios continuos cuando la temperatura se encuentra cerca de la referencia.

**Ejemplo de configuración:**

- Temperatura de referencia: 30 °C.
- Histéresis: 1 °C.
- Límite inferior: 29 °C.
- Límite superior: 31 °C.

En este ejemplo, la calefacción se activa cuando la temperatura baja a 29 °C o menos, y se desactiva cuando alcanza 31 °C o más. Entre ambos límites se mantiene el estado previo.

> 📘 Nota: la lógica anterior corresponde a un sistema de calefacción. Para refrigeración, la lógica debe invertirse.

---

## ⌨️ 4. Interfaz de usuario: keypad 4×4

El keypad permite modificar los parámetros de operación del controlador sin recompilar el programa.

La asignación de teclas puede implementarse de la siguiente manera:

| Tecla | Función |
|---|---|
| `A` | Seleccionar la configuración de temperatura de referencia |
| `B` | Seleccionar la configuración de histéresis |
| `C` | Borrar la entrada actual |
| `D` | Regresar a la pantalla principal o cancelar |
| `0–9` | Introducir valores numéricos |
| `*` | Introducir el punto decimal, si está implementado |
| `#` | Confirmar el valor introducido |

### 🔄 Secuencia de operación

1. Al encender el sistema, se inicializan el sensor, el LCD y el keypad.
2. La pantalla muestra la temperatura actual y los parámetros configurados.
3. El usuario presiona `A` para introducir la temperatura de referencia.
4. Introduce el valor numérico y presiona `#` para confirmarlo.
5. Presiona `B` para modificar la histéresis y confirma con `#`.
6. El programa valida los valores y actualiza los parámetros del controlador.
7. El sistema continúa midiendo la temperatura y controlando la salida automáticamente.

**Importante:** las teclas y funciones descritas representan la interfaz propuesta. Deben coincidir con la implementación concreta del código fuente.

---

## 🖥️ 5. Visualización en LCD I2C

La pantalla LCD 16×2 permite consultar el estado del proceso sin utilizar el monitor serial.

Una posible distribución es:

```text
T: 28.5C SP:30.0
H: 1.0C OUT: ON
```

Donde:

- `T`: temperatura medida.
- `SP`: temperatura de referencia o *setpoint*.
- `H`: histéresis configurada.
- `OUT`: estado de la salida de control.

La presentación exacta dependerá del formato implementado en el programa. Para una pantalla de 16 columnas, es necesario abreviar los textos y controlar la cantidad de caracteres.

---

## 🔌 6. Conexiones del sistema

Las siguientes conexiones son una propuesta de referencia para ESP32 DevKit V1. Deben coincidir con los pines definidos en `main.cpp` y `diagram.json`.

| Dispositivo | Pin del dispositivo | Pin ESP32 |
|---|---|---|
| LCD I2C | SDA | GPIO 21 |
| LCD I2C | SCL | GPIO 22 |
| Keypad 4×4 | Filas R1–R4 | GPIO 13, 12, 14, 27 |
| Keypad 4×4 | Columnas C1–C4 | GPIO 26, 25, 33, 32 |
| DS18B20 | DATA | GPIO 4 |
| DS18B20 | VCC | 3.3 V |
| DS18B20 | GND | GND |
| Resistencia pull-up | DATA a VCC | 4.7 kΩ |
| Salida de control | Señal de mando | GPIO 23 |

### ⚠️ Consideraciones eléctricas

- La alimentación y las conexiones a tierra deben ser compatibles con el ESP32.
- La línea DATA del DS18B20 requiere una resistencia pull-up, típicamente de 4.7 kΩ.
- Verifica que el módulo LCD I2C sea compatible con los niveles lógicos de 3.3 V del ESP32. Algunos módulos alimentados a 5 V elevan también las líneas SDA y SCL a 5 V.
- No conectes directamente cargas de potencia a la salida GPIO.
- La salida debe tener un estado seguro durante el arranque y cuando falle el sensor.

---

## 💻 7. Estructura del proyecto en PlatformIO

Una estructura recomendada es:

```text
Controlador_Temperatura_ON_OFF/
├── include/
│   └── README
├── lib/
├── src/
│   └── main.cpp
├── test/
├── diagram.json
├── wokwi.toml
├── platformio.ini
├── .gitignore
└── README.md
```

### 📄 Archivo `platformio.ini`

Ejemplo de configuración para una ESP32 DevKit V1:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino

monitor_speed = 115200

lib_deps =
    marcoschwartz/LiquidCrystal_I2C
    chris--a/Keypad
    milesburton/DallasTemperature
    paulstoffregen/OneWire
```

Las versiones de las bibliotecas pueden variar. Si utilizas una biblioteca LCD I2C diferente, ajusta las dependencias y la inicialización del display según su documentación.

---

## ▶️ 8. Compilación y simulación

### Paso 1. Abrir el proyecto

Abre la carpeta del proyecto en Visual Studio Code con PlatformIO instalado.

### Paso 2. Revisar las dependencias

Verifica que `platformio.ini` contenga las bibliotecas necesarias para el keypad, el LCD I2C y el DS18B20.

### Paso 3. Compilar

Ejecuta la tarea **PlatformIO: Build** o utiliza el botón de compilación de la extensión.

### Paso 4. Configurar Wokwi

Revisa que `diagram.json` incluya:

- La tarjeta ESP32.
- El keypad 4×4.
- El LCD I2C.
- El DS18B20.
- Las conexiones a los GPIO definidos en el programa.
- La salida de control representada mediante un LED u otro elemento de simulación.

Si utilizas Wokwi con PlatformIO, verifica que `wokwi.toml` apunte al firmware compilado y al archivo de diagrama correctos.

### Paso 5. Ejecutar las pruebas

Durante la simulación:

1. Cambia la temperatura del DS18B20.
2. Configura diferentes referencias con el keypad.
3. Modifica la histéresis.
4. Observa el cambio de estado de la salida.
5. Comprueba que la pantalla refleje los parámetros actualizados.

---

## 🧪 9. Pruebas funcionales

| Prueba | Procedimiento | Resultado esperado |
|---|---|---|
| Inicialización | Encender el sistema | Se inicializan LCD, keypad y sensor |
| Lectura | Modificar la temperatura simulada | Se actualiza la lectura |
| Configuración de referencia | Introducir un nuevo valor | Se actualiza el setpoint |
| Configuración de histéresis | Introducir un nuevo valor | Se actualizan los límites |
| Activación | Bajar la temperatura al límite inferior | La salida de calefacción se activa |
| Desactivación | Subir la temperatura al límite superior | La salida se desactiva |
| Histéresis | Mantener la temperatura dentro de la banda | Se conserva el estado anterior |
| Entrada inválida | Introducir un valor fuera de rango | El valor se rechaza o solicita nuevamente |
| Fallo del sensor | Simular una lectura inválida | La salida pasa al estado seguro definido |

Los resultados deben comprobarse con la implementación real. La tabla describe los criterios de aceptación, no resultados experimentales ya obtenidos.

---

## 📊 10. Conceptos de ingeniería aplicados

El proyecto permite estudiar:

- Sistemas embebidos basados en microcontroladores.
- Adquisición de variables físicas mediante sensores digitales.
- Interfaces de usuario con teclados matriciales.
- Comunicación I2C.
- Control automático ON-OFF.
- Histéresis y frecuencia de conmutación.
- Máquinas de estados y programación no bloqueante.
- Validación de parámetros de control.
- Simulación y pruebas funcionales.

### 🚀 Posibles mejoras

- Guardar los parámetros en memoria no volátil para conservarlos después de reiniciar.
- Añadir un modo manual para pruebas de laboratorio.
- Incorporar alarmas por sobretemperatura.
- Implementar detección de desconexión o fallo del DS18B20.
- Añadir un registro serial de temperatura, setpoint y salida.
- Comparar el comportamiento ON-OFF con un controlador PID.
- Incorporar un segundo sensor para supervisar otra zona térmica.

---

## 📚 11. Resultado esperado

Al finalizar el proyecto se espera disponer de un sistema de control de temperatura que permita:

- Medir y visualizar la temperatura en tiempo real.
- Modificar el setpoint y la histéresis desde el keypad.
- Activar y desactivar una salida de acuerdo con las condiciones de control.
- Verificar el comportamiento del sistema mediante simulación.
- Documentar el desarrollo con PlatformIO y Wokwi.

El sistema constituye una práctica integradora para la asignatura de Sistemas Embebidos, relacionando adquisición de datos, programación de microcontroladores, interfaces de usuario y fundamentos de control automático.

---

## 📌 12. Licencia y uso académico

Proyecto con fines educativos y de experimentación. Antes de utilizarlo para controlar un equipo térmico real, deben validarse los límites de temperatura, la etapa de potencia, el aislamiento eléctrico y las condiciones de seguridad aplicables.

**Autor:** Sistemas Embebidos  
**Plataforma:** ESP32  
**Entorno de desarrollo:** PlatformIO + Arduino Framework  
**Simulación:** Wokwi  
**Control:** ON-OFF con histéresis  
**Sensor:** DS18B20  
**Interfaz:** Keypad 4×4 + LCD I2C
