# 🎃 Animatrónico de Halloween con ESP32
### 👻 Detección de movimiento, reproducción de audio, ojos LED y boca móvil

![ESP32](https://img.shields.io/badge/ESP32-Sistemas_Embebidos-red?style=for-the-badge&logo=espressif&logoColor=white)
![PlatformIO](https://img.shields.io/badge/PlatformIO-Desarrollo-orange?style=for-the-badge&logo=platformio&logoColor=white)
![Wokwi](https://img.shields.io/badge/Wokwi-Simulaci%C3%B3n-purple?style=for-the-badge)
![Halloween](https://img.shields.io/badge/Halloween-Animatr%C3%B3nico-black?style=for-the-badge)

## 🧟 1. Descripción del proyecto

El objetivo de este proyecto es desarrollar un **animatrónico interactivo con temática de Halloween**, utilizando un ESP32 como unidad de control. El sistema detecta la presencia de personas mediante un sensor PIR y activa una secuencia de efectos electrónicos y mecánicos para generar una experiencia de terror.

Al detectar movimiento, el animatrónico reproduce sonidos o frases de terror mediante un reproductor MP3, enciende los LED que representan los ojos y mueve la boca mediante un servomotor. Cuando termina la secuencia de activación, el sistema regresa al estado de reposo.

El proyecto integra programación de microcontroladores, sensores digitales, actuadores, reproducción de audio y control de secuencias.

## 🎯 2. Objetivo general

Diseñar e implementar un animatrónico de Halloween controlado mediante ESP32, capaz de reaccionar ante la presencia de personas mediante la integración de detección de movimiento, reproducción de audio, efectos luminosos y movimiento mecánico de la boca.

## ⚙️ 3. Funcionamiento del sistema

El sistema opera mediante la siguiente secuencia:

1. **😴 Estado de reposo:** el animatrónico espera la detección de movimiento.
2. **👁️ Detección:** el sensor PIR identifica la presencia de una persona.
3. **🔴 Activación de los ojos:** los LED se encienden o parpadean para generar un efecto visual.
4. **🔊 Reproducción de audio:** el módulo MP3 reproduce un sonido, una risa o una frase de terror.
5. **💀 Movimiento de la boca:** el servomotor modifica la posición de la boca para simular que el personaje habla o grita.
6. **🌑 Finalización:** los ojos se apagan, la boca regresa a su posición inicial y el sistema queda listo para una nueva activación.

> **Nota:** el movimiento de la boca se coordina con la duración del audio mediante una secuencia programada. Esto produce una sincronización visual aproximada; no constituye sincronización fonética real.

## 🧰 4. Materiales y componentes

| Cantidad | Componente | Función |
|---:|---|---|
| 1 | ESP32 DevKit V1 | Unidad de control principal |
| 1 | Sensor PIR HC-SR501 | Detección de movimiento |
| 1 | Servomotor SG90 | Movimiento de la boca |
| 2 | LED rojos o de otro color | Simulación de los ojos |
| 2 | Resistencias de 220–330 Ω | Limitación de corriente de los LED |
| 1 | Módulo reproductor MP3, por ejemplo DFPlayer Mini | Reproducción de audio |
| 1 | Tarjeta microSD compatible | Almacenamiento de sonidos |
| 1 | Altavoz compatible con el reproductor | Salida de audio |
| Según necesidad | Protoboard y cables Dupont | Conexiones eléctricas |
| 1 | Fuente regulada adecuada | Alimentación del sistema |

**Consideraciones:** el ESP32 puede simular parte del comportamiento en Wokwi, pero la disponibilidad del reproductor MP3 depende del componente virtual utilizado. El audio real requiere un módulo compatible, altavoz y archivos de sonido.

## 🔌 5. Arquitectura del sistema

```text
          SENSOR PIR
               │
               ▼
        ┌─────────────┐
        │    ESP32    │
        │ Controlador │
        └─────────────┘
          │    │    │
          │    │    └──────────────┐
          │    │                   │
          ▼    ▼                   ▼
       SERV0   LED             REPRODUCTOR
       BOCA   OJOS                MP3
                                  │
                                  ▼
                               ALTAVOZ
```

El ESP32 recibe la señal digital del PIR y ejecuta una secuencia de control para los actuadores y el reproductor de audio.

## 🔧 6. Propuesta de asignación de pines

| Dispositivo | Señal | Pin ESP32 |
|---|---|---|
| PIR HC-SR501 | OUT | GPIO 27 |
| Servomotor | PWM | GPIO 18 |
| LED del ojo izquierdo | Ánodo mediante resistencia | GPIO 25 |
| LED del ojo derecho | Ánodo mediante resistencia | GPIO 26 |
| DFPlayer Mini | RX del módulo | GPIO 17 (TX2 del ESP32) |
| DFPlayer Mini | TX del módulo | GPIO 16 (RX2 del ESP32) |
| Componentes | GND | GND común |

Los pines propuestos pueden modificarse según el cableado definitivo. En la conexión serial del DFPlayer Mini, el TX del ESP32 se conecta al RX del reproductor y el TX del reproductor al RX del ESP32. Verifica los niveles eléctricos recomendados por el módulo.

## 🔊 7. Preparación de los sonidos

Para utilizar el DFPlayer Mini:

1. Formatea una tarjeta microSD con un sistema de archivos compatible.
2. Crea una carpeta llamada `mp3`.
3. Guarda los archivos con nombres numéricos, por ejemplo:

```text
/mp3/0001.mp3
/mp3/0002.mp3
/mp3/0003.mp3
```

4. Utiliza audios breves, como una risa, un grito o una frase de terror.
5. Verifica que el formato de audio y la tarjeta sean compatibles con el módulo.

Los nombres numéricos facilitan la selección de pistas desde el programa.

## 🧠 8. Estrategia de programación

El programa se puede organizar en las siguientes funciones:

- `leerPIR()`: consulta el estado del sensor.
- `activarOjos()`: enciende o hace parpadear los LED.
- `reproducirAudio()`: inicia la pista de terror seleccionada.
- `moverBoca()`: alterna entre las posiciones de boca abierta y cerrada.
- `finalizarSecuencia()`: detiene los efectos y devuelve el sistema al reposo.

Se recomienda utilizar una máquina de estados para distinguir entre reposo, activación, reproducción y finalización. Esto permite gestionar los efectos de forma ordenada y facilita la incorporación de nuevas funciones.

## 🧪 9. Pruebas y validación

- [ ] El sensor PIR detecta movimiento.
- [ ] El sistema se activa únicamente cuando corresponde.
- [ ] Los LED simulan correctamente los ojos del personaje.
- [ ] El reproductor reproduce el archivo de audio seleccionado.
- [ ] El servomotor mueve la boca sin bloquearse.
- [ ] La boca se mueve durante la reproducción del sonido.
- [ ] El sistema vuelve a reposo al finalizar la secuencia.
- [ ] La alimentación soporta el funcionamiento conjunto de los componentes.

## ⚠️ 10. Recomendaciones de seguridad

- No alimentes el servomotor directamente desde un GPIO.
- Utiliza una fuente de alimentación adecuada para el servo y el reproductor.
- Comparte GND entre la fuente externa y el ESP32.
- Coloca resistencias limitadoras en serie con los LED.
- Asegura mecánicamente el servo para evitar que el mecanismo de la boca se atasque.
- Mantén los cables y componentes electrónicos protegidos dentro de la estructura del animatrónico.

## 🚀 11. Posibles mejoras

- Incorporar un segundo servomotor para mover la cabeza.
- Agregar un sensor de distancia para detectar personas a una distancia determinada.
- Implementar varios sonidos aleatorios.
- Ajustar los patrones de parpadeo de los ojos.
- Controlar la intensidad y duración de los efectos.
- Utilizar una máquina de estados no bloqueante para coordinar audio, luces y movimiento.
- Añadir un botón para activar manualmente el animatrónico.

## 📚 12. Aplicaciones didácticas

Este proyecto permite aplicar conocimientos de:

- Sistemas embebidos con ESP32.
- Programación en C++ y Arduino.
- Lectura de sensores digitales.
- Generación de señales PWM para servomotores.
- Comunicación serial UART.
- Control de salidas digitales.
- Integración de hardware y software.
- Diseño de secuencias y máquinas de estados.

## 🏁 13. Resultado esperado

Un animatrónico de Halloween capaz de detectar la presencia de una persona y responder mediante una combinación de movimiento mecánico, efectos luminosos y sonidos de terror, integrando los principios fundamentales de los sistemas embebidos y la automatización interactiva.

**Proyecto académico:** Sistemas Embebidos  
**Plataforma de desarrollo:** ESP32 + PlatformIO  
**Entorno de simulación:** Wokwi  
**Aplicación:** Animatrónico interactivo para Halloween
