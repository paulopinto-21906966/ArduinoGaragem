// Written by: Mohamed Soliman
// This code is for controlling servo motor with IR remote control
// When clicking at any of two buttons the motor is toggling between the rotation and stop

#include <IRremote.h>      //must copy IRremote library to arduino libraries

#include <Servo.h>

#define plus 0xFF629D //clockwise rotation button
#define minus 0xFFA25D //counter clockwise rotation button

int RECV_PIN = 8; //IR receiver pin
Servo servo;
int val; //rotation angle
bool cwRotation, ccwRotation; //the states of rotation

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
    Serial.begin(9600);
    irrecv.enableIRIn(); // Start the receiver

}

void loop() {
    if (irrecv.decode( & results)) {
        Serial.println(results.value, HEX);
        irrecv.resume(); // Receive the next value

        if (results.value == plus) {

            cwRotation = !cwRotation; //toggle the rotation value
            ccwRotation = false; //no rotation in this direction
        }

        if (results.value == minus) {
            ccwRotation = !ccwRotation; //toggle the rotation value
            cwRotation = false; //no rotation in this direction

        }
    }
    if (cwRotation && (val != 175)) {
        val++; //for colockwise button
    }
    if (ccwRotation && (val != 0)) {
        val--; //for counter colockwise button
    }
    servo.write(0);
    servo.attach(12); //servo pin
    servo.write(180);
    servo.detach();
    delay(1000); //General speed
}