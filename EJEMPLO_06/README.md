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
| ESP32 DevKit V1 | Proces
