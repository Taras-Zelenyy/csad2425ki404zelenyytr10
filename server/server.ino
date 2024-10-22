#include <Arduino.h>

String message = "";

void setup() {
  Serial.begin(9600);
  while (!Serial) { }
}

void loop() {
  if (Serial.available() > 0) {
    message = Serial.readString();

    if (message == "Hello Arduino!"){
      Serial.println("Hello User!");
    }
    else
    {
      Serial.println("I don't know of any such command");
    }
  }
}
