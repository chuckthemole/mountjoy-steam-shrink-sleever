#include <Arduino.h>

// Define the pin where the relay is connected
const int RELAY_PIN = 2; // Adjust this to your wiring

void setup()
{
    // Initialize the relay pin as output
    pinMode(RELAY_PIN, OUTPUT);

    // Start with the relay off
    digitalWrite(RELAY_PIN, LOW);

    // Debug message
    Serial.begin(9600);
    Serial.println("Relay control started.");
}

void loop()
{
    // Turn relay ON
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Relay ON");
    delay(1000); // 1 second

    // Turn relay OFF
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Relay OFF");
    delay(1000); // 1 second
}
