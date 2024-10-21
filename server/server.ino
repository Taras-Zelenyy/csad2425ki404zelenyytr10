#include <Arduino.h>

String message = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
}

void loop() {
  if (Serial.available() > 0) {
    message = Serial.readString();

    if (message == "Привіт Arduino!"){
      Serial.println("Привіт User!");
    }
    else
    {
      Serial.println("Мені не відома така команда");
    }
  }
}
