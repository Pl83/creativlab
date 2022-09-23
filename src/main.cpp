#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library
#include <Wire.h> 

int lastlenght = 0;
int curentlenght = 0;
// ---------------------------------------------------------------- //
// Arduino Ultrasoninc Sensor HC-SR04
// Re-writed by Arbi Abdul Jabbaar
// Using Arduino IDE 1.8.7
// Using HC-SR04 Module
// Tested on 17 September 2019
// ---------------------------------------------------------------- //

#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

// ST7789 TFT module connections

#define TFT_CS        10
  #define TFT_RST        9 // Or set to -1 and connect to Arduino RESET pin
  #define TFT_DC         8
// Initialize Adafruit ST7789 TFT library
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);


float p = 3.1415926;


const int pir_output = 4;
//PIR sensor output at pin 2

void setup(void) {
  Serial.begin(9600); // Serial Communication is starting with 9600 of baudrate speed
  pinMode(pir_output, INPUT);
  Serial.print(F("Hello! ST77xx TFT Test"));
  // if the display has CS pin try with SPI_MODE0
  tft.init(240, 320, SPI_MODE2);    // Init ST7789 display 240x240 pixel

  // if the screen is flipped, remove this command
  tft.setRotation(1);

  Serial.println(F("Initialized"));
  uint16_t time = millis();
  tft.fillScreen(ST77XX_BLACK);
  time = millis() - time;
  Serial.println(time, DEC);
  Serial.println("done");
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); 
  Serial.println("with Arduino UNO R3");
  // initialize the screen
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(5);
  tft.setCursor(0,0);
  tft.println("Distance:");

  
}

void loop() {

  
  // Serial.println(lastlenght);
  // Serial.println(curentlenght);
  delay(1000);

  if (digitalRead(pir_output) == HIGH){
    digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; 
  // Serial.print(distance);

  int lenght = distance; 
  // Serial.println(lenght);

  if (lastlenght != curentlenght) {
      tft.setCursor(80,100);
    if (distance <= 10){
      tft.fillRect(-10,80,400,400,ST77XX_BLACK);
      tft.setTextColor(ST77XX_RED);
      tft.print(distance);
      tft.println(" cm");
      tft.print(" To close");
      curentlenght = lenght;
    }else{
      tft.fillRect(-10,80,400,400,ST77XX_BLACK);
      tft.setTextColor(ST77XX_GREEN);
      tft.print(distance);
      tft.print(" cm");
      curentlenght = lenght;
    }
  
  }else{
  }
  lastlenght = lenght;
  }
  else {
    tft.setCursor(80,100);
    tft.fillRect(-10,80,400,400,ST77XX_BLACK);
  }
}