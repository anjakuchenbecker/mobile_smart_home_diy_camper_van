/**************************************************************************************
Example sketch that illustrates reading from four daisy-chained 74HC165N shift registers.

Inspired by https://playground.arduino.cc/Code/ShiftRegSN74HC165N/

********************************************
Copyright © 2021 Anja Kuchenbecker

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************************/

// Shift register global stuff
#define NUMBER_OF_SHIFT_CHIPS 4 // Amount of daisy-chaned shift registers
#define DATA_WIDTH NUMBER_OF_SHIFT_CHIPS * 8 // Calculated data width
#define PULSE_WIDTH_USEC 5 // Pulse width to trigger the shift register to read and latch
#define POLL_DELAY_MSEC 1 // Optional delay between single shift register reads
#define SHIFT_REGISTER_LOAD 47 // PL pin --> 1    TODO: Replace with your digital pin selection
#define SHIFT_REGISTER_CLOCK_ENABLE_PIN 48 // CE pin --> 15   TODO: Replace with your digital pin selection
#define SHIFT_REGISTER_DATA_IN 45 // Q7 pin --> 9   TODO: Replace with your digital pin selection
#define SHIFT_REGISTER_CLOCK_IN 46 // CP pin --> 2  TODO: Replace with your digital pin selection
#define BTN_1 1 // TODO: Replace with proper value coming from shift register
unsigned long remotecontrol_button_pressed_state; 

void setup(){

// Shift register setup
pinMode(SHIFT_REGISTER_LOAD, OUTPUT);
pinMode(SHIFT_REGISTER_CLOCK_ENABLE_PIN, OUTPUT);
pinMode(SHIFT_REGISTER_CLOCK_IN, OUTPUT);
pinMode(SHIFT_REGISTER_DATA_IN, INPUT);
digitalWrite(SHIFT_REGISTER_CLOCK_IN, LOW);
digitalWrite(SHIFT_REGISTER_LOAD, HIGH);

// Setup serial monitor
Serial.begin(9600); 

// Let's go hint
Serial.println("Ready");

}

void loop(){

    // Read the state of all shift registers
    remotecontrol_button_pressed_state = read_shift_regs();
    delay(POLL_DELAY_MSEC);
    
    // Print what shift register reads
    Serial.println("Current shift register reading:");
    Serial.println(remotecontrol_button_pressed_state);
    
    // Handling of button 1 press
    if ( remotecontrol_button_pressed_state == BTN_1 ) {

        // Debug only: Show info about pressed button
        Serial.println("Button 1 pressed!");
        
        // TODO: Insert wished functionality here, what should happen when your button has been pressed?
        
        // Perform sufficient delay
        delay(300);
    }

}

/* ***************************************************************************************************
 * Function that reads the serial data from four daisy-chained shift register chips (74HC165N) 
 * 
 * Returns the state.
 ******************************************************************************************************/
unsigned long read_shift_regs() {

    // Define helper variables
    long bit_val;
    unsigned long bytes_val = 0;
    
    // Trigger parallel load to latch the state of the data lines
    digitalWrite(SHIFT_REGISTER_CLOCK_ENABLE_PIN, HIGH);
    digitalWrite(SHIFT_REGISTER_LOAD, LOW);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(SHIFT_REGISTER_LOAD, HIGH);
    digitalWrite(SHIFT_REGISTER_CLOCK_ENABLE_PIN, LOW);

    // Loop to read each bit value from the serial out line of the SN74HC165N
    for(int i = 0; i < DATA_WIDTH; i++) {
        bit_val = digitalRead(SHIFT_REGISTER_DATA_IN);

        // Set the corresponding bit in bytesVal
        bytes_val |= (bit_val << ((DATA_WIDTH-1) - i));

        // Pulse the Clock (rising edge shifts the next bit)
        digitalWrite(SHIFT_REGISTER_CLOCK_IN, HIGH);
        delayMicroseconds(PULSE_WIDTH_USEC);
        digitalWrite(SHIFT_REGISTER_CLOCK_IN, LOW);
    }

    // Return the state
    return(bytes_val);
}
