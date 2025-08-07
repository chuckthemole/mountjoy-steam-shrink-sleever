#include <Arduino.h>

// Relay pins
const int RELAY_PIN_1 = 8; // Relay 3 on shield
const int RELAY_PIN_2 = 9; // Relay 4 on shield

// Timing variables
unsigned long lastRelayToggle1 = 0;
unsigned long lastRelayToggle2 = 0;

const unsigned long interval1 = 1000; // 1 second for Relay 1
const unsigned long interval2 = 1500; // 1.5 seconds for Relay 2

bool relayState1 = false;
bool relayState2 = false;

void setup()
{
    Serial.begin(9600);

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);

    digitalWrite(RELAY_PIN_1, LOW); // Start both relays OFF
    digitalWrite(RELAY_PIN_2, LOW);

    Serial.println("Relay test started.");
}

void loop()
{
    unsigned long currentTime = millis();

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
