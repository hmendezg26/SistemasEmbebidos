
#include <Arduino.h>
#include <ESP32Servo.h>

// Definicion de pines
const int PIR_PIN = 27;
const int SERVO_PIN = 18;

// Posiciones del servomotor
const int ANGULO_REPOSO = 0;
const int ANGULO_MOVIMIENTO = 90;

Servo servo;

int estadoPIR = LOW;
int ultimoEstadoPIR = LOW;

void setup() {
  Serial.begin(115200);

  pinMode(PIR_PIN, INPUT);

  // Configuracion del servomotor
  servo.setPeriodHertz(50);
  servo.attach(SERVO_PIN, 500, 2400);
  servo.write(ANGULO_REPOSO);

  Serial.println("Sistema PIR + Servo iniciado");
  Serial.println("Esperando movimiento...");
}

void loop() {
  estadoPIR = digitalRead(PIR_PIN);

  // Detectar cambios en el estado del PIR
  if (estadoPIR != ultimoEstadoPIR) {

    if (estadoPIR == HIGH) {
      servo.write(ANGULO_MOVIMIENTO);

      Serial.println("Movimiento detectado");
      Serial.println("Servo: 90 grados");
    } else {
      servo.write(ANGULO_REPOSO);

      Serial.println("Sin movimiento");
      Serial.println("Servo: 0 grados");
    }

    ultimoEstadoPIR = estadoPIR;
  }

  delay(50);
}
