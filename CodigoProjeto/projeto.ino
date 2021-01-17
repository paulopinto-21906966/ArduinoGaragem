// Projeto AAC - Servo x IR
//lib IR
#include <IRremote.h>

//libs Servo
//#include <ServoTimer2.h>
#include <Servo.h>

//comunicacao
#include <Wire.h>

//lib LCD
#include <LiquidCrystal_I2C.h>

// DEFINIÇÕES
#define endereco 0x27 // Endereços comuns: 0x27, 0x3F
#define colunas 16
#define linhas 2

//LCD
LiquidCrystal_I2C lcd(endereco, colunas, linhas);

// Define as bibliotecas externas que serão utilizadas ao longo da programação.
//Servo
//ServoTimer2 myservo; // Introduz o servo motor que irá executar o código predefinido no Void Loop e Void Setup.
Servo myservo;
//RGB
int red = 11; // rgb lights
int green = 10;
int blue = 8;

//IR
int RECV_PIN = 9; // Associa cada pino do Arduino a uma determinada variável.

//buzzer
int piezo = 12;

//código certo
int codigoCerto[4] = {
    1,
    2,
    3,
    4
};
int tentativa[4];
int counter = 0;
int tentativasAlarm = 0;

//sensor palmas e luzes
int soundSensor = 6;
int LED = 4;
boolean LEDStatus = false;
int val = 0;

IRrecv irrecv(RECV_PIN); // Definir o objeto receptor (entrada).

decode_results results; // Quando um código é recebido, as informações são armazenadas em "resultados".

void setup() // Define-se as entradas e as saídas, bem como determinados comandos que serão posteriormente executados assim que o circuito for energizado.
{
    Serial.begin(9600); // Define a taxa de comunicação de bits por segundo.

    irrecv.enableIRIn(); // Inicia o pino receptor do sensor infravermelho.
    //pinMode(8, INPUT);
    //digitalWrite(8, LOW);

    pinMode(red, OUTPUT);
    pinMode(green, OUTPUT);
    pinMode(blue, OUTPUT);
    pinMode(piezo, OUTPUT);
    pinMode(4, OUTPUT);

    lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
    lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY

    digitalWrite(red, LOW);
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
}

void loop() {
    // digitalWrite(piezo, HIGH); // Usar millis para calcular o tempo do piezo
    // Definir a situação das saídas em HIGH/LOW.
    lcd.setCursor(0, 0); // Define a posição do que será escrito no Liquid Crystal.
    lcd.print("FECHADO"); //Define o que será mostrado no Liquid Crystal
    //Luzes
    digitalWrite(4, HIGH);
    digitalWrite(blue, HIGH);
    delay(300);
    digitalWrite(4, LOW);
    //3 tentativas
    while (tentativasAlarm < 3) {
        //código 4 caracteres
        while (counter < 5) {
            //lê resultado
            if (irrecv.decode( & results)) {
                /* HEXADECIMAL NUMEROS

                    FF6897 / = 0
                    FF30CF / = 1
                    FF18E7 / = 2
                    FF7A85 / = 3
                    FF10EF / = 4
                    FF38C7 / = 5
                    FF5AA5 / = 6 
                    FF42BD / = 7
                    FF4AB5 / = 8
                    FF52A / = 9
                    
                    RUN / >= = FFC23D
                    
                    */
                // Depois de receber, isso deve ser chamado para redefinir o receptor e prepará-lo para receber outro código.
                irrecv.resume();
                Serial.println(results.value, HEX); //Recebe os resultados do receptor e exibe códigos hexadecimais equivalentes no monitor serial.
                if (results.value == 0xFF6897) {
                    tentativa[counter] = 0;
                }
                if (results.value == 0xFF30CF) {

                    tentativa[counter] = 1;
                }
                if (results.value == 0xFF18E7) {

                    tentativa[counter] = 2;
                }
                if (results.value == 0xFF7A85) {

                    tentativa[counter] = 3;
                }
                if (results.value == 0xFF10EF) {

                    tentativa[counter] = 4;
                }
                if (results.value == 0xFF38C7) {

                    tentativa[counter] = 5;
                }
                if (results.value == 0xFF5AA5) {

                    tentativa[counter] = 6;
                }
                if (results.value == 0xFF42BD) {

                    tentativa[counter] = 7;
                }
                if (results.value == 0xFF4AB5) {

                    tentativa[counter] = 8;
                }
                if (results.value == 0xFF52AD) {

                    tentativa[counter] = 9;
                }

                if (results.value == 0xFFC23D) {

                    //for (int i = 0; i < 4; i++) { // Comparar Keys
                    Serial.print("Ten=");
                    boolean certo = true;
                    for (int i = 0; i < 4; i++) {
                        if (tentativa[i] != codigoCerto[i]) {
                            certo = false;
                        }
                    }

                    if (certo) {

                        pinMode(soundSensor, INPUT);
                        Serial.println("Certo");
                        lcd.setCursor(0, 0);
                        lcd.print("CODIGO CERTO!!");
                        lcd.setCursor(1, 2);

                        digitalWrite(red, LOW);
                        digitalWrite(blue, LOW);
                        digitalWrite(green, HIGH);

                        //myServo.write(0);
                        // myservo.write(180);

                        myservo.attach(7);
                        myservo.writeMicroseconds(1000);
                        delay(2000);

                        lcd.clear();
                        lcd.print("ABERTO");

                        while (true) {
                            //val = analogRead(A0);
                            val = digitalRead(soundSensor);
                            Serial.println(myservo.read());
                            // when the sensor detects a signal above the threshold value, LED flashes
                            if (val == 1) {
                                digitalWrite(4, HIGH);
                                delay(6000);
                                break;
                            }
                            //delay(50);
                        }

                        digitalWrite(4, LOW);
                        digitalWrite(green, LOW);
                        digitalWrite(piezo, HIGH);
                        delay(50);
                        digitalWrite(piezo, LOW);

                        myservo.writeMicroseconds(2000);
                        delay(2000);
                        digitalWrite(blue, HIGH);
                        lcd.clear();
                        lcd.print("FECHADO");
                        myservo.detach();
                        /* myservo.write(13);
                        myservo.detach();
                         myservo.write(0);
                        myservo.attach(7);
                         myservo.detach();*/
                    } else {
                        Serial.println("Errado");
                        lcd.setCursor(0, 0);
                        lcd.print("CODIGO Errado");

                        digitalWrite(blue, LOW);
                        digitalWrite(green, LOW);
                        for (int i = 0; i < 4; i++) {

                            if (digitalRead(red) == LOW) {

                                digitalWrite(red, HIGH);
                            } else {

                                digitalWrite(red, LOW);
                            }
                            delay(1000);

                        }
                        myservo.write(180); // muda o ângulo do servo
                        delay(1000);
                        myservo.write(0);
                        tentativasAlarm++;
                        counter = 0;
                    }
                }

                Serial.println(tentativa[counter]);
                counter++;
                if (counter == 5) {
                    counter = 0;
                    //tentativasAlarm++;
                }
                Serial.print("A");
                Serial.println(tentativasAlarm);

                if (tentativasAlarm == 3) {
                    Serial.println("ERROU");
                    digitalWrite(blue, LOW);
                    digitalWrite(green, LOW);
                    digitalWrite(red, HIGH);
                    for (int i = 0; i < 3; i++) {
                        digitalWrite(piezo, HIGH);
                        delay(300);
                        digitalWrite(piezo, LOW);
                    }
                }
            }
            delay(1000);
        }

        if (counter == 5) {
            Serial.println("TIMEOUT");
            counter = 0;
        }
    }
    delay(1000);
}