#include <Arduino.h>
#include <knx.h>

#define PROG_LED_PIN 13
#define PROG_LED_PIN_ACTIVE_ON HIGH
#define PROG_BUTTON_PIN 11
#define PROG_BUTTON_PIN_INTERRUPT_ON FALLING
#define SAVE_INTERRUPT_PIN 8
#define INFO_LED_PIN 38
#define INFO_LED_PIN_ACTIVE_ON HIGH

#define goCurrent knx.getGroupObject(0)

void setup() {
  SerialUSB.begin(9600);
  while(!SerialUSB) {}
  SerialUSB.println("Serial bereit");
  pinMode(INFO_LED_PIN, OUTPUT);
  pinMode(PROG_BUTTON_PIN, INPUT);

  ArduinoPlatform::SerialDebug = &SerialUSB;

  SerialUSB.println("Reading");
  knx.readMemory();
  SerialUSB.println("Read memory");

  if(knx.configured()) {
    SerialUSB.println("KNX Gerät wurde konfiguriert");
  }

  knx.ledPin(PROG_LED_PIN);
  knx.ledPinActiveOn(PROG_LED_PIN_ACTIVE_ON);
  knx.buttonPin(PROG_BUTTON_PIN);
  knx.buttonPinInterruptOn(PROG_BUTTON_PIN_INTERRUPT_ON);

  knx.start();
}

void loop() {
  knx.loop();

    // only run the application code if the device was configured with ETS
    if (!knx.configured())
        return;

  
  digitalWrite(INFO_LED_PIN, HIGH);
  delay(1000);
  digitalWrite(INFO_LED_PIN, LOW);
  delay(1000);
}