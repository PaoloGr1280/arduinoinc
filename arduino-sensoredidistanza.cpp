#include <Adafruit_LiquidCrystal.h>
#include "Adafruit_LEDBackpack.h"

int distanza = 0;
int i = 0;
int ritardo = 0;

Adafruit_LiquidCrystal lcd_1(0);

Adafruit_7segment led_display1 = Adafruit_7segment();

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(8, OUTPUT);
  lcd_1.begin(16, 2);
  led_display1.begin(112);
  Serial.begin(9600);
  pinMode(12, OUTPUT);

  digitalWrite(6, LOW);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
  digitalWrite(8, HIGH);
  ritardo = 15;
}

void loop()
{
  led_display1.blinkRate(0);
  delay(1000); // Wait for 1000 millisecond(s)
  distanza = 0.01723 * readUltrasonicDistance(8, 7);
  Serial.println(distanza);
  lcd_1.print("Distanza: ");
  lcd_1.setCursor(0, 1);
  lcd_1.print(distanza);
  if (distanza <= 25) {
    digitalWrite(6, HIGH);
    for (i = 0; i <= 255; i += 1) {
      tone(12, 698, 1000 * ritardo); // play tone 65 (F5 = 698 Hz)
      tone(12, 659, 1000 * ritardo); // play tone 64 (E5 = 659 Hz)
      analogWrite(6, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
    for (i = 255; i >= 0; i -= 1) {
      analogWrite(6, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
  }
  noTone(12);
  digitalWrite(6, LOW);
  if (distanza >= 26 && distanza <= 150) {
    digitalWrite(5, HIGH);
    for (i = 0; i <= 255; i += 1) {
      analogWrite(5, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
    for (i = 255; i >= 0; i -= 1) {
      analogWrite(5, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
  }
  digitalWrite(5, LOW);
  if (distanza >= 151 && distanza <= 334) {
    digitalWrite(3, HIGH);
    for (i = 0; i <= 255; i += 1) {
      analogWrite(3, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
    for (i = 255; i >= 0; i -= 1) {
      analogWrite(3, i);
      delay(ritardo); // Wait for ritardo millisecond(s)
    }
  }
  if (distanza >= 335) {
    analogWrite(6, 255);
    analogWrite(5, 102);
    analogWrite(3, 0);
    lcd_1.clear();
    lcd_1.print("Distanza: ");
    lcd_1.setCursor(0, 1);
    lcd_1.print("Errore");
    delay(5000); // Wait for 5000 millisecond(s)
  }
  lcd_1.clear();
  delay(1000); // Wait for 1000 millisecond(s)
}