#include <dht11.h>
#include <LiquidCrystal.h>

#define DHT11_PIN A2
dht11 DHT11;

int temperature;
int humidity;
int lum;
int distance;

const int buzzerPin = A1;
const int trigPin = 7;
const int echoPin = 13;
const int fanPin = 8;
const int redLedPin = 1;
const int yellowLedPin = 9;
const int greenLedPin = 10;
const int blueLedPin = 6;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  int i;

  int ledPins[4] = {blueLedPin, greenLedPin, yellowLedPin, redLedPin};
  for (i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  pinMode(fanPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);
}

void loop() {
  int chk;

  chk = DHT11.read(DHT11_PIN);
  temperature = DHT11.temperature;
  humidity = DHT11.humidity;

  lum = analogRead(A0);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C ");
  lcd.setCursor(0,1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%   ");

  if(digitalRead(13) == HIGH){
    lcd.scrollDisplayLeft();
    delay(500);
  }

  if (temperature >= 10 && temperature <= 18) {
    digitalWrite(blueLedPin, HIGH);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(fanPin, LOW);
  } else if (temperature >= 19 && temperature <= 21) {
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, HIGH);
    digitalWrite(fanPin, LOW);
  } else if (temperature > 22) {
    digitalWrite(blueLedPin, LOW);
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, LOW);
    digitalWrite(redLedPin, LOW);
    digitalWrite(fanPin, HIGH);
  } else {
    int i;
    int ledPins[4] = {blueLedPin, greenLedPin, yellowLedPin, redLedPin};
    for (i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    digitalWrite(fanPin, LOW);
  }

  if (humidity >= 40 && humidity <= 60) {
    digitalWrite(greenLedPin, HIGH);
    digitalWrite(yellowLedPin, LOW);
  } else {
    digitalWrite(greenLedPin, LOW);
    digitalWrite(yellowLedPin, HIGH);
  }

  if (distance < 20) {
    tone(buzzerPin, 2000);
    delay(100);
   
