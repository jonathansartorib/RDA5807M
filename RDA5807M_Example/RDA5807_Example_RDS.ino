/*
 * RDA5807M Example Sketch
 *
 * This example sketch demonstrates how to use the RDA5807M Library to interact with the RDA5807M FM radio module.
 * The sketch initializes the RDA5807M in West-FM mode (87-108MHz), waits for RDS data to become available,
 * and then displays the received station name and RDS block information via the serial port.
 *
 * HARDWARE SETUP:
 * Ensure you have the RRD-102 (V2.0) breakout board connected to a 3.3V Arduino's I2C interface.
 * If using a 5V Arduino, use an appropriate I2C level translator (as mentioned in the README).
 * Connect a suitable audio amplifier, as the RDA5807M's output is too weak for headphones.
 * You may use active speakers or a similar audio amplifier.
 * Make sure to connect a proper antenna to the breakout board's FM antenna pad, such as a 2ft (60cm) length of wire.
 * Decent results can also be obtained with a 6" breadboard jumper wire.
 */

// Due to a bug in Arduino, this needs to be included here too/first
#include <Wire.h>

// Add the RDA5807M Library to the sketch.
#include <RDA5807M.h>

RDA5807M radio;

void setup()
{
    Serial.begin(9600);
    radio.init();
    radio.setFrequency(100.0); // Set the desired frequency in MHz
    radio.setVolume(10);       // Set the desired volume (0-15)

    // Enable RDS
    radio.setRegister(0x02, radio.getRegister(0x02) | (1 << 15)); // Set the RDS_EN bit
}

void loop()
{
    radio.update();

    if (radio.getRegister(0x0A) & (1 << 15))
    {
        // The RDSR bit in register 0x0A has been set, indicating available RDS data
        Serial.println("RDS Signal Received!");
        Serial.print("Station: ");
        Serial.println(radio.getStationName());

        // Read and print RDS blocks (0x0C to 0x0F)
        for (int i = 0x0C; i <= 0x0F; i++)
        {
            Serial.print("RDS Block ");
            Serial.print(i - 0x0C);
            Serial.print(": 0x");
            Serial.println(radio.getRegister(i), HEX);
        }

        Serial.println();
    }
}
