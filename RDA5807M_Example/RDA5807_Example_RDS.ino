/*
 * RDA5807M Example Sketch
 *
 * This example sketch demonstrates how to use the RDA5807M Library to interact with the RDA5807M FM radio module.
 * The sketch initializes the RDA5807M in West-FM mode (87-108MHz), reads the current frequency, waits for RDS data to become available,
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

#include <RDA5807M.h>

RDA5807M radio;

void setup()
{
    // Initialize communication with the RDA5807M module
    radio.begin(RDA5807M_BAND_WEST); // Choose the west band

    // Enable RDS data reception
    radio.updateRegister(RDA5807M_REG_RDS, RDA5807M_FLG_RDS);

    // Initialize the serial monitor
    Serial.begin(9600);
}

void loop()
{
    // Read the current frequency
    word frequency = radio.getFrequency(); // Frequency in 10 kHz units

    // Tune the radio to the current frequency
    radio.setFrequency(frequency);

    // Read RDS data blocks A and B
    word rdsA, rdsB;
    radio.getRegisterBulk(2, &rdsA);
    radio.updateRegister(RDA5807M_REG_RDS, RDA5807M_FLG_RDS); // Clear the RDS_READY bit

    // Decode RDS data (as before)

    // Display the current frequency and RDS data
    Serial.print("Current Frequency: ");
    Serial.print(frequency);
    Serial.println(" kHz");
    Serial.print("Group Type: ");
    Serial.println(groupType);
    Serial.print("Version Code: ");
    Serial.println(versionCode);
    Serial.print("Traffic Flag: ");
    Serial.println(trafficFlag);
    Serial.print("Program Type: ");
    Serial.println(programType);
    Serial.print("Text Segment: ");
    Serial.println(textSegment);

    // Wait for some time before reading again
    delay(1000);
}
