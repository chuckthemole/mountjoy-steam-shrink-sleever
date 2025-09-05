#include <Arduino.h>

// Relay pins
const int RELAY_PIN_1 = 8;  // Relay controlling piston UP
const int RELAY_PIN_2 = 12; // Relay helping piston DOWN (opposite of Relay 1)

// Potentiometer pin
const int POT_PIN = A0;

// Timing ranges
const unsigned long FIXED_UP_TIME = 4000; // 4 seconds UP
const int MIN_DOWN_TIME = 3000;           // 3 seconds minimum DOWN
const int MAX_DOWN_TIME = 20000;          // 20 seconds maximum DOWN

// State variables
unsigned long lastRelayToggle1 = 0;

unsigned long intervalUp = FIXED_UP_TIME;   // fixed UP time
unsigned long intervalDown = MIN_DOWN_TIME; // variable DOWN time
unsigned long currentInterval = FIXED_UP_TIME;

bool relayState1 = false; // false = piston down, true = piston up

void setup()
{
    Serial.begin(9600);

    pinMode(RELAY_PIN_1, OUTPUT);
    pinMode(RELAY_PIN_2, OUTPUT);

    digitalWrite(RELAY_PIN_1, LOW);
    digitalWrite(RELAY_PIN_2, HIGH); // start with piston DOWN

    pinMode(POT_PIN, INPUT);

    Serial.println("Piston control: fixed UP (4s), variable DOWN (pot).");
}

void loop()
{
    unsigned long currentTime = millis();

    // Read potentiometer and map to DOWN interval
    int potValue = analogRead(POT_PIN);
    intervalDown = map(potValue, 0, 1023, MIN_DOWN_TIME, MAX_DOWN_TIME);

    // Debug info
    static unsigned long lastPrint = 0;
    if (currentTime - lastPrint >= 1000)
    {
        lastPrint = currentTime;
        Serial.print("Pot: ");
        Serial.print(potValue);
        Serial.print(" | UP=");
        Serial.print(intervalUp);
        Serial.print(" ms, DOWN=");
        Serial.print(intervalDown);
        Serial.println(" ms");
    }

    // ===== Relay 1 & 2 control =====
    if (currentTime - lastRelayToggle1 >= currentInterval)
    {
        lastRelayToggle1 = currentTime;
        relayState1 = !relayState1;

        if (relayState1)
        {
            // Going UP (fixed 4s ON)
            digitalWrite(RELAY_PIN_1, HIGH);
            digitalWrite(RELAY_PIN_2, LOW); // opposite
            currentInterval = intervalUp;

            Serial.println("Relay 1 -> ON (piston UP for 4s)");
            Serial.println("Relay 2 -> OFF");
        }
        else
        {
            // Going DOWN (variable OFF time)
            digitalWrite(RELAY_PIN_1, LOW);
            digitalWrite(RELAY_PIN_2, HIGH); // opposite
            currentInterval = intervalDown;

            Serial.print("Relay 1 -> OFF (piston DOWN for ");
            Serial.print(intervalDown / 1000.0, 1);
            Serial.println("s)");
            Serial.println("Relay 2 -> ON");
        }
    }
}
