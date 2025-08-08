#include <Arduino.h>

// Relay pins
const int RELAY_PIN_1 = 8;  // Relay 3 on shield
const int RELAY_PIN_2 = 12; // Relay 4 on shield

// Potentiometer pin
const int POT_PIN = A0;

// Timing variables
unsigned long lastRelayToggle1 = 0;
unsigned long lastRelayToggle2 = 0;

unsigned long interval1 = 1000; // Will be adjusted by potentiometer
unsigned long interval2 = 1500; // Will also be adjusted

bool relayState1 = false;
bool relayState2 = false;

void setup()
{
    Serial.begin(9600);

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);

    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_2, LOW);

    pinMode(POT_PIN, INPUT);

    Serial.println("Relay test with potentiometer speed control started.");
}

void loop()
{
    unsigned long currentTime = millis();

    // Read potentiometer and map to interval (100ms to 2000ms)
    int potValue = analogRead(POT_PIN);
    interval1 = map(potValue, 0, 1023, 100, 2000);
    interval2 = map(potValue, 0, 1023, 150, 3000); // you can tweak these separately

    // Print mapped value occasionally
    static unsigned long lastPrint = 0;
    if (currentTime - lastPrint >= 1000)
    {
        lastPrint = currentTime;
        Serial.print("Potentiometer value: ");
        Serial.print(potValue);
        Serial.print(" | Interval1: ");
        Serial.print(interval1);
        Serial.print(" ms | Interval2: ");
        Serial.print(interval2);
        Serial.println(" ms");
    }

    // Toggle Relay 1
    if (currentTime - lastRelayToggle1 >= interval1)
    {
        lastRelayToggle1 = currentTime;
        relayState1 = !relayState1;
        digitalWrite(RELAY_PIN_1, relayState1 ? HIGH : LOW);
        Serial.print("Relay 1 ");
        Serial.println(relayState1 ? "ON" : "OFF");
    }

    // Toggle Relay 2
    if (currentTime - lastRelayToggle2 >= interval2)
    {
        lastRelayToggle2 = currentTime;
        relayState2 = !relayState2;
        digitalWrite(RELAY_PIN_2, relayState2 ? HIGH : LOW);
        Serial.print("Relay 2 ");
        Serial.println(relayState2 ? "ON" : "OFF");
    }
}
