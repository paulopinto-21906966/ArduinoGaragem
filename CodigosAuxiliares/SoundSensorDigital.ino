int soundSensor = 3;
int LED = 4;

void setup() {
    pinMode(soundSensor, INPUT);
    pinMode(LED, OUTPUT);

    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
}

void loop() {

    int SensorData = digitalRead(soundSensor);
    if (SensorData == 1) {

        digitalWrite(LED, HIGH);
        delay(10000);
    } else {
        digitalWrite(LED, LOW);
    }
}