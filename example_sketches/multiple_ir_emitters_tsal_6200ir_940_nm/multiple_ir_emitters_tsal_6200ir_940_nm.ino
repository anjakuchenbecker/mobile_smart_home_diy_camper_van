/**************************************************************************************
Example sketch that illustrates the driving of multiple IR ermitters (e.g. TSAL 6200 IR 940 mn), 
which can controlled each separately.

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
// IR lib integration
#include <IRremote.h> 

// IR emitter units config (we want to drive three IR emitter units)
#define IR_1_PIN 22 // TODO: Replace with your digital pin selection 
#define IR_2_PIN 23 // TODO: Replace with your digital pin selection
#define IR_3_PIN 24 // TODO: Replace with your digital pin selection

// TODO: Replace with the proper data len from your recorded IR codes
#define RAW_DATA_LEN 68

// TODO: Replace with your recorded IR codes (RAW data format)
uint16_t raw_data_ir_code_mock_on[RAW_DATA_LEN]={
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0};

// TODO: Replace with your recorded IR codes (RAW data format)
uint16_t raw_data_ir_code_mock_off[RAW_DATA_LEN]={
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 
  0, 0, 0, 0};

// Constructors
IRsend  irsend;     // pin D9 on arduino mega

void setup() {
  
  // Set as output to be able to control each IR emitter unit separately
  pinMode(IR_1_PIN, OUTPUT);
  pinMode(IR_2_PIN, OUTPUT);
  pinMode(IR_3_PIN, OUTPUT);

}

void loop() {
  
  // (Re)Set all IRs emitter units back to HIGH
  // HIGH means that the IR is deactivated, to send a signal set the IR (or a set of them) to LOW
  digitalWrite(IR_1_PIN, HIGH);
  digitalWrite(IR_2_PIN, HIGH);
  digitalWrite(IR_3_PIN, HIGH);

  // Now drive the available IR emitter units
  drive_available_ir_emitter_units();

}

/*
 * This function drives the different available IR emitter units
 */
void drive_available_ir_emitter_units() {

  // Drive IR emitter unit 1 and 2 (lamp on)
  // repeat signal sending --> TODO: Adjust repeats for your needs
  for (int i=0; i <= 2; i++){ 
    // Set pins to LOW to activate the IR emitter units
    digitalWrite(IR_1_PIN, LOW);
    digitalWrite(IR_2_PIN, LOW);
    // Now send your IR code, in this constellation IR emitter unit 1 and 2 sends the same signal
    irsend.sendRaw(raw_data_ir_code_mock_on, RAW_DATA_LEN, 38 /* kHz */);
    // Deactivate pins again, set it to HIGH
    digitalWrite(IR_1_PIN, HIGH);
    digitalWrite(IR_2_PIN, HIGH);
  }

  // Drive IR emitter unit 3 only (lamp on)
  // repeat signal sending --> TODO: Adjust repeats for your needs
  for (int i=0; i <= 2; i++){ 
    // Set pin to LOW to activate the IR emitter unit
    digitalWrite(IR_3_PIN, LOW);
    // Now send your IR code, in this constellation IR emitter only IR emitter unit 3 sends a signal
    irsend.sendRaw(raw_data_ir_code_mock_on, RAW_DATA_LEN, 38 /* kHz */);
    // Deactivate pin again, set it to HIGH
    digitalWrite(IR_3_PIN, HIGH);
  }
  
  delay(2000);

  // Drive IR emitter unit 1 and 2 (lamp off)
  // repeat signal sending --> TODO: Adjust repeats for your needs
  for (int i=0; i <= 2; i++){ 
    // Set pins to LOW to activate the IR emitter units
    digitalWrite(IR_1_PIN, LOW);
    digitalWrite(IR_2_PIN, LOW);
    // Now send your IR code, in this constellation IR emitter unit 1 and 2 sends the same signal
    irsend.sendRaw(raw_data_ir_code_mock_off, RAW_DATA_LEN, 38 /* kHz */);
    // Deactivate pins again, set it to HIGH
    digitalWrite(IR_1_PIN, HIGH);
    digitalWrite(IR_2_PIN, HIGH);
  }


  // Drive IR emitter unit 3 only (lamp off)
  // repeat signal sending --> TODO: Adjust repeats for your needs
  for (int i=0; i <= 2; i++){ 
    // Set pin to LOW to activate the IR emitter unit
    digitalWrite(IR_3_PIN, LOW);
    // Now send your IR code, in this constellation IR emitter only IR emitter unit 3 sends a signal
    irsend.sendRaw(raw_data_ir_code_mock_off, RAW_DATA_LEN, 38 /* kHz */);
    // Deactivate pin again, set it to HIGH
    digitalWrite(IR_3_PIN, HIGH);
  }

  delay(2000);
  
}
