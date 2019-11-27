#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

// GPIO pin to use
const uint16_t irPin = 14;

const int btnPin1 = 2;
const int btnPin2 = 4;
const int btnPin3 = 5;

// initial button state
int btn1State = 0;
int btn2State = 0;
int btn3State = 0;

// fix signal for channel 2, 3 and 5
const int ch2 = 0x00A1DE619E;
const int ch3 = 0x00A1DEA15E;
const int ch5 = 0x00A1DE51AE;

IRsend irsend(irPin);	// Set the GPIO to be used to sending the message.

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1);

  pinMode(btnPin1, INPUT);
  pinMode(btnPin2, INPUT);
  pinMode(btnPin3, INPUT);
}

void checkBtn(int btn, int ch1, int ch2) {
  if (btn == HIGH) {
    Serial.println("*** push channel ***");
    Serial.println("first channel");
    irsend.sendNEC(ch1);
    delay(500);
    Serial.println("second channel");
    irsend.sendNEC(ch2);
    delay(500);
  }
}

void loop() {
  btn1State = digitalRead(btnPin1);
  btn2State = digitalRead(btnPin2);
  btn3State = digitalRead(btnPin3);

  checkBtn(btn1State, ch2, ch3);
  checkBtn(btn2State, ch3, ch3);
  checkBtn(btn3State, ch3, ch5);

  delay(100);
}
