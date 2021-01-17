/*
 * PIR sensor tester
 */

int ledPin = 4; // choose the pin for the LED
int inputPin = A1; // choose the input pin (for PIR sensor)
int val = 0; // variable for reading the pin status
unsigned long thisTime = 0;
void setup() {
    pinMode(ledPin, OUTPUT); // declare LED as output
    pinMode(inputPin, INPUT); // declare sensor as input

    Serial.begin(9600);
}

void loop() {
    Serial.println(millis() - thisTime);
    val = analogRead(inputPin); // read input value
    Serial.println(val);
    if (val >= 1026 || val <= 1015) { // check if the input is HIGH
        digitalWrite(ledPin, HIGH); // turn LED ON
        // we have just turned on
        Serial.println("Motion detected!");
        delay(1000);
        // We only want to print on the output change, not state

        thisTime = millis();

        digitalWrite(ledPin, LOW); // turn LED OFF
    } else {
        if (millis() - thisTime > 5000) {
            digitalWrite(ledPin, HIGH);
            delay(1000);
            digitalWrite(ledPin, LOW);
            delay(500);
            digitalWrite(ledPin, HIGH);
            delay(2000);
            digitalWrite(ledPin, LOW);
            Serial.println("AAAAAAAAAAA");
        }
    }
    delay(100);
}