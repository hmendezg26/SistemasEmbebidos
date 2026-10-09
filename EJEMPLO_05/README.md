# 🌡️ Monitor de Voltaje y Temperatura con ESP32

### ⚡ Adquisición de señales analógicas y visualización en LCD 16×2 mediante I²C

![ESP32](https://img.shields.io/badge/ESP32-Microcontrolador-E7352C?style=for-the-badge\&logo=espressif\&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-IDE-orange?style=for-the-badge\&logo=platformio\&logoColor=white)
![Arduino](https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge\&logo=arduino\&logoColor=white)
![Wokwi](https://img.shields.io/badge/Simulaci%C3%B3n-Wokwi-4CAF50?style=for-the-badge)
![License](https://img.shields.io/badge/Licencia-Educativa-blue?style=for-the-badge)

## 📌 Descripción del proyecto

Este proyecto consiste en desarrollar un sistema de adquisición de señales analógicas utilizando una tarjeta **ESP32**, dos potenciómetros y un termistor NTC para medir variaciones de voltaje y estimar la temperatura.

Los datos adquiridos se muestran en una pantalla LCD de 16 columnas por 2 filas, utilizando el protocolo de comunicación **I²C**. Adicionalmente, las lecturas se envían al monitor serie para facilitar la supervisión y el análisis de las variables.

El sistema puede implementarse y probarse mediante **Wokwi**, integrándolo con Visual Studio Code y PlatformIO.

## 🎯 Objetivo general

Implementar un sistema embebido basado en ESP32 capaz de adquirir dos señales analógicas, estimar la temperatura mediante un termistor NTC y visualizar las variables medidas en una pantalla LCD con comunicación I²C.

### 🎓 Objetivos específicos

* 🔌 Configurar entradas analógicas de la ESP32 para adquirir señales eléctricas.
* 🎚️ Medir el voltaje de salida de dos potenciómetros.
* 🌡️ Estimar la temperatura a partir de la resistencia eléctrica de un termistor NTC.
* 🧮 Aplicar la ecuación Beta para convertir la resistencia del termistor en temperatura.
* 🖥️ Implementar la comunicación I²C para visualizar los datos en una pantalla LCD.
* 📡 Enviar las mediciones al monitor serie para su supervisión.
* 🧪 Validar el comportamiento del sistema mediante simulación.

## 🧰 Materiales y herramientas

| Componente                   | Función                                     |
| ---------------------------- | ------------------------------------------- |
| 🔴 ESP32 DevKit V1           | Adquisición y procesamiento de señales      |
| 🎚️ Potenciómetro 1          | Generación de una señal analógica variable  |
| 🎚️ Potenciómetro 2          | Generación de una segunda señal analógica   |
| 🌡️ Termistor NTC de 10 kΩ   | Detección de cambios de temperatura         |
| 🟫 Resistencia fija de 10 kΩ | Formación del divisor de voltaje con el NTC |
| 🖥️ LCD 16×2 con módulo I²C  | Visualización de las mediciones             |
| 🔗 Cables de conexión        | Interconexión de los componentes            |
| 💻 Visual Studio Code        | Entorno de desarrollo                       |
| ⚙️ PlatformIO                | Compilación y gestión del proyecto          |
| 🧪 Wokwi                     | Simulación del circuito electrónico         |

## 🔌 Diagrama de conexiones

### 📍 Asignación de pines de la ESP32

| Dispositivo                  | Pin del dispositivo | Pin ESP32 |
| ---------------------------- | ------------------- | --------- |
| Potenciómetro 1              | Terminal central    | GPIO 34   |
| Potenciómetro 2              | Terminal central    | GPIO 35   |
| Divisor de voltaje NTC       | Punto medio         | GPIO 32   |
| LCD I²C                      | SDA                 | GPIO 21   |
| LCD I²C                      | SCL                 | GPIO 22   |
| Potenciómetros y divisor NTC | Alimentación        | 3.3 V     |
| Todos los dispositivos       | Tierra              | GND común |

**⚠️ Importante:** conecta cada potenciómetro entre 3.3 V y GND, utilizando su terminal central como salida analógica.

### 🌡️ Conexión del termistor NTC

El termistor y la resistencia fija forman un divisor de voltaje:

```text
       3.3 V
          |
         NTC
          |
          +---------- GPIO 32
          |
       10 kΩ
          |
         GND
```

En esta configuración, la resistencia del NTC disminuye cuando aumenta la temperatura. Como consecuencia, aumenta el voltaje en el punto de medición.

> ⚠️ La conexión del divisor debe coincidir con la ecuación implementada en el programa. Si se invierte el orden del NTC y la resistencia fija, será necesario modificar el cálculo.

## ⚙️ Fundamento teórico

### 1. 🎚️ Conversión analógica a digital

La ESP32 utiliza su convertidor analógico-digital (ADC) para leer las señales de los potenciómetros y del divisor de voltaje.

Para una resolución nominal de 12 bits, las lecturas se encuentran entre 0 y 4095.

El voltaje se estima mediante:

$$
V_{\text{in}}=\frac{ADC}{4095}\,V_{\text{ref}}
$$

Donde:

* \(V_{\text{in}}\): voltaje estimado de entrada.
* \(ADC\): lectura digital obtenida.
* \(V_{\text{ref}}\): voltaje de referencia nominal, considerado de 3.3 V en este proyecto.

**Nota:** la conversión es nominal; la referencia efectiva, la atenuación y la no linealidad del ADC pueden introducir errores.

### 2. 🌡️ Medición de temperatura con NTC

Un termistor NTC (Negative Temperature Coefficient) es un componente cuya resistencia eléctrica disminuye cuando aumenta su temperatura.

Para la conexión utilizada:

$$
R_{NTC}=R_F\left(\frac{4095}{ADC}-1\right)
$$

Donde:

* \(R_{NTC}\): resistencia estimada del termistor.
* \(R_F\): resistencia fija de 10 kΩ.
* \(ADC\): lectura digital del punto medio del divisor.

### 3. 🧮 Ecuación Beta

La temperatura se estima a partir de la resistencia del termistor mediante:

$$
T=\left[
\frac{1}{T_0}+
\frac{1}{\beta}\ln\left(\frac{R_{NTC}}{R_0}\right)
\right]^{-1}
$$

La temperatura en grados Celsius se obtiene con:

$$
T_{^\circ C}=T_K-273.15
$$

Parámetros considerados:

| Parámetro |            Valor |
| --------- | ---------------: |
| \(R_0\)   |            10 kΩ |
| \(T_0\)   | 298.15 K (25 °C) |
| \(\beta\) |           3950 K |
| \(R_F\)   |            10 kΩ |

Estos valores son de referencia y deben ajustarse a las características del termistor utilizado.

## 🖥️ Visualización de datos

La pantalla LCD presenta las mediciones de los dos potenciómetros y la temperatura estimada.

Ejemplo ilustrativo:

```text
┌────────────────┐
│P1:1.25 P2:2.40  │
│NTC: 25.0°C     │
└────────────────┘
```

Las lecturas se actualizan periódicamente y también se envían al monitor serie a una velocidad de **115200 baudios**.

### 📊 Variables monitoreadas

| Variable                    | Unidad | Origen  |
| --------------------------- | ------ | ------- |
| Voltaje del potenciómetro 1 | V      | GPIO 34 |
| Voltaje del potenciómetro 2 | V      | GPIO 35 |
| Temperatura estimada        | °C     | GPIO 32 |

*Los valores mostrados son únicamente ejemplos; no representan mediciones experimentales.*

## 🚀 Instalación y ejecución

### 1. 💻 Preparar el entorno

Instala las siguientes herramientas:

* [Visual Studio Code](https://code.visualstudio.com/)
* [Extensión PlatformIO IDE](https://platformio.org/install/ide?install=vscode)
* [Simulador Wokwi](https://wokwi.com/)

### 2. 📁 Crear el proyecto

En PlatformIO:

1. Selecciona **New Project**.
2. Elige la tarjeta **ESP32 DevKit V1**.
3. Selecciona el framework **Arduino**.
4. Define el nombre del proyecto.
5. Espera a que se genere la estructura de archivos.

### 3. 📦 Instalar la biblioteca LCD

Agrega la siguiente dependencia en `platformio.ini`:

```ini
lib_deps =
    marcoschwartz/LiquidCrystal_I2C
```

Ejemplo de configuración:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
monitor_speed = 115200

lib_deps =
    marcoschwartz/LiquidCrystal_I2C
```

### 4. 📝 Agregar el programa

Copia el código del sistema en:

```text
src/main.cpp
```

### 5. 🧪 Simular el circuito

1. Construye el circuito con la ESP32, los dos potenciómetros, el NTC, la resistencia y el LCD.
2. Verifica que las conexiones correspondan a la tabla de pines.
3. Ejecuta la simulación.
4. Modifica los potenciómetros y la temperatura del NTC.
5. Observa los cambios en el LCD y en el monitor serie.

**Nota:** si utilizas Wokwi con PlatformIO, configura la integración y el archivo `diagram.json` según el método de simulación que hayas instalado.

## 🧪 Pruebas de funcionamiento

| Prueba | Acción                           | Resultado esperado                        |
| ------ | -------------------------------- | ----------------------------------------- |
| 1️⃣    | Girar el potenciómetro 1         | Cambia el voltaje P1                      |
| 2️⃣    | Girar el potenciómetro 2         | Cambia el voltaje P2                      |
| 3️⃣    | Aumentar la temperatura del NTC  | Aumenta la temperatura calculada          |
| 4️⃣    | Disminuir la temperatura del NTC | Disminuye la temperatura calculada        |
| 5️⃣    | Observar la pantalla LCD         | Se actualizan las tres variables          |
| 6️⃣    | Abrir el monitor serie           | Se muestran las mediciones periódicamente |

## 🛠️ Solución de problemas

| Problema                       | Posible causa                                   | Solución                                     |
| ------------------------------ | ----------------------------------------------- | -------------------------------------------- |
| LCD sin texto                  | Dirección I²C incorrecta                        | Verificar si la dirección es `0x27` o `0x3F` |
| Temperatura incorrecta         | Parámetros Beta o resistencia nominal distintos | Revisar la ficha técnica del NTC             |
| Lecturas de voltaje inestables | Ruido o conexiones deficientes                  | Revisar el cableado y la alimentación        |
| Temperatura inválida           | Lectura ADC cercana a los extremos              | Verificar el divisor y las conexiones        |
| No aparece información serie   | Puerto o velocidad incorrectos                  | Configurar 115200 baudios                    |
| No compila el proyecto         | Biblioteca ausente o incompatible               | Revisar `platformio.ini`                     |

## 📚 Competencias desarrolladas

* ⚡ Electrónica analógica y divisores de voltaje.
* 🔌 Configuración de entradas ADC en microcontroladores.
* 🌡️ Instrumentación y medición de temperatura.
* 🧮 Conversión de señales y aplicación de modelos matemáticos.
* 🔗 Comunicación serial e interfaz I²C.
* 💻 Programación de sistemas embebidos en C++.
* 🧪 Simulación y validación de circuitos electrónicos.

## 🔮 Posibles mejoras

* 📈 Graficar las variables en tiempo real desde una computadora.
* 📲 Transmitir las mediciones por Bluetooth o Wi-Fi.
* 💾 Registrar las lecturas en archivos CSV.
* 🚨 Implementar alarmas cuando la temperatura supere un umbral.
* 🎛️ Incorporar un sistema de control automático de temperatura.
* 📏 Calibrar el NTC para mejorar la precisión de las mediciones.

## 👨‍💻 Autoría y uso educativo

**Proyecto académico de Sistemas Embebidos.**

Desarrollado para prácticas de adquisición de datos, procesamiento de señales analógicas, instrumentación y visualización de variables con ESP32.

---

⭐ *Si este proyecto te resulta útil, puedes adaptarlo para tus prácticas de electrónica, instrumentación y control.*
