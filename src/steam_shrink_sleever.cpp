#include <Arduino.h>

// Relay pin
const int RELAY_PIN = 2; // Adjust as needed

// Switch pins
#define RUN_PIN 3
#define JOG_PIN 4
#define STOP_PIN 5

// Timing variables
const unsigned long reportInterval = 5000; // 5 seconds for switch reporting
unsigned long lastReportTime = 0;

enum State
{
    STOP,
    RUN,
    JOG,
    UNKNOWN
};

void setup()
{
    Serial.begin(9600);

    pinMode(RELAY_PIN, OUTPUT);
    digitalWrite(RELAY_PIN, LOW); // Start relay OFF

    pinMode(RUN_PIN, INPUT_PULLUP);
    pinMode(JOG_PIN, INPUT_PULLUP);
    pinMode(STOP_PIN, INPUT_PULLUP);

    Serial.println("Relay control and switch state monitor started.");
}

State readSwitchState()
{
    if (digitalRead(STOP_PIN) == LOW)
    {
        return STOP;
    }
    else if (digitalRead(RUN_PIN) == LOW)
    {
        return RUN;
    }
    else if (digitalRead(JOG_PIN) == LOW)
    {
        return JOG;
    }
    return UNKNOWN;
}

void loop()
{
    static bool relayState = false;
    static unsigned long lastRelayToggle = 0;
    unsigned long currentTime = millis();

    // Relay toggle every 1 second
    if (currentTime - lastRelayToggle >= 1000)
    {
        lastRelayToggle = currentTime;
        relayState = !relayState;
        digitalWrite(RELAY_PIN, relayState ? HIGH : LOW);
        Serial.print("Relay ");
        Serial.println(relayState ? "ON" : "OFF");
    }

    // Switch state report every 5 seconds
    if (currentTime - lastReportTime >= reportInterval)
    {
        lastReportTime = currentTime;

        State currentState = readSwitchState();

        Serial.print("Switch state: ");
        switch (currentState)
        {
        case RUN:
            Serial.println("RUN");
            break;
        case JOG:
            Serial.println("JOG");
            break;
        case STOP:
            Serial.println("STOP");
            break;
        default:
            Serial.println("UNKNOWN (no active input)");
            break;
        }
    }
}
