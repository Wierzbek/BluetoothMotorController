#include <VescUart.h>
/** bl */
#include "Arduino.h"
#include <SoftwareSerial.h>

const byte rxPin = 9;
const byte txPin = 8;
SoftwareSerial BTSerial(rxPin, txPin);


/** Initiate VescUart class */
VescUart UART;

// Global variables
float current = 0.0;
int last = 99;
char data = '0';
bool isValid = true;

// BTconnected will = false when not connected and true when connected
boolean BTconnected = false;
// connect the STATE pin to Arduino pin D4
const byte BTpin = 4;

// Setup - called only once
void setup() {
    // set the BTpin for input
    pinMode(BTpin, INPUT);  

    // define pin modes for tx, rx:
    pinMode(rxPin, INPUT);
    pinMode(txPin, OUTPUT);
    BTSerial.begin(19200);
    /** Setup UART port (Serial1 on Atmega32u4) */
    Serial.begin(19200);

    // wait until the HC-05 has made a connection
    while (!BTconnected)
    {
      if ( digitalRead(BTpin)==HIGH)  { BTconnected = true;};
    } 
    Serial.println("HC-05 is now connected");

    while (!Serial) {;}

    /** Define which ports to use as UART */
    UART.setSerialPort(&Serial);

}

// Main Loop
void loop() {
    // If the HC-05 is connected, allow to set motor speeds
    if (BTConnected == true)
    {  
        if ( digitalRead(BTpin)==LOW)
        {
            BTconnected = false;
            Serial.println("HC-05 is now disconnected");
            setup();
        }
        data = BTSerial.read();

        // Check if the value sent via Bluetooth is in the range 0 - 9
        validateInput(data);
        UART.setCurrent(current);
        // else, switch the motor off
    } else {
        current = 0;
    }    
}

void validateInput(char c){
    // Convert char to ASCII using - int tmp
    int temp = c;  
    // ASCII 48 = 0
    // ASCII 57 = 9
    if (temp != last){
        if(temp >= 48 && temp <= 57){
            // Convert ASCII to int
            temp = temp - 48;
            
            // Set the value of the current to increments of 0.15 starting from 1 = 0.8
            if(temp == 0){
                current = 0.0;
            } else if(temp == 1){
                current = 0.8;
            } else {
                current = 0.8 + ((temp - 1) * 0.15);
            }
            last = temp;
        }
    Serial.println("Current is set to:");
    Serial.println(temp);    
    }
}