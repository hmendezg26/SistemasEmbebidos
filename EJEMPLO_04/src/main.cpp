#include <Arduino.h>
#include <ESP32Servo.h>

Servo servo;

#define SERVO_PIN 18

void setup() {

    Serial.begin(115200);

    servo.attach(SERVO_PIN);
    servo.write(0);
    Serial.println("ESP32 listo");
    Serial.println("Servo en 90 grados");
    delay(1000);
}

void loop() {

    for(int deg=0; deg<=180; deg+=5){
        servo.write(deg);
        delay(100);
    }
    
    servo.write(0);
    delay(1000);

}