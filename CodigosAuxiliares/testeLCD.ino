#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 7, 6, 5, 4, 3, 2); // Define os pinos a serem utilizados para conexão do LiquidCrystal.

void setup() {
    lcd.begin(16, 2);
}

void loop() {
    analogWrite(3, 100);
    delay(1000);
    lcd.setCursor(0, 0);
    lcd.print("   Subscribe!");
    lcd.setCursor(2, 1);
    lcd.print("RaspberryUser");
    delay(1000);
    digitalWrite(7, HIGH);
    delay(1000);
    digitalWrite(7, LOW);
    delay(1000);
    digitalWrite(7, HIGH);
}