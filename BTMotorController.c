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

    while (!Serial) {;}

    /** Define which ports to use as UART */
    UART.setSerialPort(&Serial);

}

// Main Loop
void loop() {
    data = BTSerial.read();    
    // Print the value of data 
    Serial.println("The BT input is: ");
    Serial.println(data);

    validateInput(data);
    UART.setCurrent(current);
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