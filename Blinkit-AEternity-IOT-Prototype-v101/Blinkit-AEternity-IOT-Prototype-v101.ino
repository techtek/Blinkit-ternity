// ------ Required libraries, install them if you dont have them installed ------- 

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>
#include "heltec.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// --------------------------------- YOUR WIFI ----------------------------------------

#ifndef STASSID
#define STASSID "yourwifiname"             //WIFI name
#define STAPSK  "yourwifipassword"         //WIFI password
#endif
 
const char* ssid = STASSID;
const char* password = STAPSK;


// --------------------------- YOUR AETERNITY WALLET ----------------------------------

String wallet = "ak_542o93BKHiANzqNaFj6UurrJuDuxU61zCGr9LJCwtTUg34kWt";    //change this to your or a projects wallet





//Preparing global variabels to download the data in 
  
  String payload = "empty"; 
  String payload2 = "empty";
  
  String payloadnames = "empty"; 
  String payloadnames2 = "empty";

  String payloadtransactions = "empty"; 
  String payloadtransactions2 = "empty";

  String net = "mainnet"; 


//defining the screen width and height
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// Assign output variables to GPIO pins to make it possible to blink and beep
  const int ledPin = 0;       //notification LED light
  const int piezopin = 15;    //piezo speaker


// Create an instance of the server, specify the port to listen on as an argument
WiFiServer server(80);


// AEternity logo byte array image
static const uint8_t image_data_Saraarray[1024] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x30, 0x0, 0x0, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x3, 0xfe, 0x0, 0x7, 0xfc, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x70, 0x0, 0x0, 0x7, 0xff, 0x80, 0x1f, 
  0xfe, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x70, 0xc0, 0x0, 
  0xf, 0x3, 0xc0, 0x3c, 0xf, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0xc0, 0x0, 0x1c, 0x0, 0xe0, 0x70, 0x3, 0x80, 0x0, 0x0, 
  0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc0, 0x0, 0x38, 0x0, 0x70, 0xe0, 
  0x1, 0xc0, 0xf, 0xef, 0xcf, 0xc7, 0xf1, 0xbb, 0xfe, 0x73, 0xf7, 0xe, 
  0x30, 0x0, 0x38, 0xc0, 0x0, 0xc0, 0x1f, 0xff, 0xef, 0xcf, 0xf1, 0xfb, 
  0xfe, 0x73, 0xf3, 0xe, 0x70, 0x0, 0x38, 0xc0, 0x0, 0xe0, 0x1c, 0x38, 
  0x63, 0xc, 0x39, 0xc3, 0x86, 0x70, 0xc3, 0x8c, 0x60, 0x0, 0x1c, 0x0, 
  0x0, 0x60, 0x0, 0x30, 0x63, 0x1c, 0x19, 0x83, 0x87, 0x70, 0xc3, 0x9c, 
  0x60, 0x0, 0xe, 0x1, 0xff, 0xe0, 0x7, 0xff, 0xf3, 0x1f, 0xf9, 0x83, 
  0x87, 0x70, 0xc1, 0x9c, 0x60, 0x0, 0x7, 0x1, 0xff, 0xe0, 0xf, 0xff, 
  0xf3, 0x1f, 0xf9, 0x83, 0x87, 0x70, 0xc1, 0xd8, 0x60, 0x0, 0x7, 0x0, 
  0x0, 0x0, 0x1c, 0x30, 0x3, 0x1c, 0x1, 0x83, 0x87, 0x70, 0xc0, 0xf8, 
  0x70, 0x0, 0x3, 0x80, 0x0, 0x0, 0x18, 0x38, 0x3, 0xc, 0x1, 0x83, 
  0x87, 0x70, 0xc0, 0xf0, 0x70, 0x0, 0x31, 0xc0, 0x0, 0x0, 0x1c, 0x7c, 
  0x23, 0x8e, 0x19, 0x83, 0x87, 0x70, 0xc0, 0xf0, 0x38, 0x0, 0x70, 0xe0, 
  0x1, 0xc0, 0x1f, 0xff, 0xe3, 0xe7, 0xf9, 0x83, 0x87, 0x70, 0xf0, 0x70, 
  0x38, 0x0, 0xf0, 0xf0, 0x1, 0xc0, 0x7, 0x87, 0xc1, 0xe3, 0xe1, 0x83, 
  0x87, 0x70, 0x70, 0x60, 0x1e, 0x1, 0xe0, 0x78, 0x7, 0x80, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x60, 0xf, 0x87, 0xc0, 0x3e, 
  0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 
  0x7, 0xff, 0x0, 0xf, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x3, 0xc0, 0x1, 0xfc, 0x0, 0x7, 0xf8, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x80, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  
};


// White blink screen byte array image
static const uint8_t image_data_Saraarray2[1024] = {
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,  
};



// Digital signage "pay here with aeternity" byte array image
static const uint8_t image_data_Saraarray3[1024] = {
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x3, 0xc0, 0x71, 0x83, 0x3, 0x6, 0x3f, 0x1f, 0x7, 0xf0, 0x30, 0xe1, 
  0x9d, 0xff, 0x30, 0xe0, 0x7, 0xf0, 0x71, 0xc6, 0x3, 0x6, 0x3f, 0x1f, 
  0xc7, 0xf0, 0x30, 0xe1, 0x9d, 0xff, 0x30, 0xe0, 0x6, 0x38, 0xf8, 0xc6, 
  0x3, 0x6, 0x30, 0x18, 0xc6, 0x0, 0x30, 0xe1, 0x9c, 0x38, 0x30, 0xe0, 
  0x6, 0x18, 0xd8, 0xcc, 0x3, 0x6, 0x30, 0x18, 0xc6, 0x0, 0x38, 0xf1, 
  0x9c, 0x38, 0x30, 0xe0, 0x6, 0x19, 0x98, 0x6c, 0x3, 0x6, 0x30, 0x18, 
  0xc6, 0x0, 0x19, 0xf1, 0x9c, 0x38, 0x30, 0xe0, 0x6, 0x39, 0x9c, 0x78, 
  0x3, 0xfe, 0x3f, 0x19, 0xc7, 0xe0, 0x19, 0xb3, 0x1c, 0x38, 0x3f, 0xe0, 
  0x7, 0xf1, 0x8c, 0x38, 0x3, 0xfe, 0x3f, 0x1f, 0x87, 0xe0, 0x19, 0xbb, 
  0x1c, 0x18, 0x3f, 0xe0, 0x7, 0xe3, 0x8c, 0x30, 0x3, 0x6, 0x30, 0x19, 
  0x86, 0x0, 0x1d, 0xbb, 0x1c, 0x18, 0x30, 0xe0, 0x6, 0x3, 0xfe, 0x30, 
  0x3, 0x6, 0x30, 0x18, 0xc6, 0x0, 0xf, 0x1e, 0x1c, 0x18, 0x30, 0xe0, 
  0x6, 0x3, 0x6, 0x30, 0x3, 0x6, 0x30, 0x18, 0xc6, 0x0, 0xf, 0x1e, 
  0x1c, 0x18, 0x30, 0xe0, 0x6, 0x6, 0x6, 0x30, 0x3, 0x6, 0x3f, 0x18, 
  0xe7, 0xf0, 0xf, 0x1e, 0x1c, 0x18, 0x30, 0xe0, 0x6, 0x6, 0x7, 0x30, 
  0x3, 0x6, 0x3f, 0x18, 0x67, 0xf0, 0xf, 0x1e, 0x1c, 0x18, 0x30, 0xe0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,  
};







void setup() {
  Serial.begin(115200);   // Starts serial communication, dont forget to set your serial monitor in the Arduino IDE to baud rate 115200 

  // Prepare LED
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  Serial.println();
  Serial.println(F("WiFi connected"));

  // Start the server
  server.begin();
  Serial.println(F("Server started"));

  // Print the IP address to the serial monitor
  Serial.println(WiFi.localIP());




  // display the aeternity boot logo on the screen

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);  
  Heltec.display->setContrast(255);
   
  delay(100);
  Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();

if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000); // Pause for 2 seconds
 
  // Clear the buffer.
  display.clearDisplay();
  
  // Draw aeternity logo byte array image on the screen
  display.drawBitmap(0, 0, image_data_Saraarray, 128, 32, 1);
  display.display();
  
  Heltec.display->display();

  delay(6000); // Pause for 6 seconds


  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);  
  Heltec.display->setContrast(255);
  
 
  delay(100);
  Heltec.display->clear();
 
  Heltec.display->drawString(0,0, "Open this site to start:");
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0,13, "http://");  
  Heltec.display->drawString(26,13, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();


  //set the mode for the GPIO pins
    pinMode(ledPin, OUTPUT);
    // Set outputs to LOW
    digitalWrite(ledPin, LOW);


  
}



// Downloads the current aeternity price from coingecko 

void download() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payload = https.getString();
        Serial.println(String("[HTTPS] Received payload: ") + payload);
        Serial.println(String("Number of transactions: ") + payload + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  // Display the downloaded data on the screen
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);  
  Heltec.display->setContrast(116);
  
  delay(100);
  Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payload.replace("aeternity", "");
  payload.replace("usd", "");
  payload.replace("{", "");
  payload.replace("}", "");
  payload.replace(":", "");
  payload.replace("\"", "");
  
  Heltec.display->drawString(0,0, "æternity price (usd):");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payload + " USD" );

  
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }







  
}


// Downloads (#2) the current aeternity price from coingecko 

void download2() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payload2 = https.getString();
        Serial.println(String("[HTTPS] Received payload2: ") + payload2);
        Serial.println(String("Number of transactions: ") + payload2 + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  // Display the downloaded data on the screen

  Heltec.display->setContrast(255);
  Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payload2.replace("aeternity", "");
  payload2.replace("usd", "");
  payload2.replace("{", "");
  payload2.replace("}", "");
  payload2.replace(":", "");
  payload2.replace("\"", "");
    
  Heltec.display->drawString(0,0, "æternity price (usd):");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payload2 + " USD" );
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();
  
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }


  
}





// Downloads the latest registered aeternity AENS name from https://mainnet.aeternal.io/ 

void downloadnames() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://" + net + ".aeternal.io/middleware/names/active?limit=1")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payloadnames = https.getString();
        Serial.println(String("[HTTPS] Received payloadnames: ") + payloadnames);
        Serial.println(String("Number of transactions: ") + payloadnames + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  // Display the downloaded data on the screen
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);  
  Heltec.display->setContrast(116);
  
  delay(100);
  //Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payloadnames.replace("name", "");
  payloadnames.replace("name_hash", "");
  payloadnames.replace("tx_hash", "");
  payloadnames.replace("created_at_height", "");
  payloadnames.replace("auction_end_height", "");
  payloadnames.replace("owner", "");
  payloadnames.replace("expires_at", "");
  payloadnames.replace("pointers", "");
  payloadnames.replace("null", "");
  payloadnames.replace("{", "");
  payloadnames.replace("}", "");
  payloadnames.replace(":", "");
  payloadnames.replace("\"", "");
  payloadnames.replace("", "");
  payloadnames.remove(25, 300); 
  payloadnames.remove(0, 1);
  payloadnames.replace("chain", "chain            ");
  
  Heltec.display->drawString(0,0, "æternity names (AENS)");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payloadnames);
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }
}





// Downloads (#2) the latest registered aeternity AENS name from https://mainnet.aeternal.io/ 

void downloadnames2() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://" + net + ".aeternal.io/middleware/names/active?limit=1")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payloadnames2 = https.getString();
        Serial.println(String("[HTTPS] Received payloadnames2: ") + payloadnames2);
        Serial.println(String("Number of transactions: ") + payloadnames2 + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  //Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payloadnames2.replace("name", "");
  payloadnames2.replace("name_hash", "");
  payloadnames2.replace("tx_hash", "");
  payloadnames2.replace("created_at_height", "");
  payloadnames2.replace("auction_end_height", "");
  payloadnames2.replace("owner", "");
  payloadnames2.replace("expires_at", "");
  payloadnames2.replace("pointers", "");
  payloadnames2.replace("null", "");
  payloadnames2.replace("{", "");
  payloadnames2.replace("}", "");
  payloadnames2.replace(":", "");
  payloadnames2.replace("\"", "");
  payloadnames2.replace("", "");
  payloadnames2.remove(25, 300); 
  payloadnames2.remove(0, 1);
  payloadnames2.replace("chain", "chain            "); 
  
  
  Heltec.display->drawString(0,0, "æternity names (AENS)");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payloadnames2);

  
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();


  
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }


  
}




// Downloads the latest transaction from from https://mainnet.aeternal.io/ for the specified wallet

void downloadtransactions() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://" + net + ".aeternal.io/middleware/transactions/account/" + wallet + "/count")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payloadtransactions = https.getString();
        Serial.println(String("[HTTPS] Received payloadtransactions: ") + payloadtransactions);
        Serial.println(String("Number of transactions: ") + payloadtransactions + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  // Display the downloaded data on the screen
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);  
  Heltec.display->setContrast(116);
  
 
  delay(100);
  Heltec.display->clear();
  
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payloadtransactions.replace("count", "");
  payloadtransactions.replace("{", "");
  payloadtransactions.replace("}", "");
  payloadtransactions.replace(":", "");
  payloadtransactions.replace("\"", "");
  payloadtransactions.replace("", "");
  
  Heltec.display->drawString(0,0, "æternity transactions (TX)");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payloadtransactions);  
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());
  
  Heltec.display->display();
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }
}



// Downloads (#2) the latest transaction from from https://mainnet.aeternal.io/ for the specified wallet

void downloadtransactions2() {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
  client->setInsecure();
  HTTPClient https;

  if (https.begin(*client, "https://" + net + ".aeternal.io/middleware/transactions/account/" + wallet + "/count")) {  // HTTPS  https://api.coingecko.com/api/v3/simple/price?ids=aeternity&vs_currencies=usd
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      // file found at server?
      if (httpCode == HTTP_CODE_OK) {
        payloadtransactions2 = https.getString();
        Serial.println(String("[HTTPS] Received payloadtransactions2: ") + payloadtransactions2);
        Serial.println(String("Number of transactions: ") + payloadtransactions2 + "");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(F("\n\rWiFi connected!"));

  //show the downloaded data on the screen

  Heltec.display->setContrast(255);
  Heltec.display->clear();

  Heltec.begin(true /*DisplayEnable Enable*/, true /*Serial Enable*/);
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);

  payloadtransactions2.replace("count", "");
  payloadtransactions2.replace("{", "");
  payloadtransactions2.replace("}", "");
  payloadtransactions2.replace(":", "");
  payloadtransactions2.replace("\"", "");
  payloadtransactions2.replace("", "");  
  
  Heltec.display->drawString(0,0, "æternity transactions (TX)");
  Heltec.display->setFont(ArialMT_Plain_16);
  Heltec.display->drawString(0,13, payloadtransactions2);  
  
  //Heltec.display->drawString(0, 19, WiFi.localIP().toString().c_str());  
  Heltec.display->display();  
        
      }
    } else {
      Serial.printf("[HTTPS] GET... failed, error: %s\n\r", https.errorToString(httpCode).c_str());
    }

    https.end();
  } else {
    Serial.printf("[HTTPS] Unable to connect\n\r");
  }
  
}








// Function to compare and download new aeternity price data to compare with.

void compare()
{
    // compare downloaded data and do a action
    if (payload.equals(payload2)) {
    Serial.println(payload + " equals " + payload2 + " Continue detecting");
    
    Serial.println(""); //empty line
    Serial.println("Blinkit is running...");
    download2();
  } else {
    Serial.println(payload + " does not equal " + payload2 + " Change Detected!!!");
    Serial.println("Blinkit Change Deteced...!");
      
      Serial.println("Download");
  download();
  Serial.println("Download done");


//play notification sound
sound();

//triggers the blink action and Blinks the LED and screen
blinks();

}
}





// Function to compare and download new AENS name to compare with.

void comparenames(){

    // compare downloaded data and do a action
    if (payloadnames.equals(payloadnames2)) {
    Serial.println(payloadnames + " equals " + payloadnames2 + " Continue Detecting");
    
    Serial.println(""); //empty line
    Serial.println("Blinkit is running...");
    downloadnames2();
  } else {
    Serial.println(payloadnames + " does not equal " + payloadnames2 + " Change Detected!!!");
    Serial.println("Blinkit Change Deteced...!");
      
      Serial.println("downloadnames");
  downloadnames();
  Serial.println("downloadnames done");



//play notification sound
sound();

//triggers the blink action and blinks the LED and screen
blinks();

}
}





// Function to compare and download new wallet transaction count, to compare with.

void comparetransactions(){

    // compare downloaded data and do a action
    if (payloadtransactions.equals(payloadtransactions2)) {
    Serial.println(payloadtransactions + " equals " + payloadtransactions2 + " Continue Detecting");
    
    Serial.println(""); //empty line
    Serial.println("Blinkit is running...");
    downloadtransactions2();
  } else {
    Serial.println(payloadtransactions + " does not equal " + payloadtransactions2 + " Change Detected!!!");
    Serial.println("Blinkit Change Deteced...!");
      
      Serial.println("downloadtransactions");
  downloadtransactions();
  Serial.println("downloadtransactions done");


//play notification sound
sound();

//triggers the blink action and Blinks the LED and screen
blinks();

}
}



// Function to store and play notification sounds (bleep, BLEEP, BLEEEEP!)
void sound() {
   
   tone(piezopin, 600, 100);              // frequency, time
   delay(100);
   tone(piezopin, 1300, 100);             // frequency, time
   delay(100);
   tone(piezopin, 1600, 300);             // frequency, time
   delay(300);
}


//Function to blink the screen and the (optional) connected LED light.
void blinks() {

    // Turn the screen and LED light ON
    display.clearDisplay();  
    // Draw byte array image on the screen
    display.drawBitmap(0, 0, image_data_Saraarray2, 128, 64, 1);
    display.display();  
    Heltec.display->display();   
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(500);
    
    // Turn off the screen and LED light OFF
    display.clearDisplay();  
    display.display();  
    Heltec.display->display();  
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500); 
    
    // Turn the screen and LED light ON
    display.clearDisplay();  
    // Draw bitmap on the screen
    display.drawBitmap(0, 0, image_data_Saraarray2, 128, 64, 1);
    display.display();  
    Heltec.display->display();   
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(500);
    
    // Turn the screen and LED light OFF
    display.clearDisplay();  
    display.display();  
    Heltec.display->display();  
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500); 

    // Turn the screen and LED light ON
    display.clearDisplay();  
    // Draw bitmap on the screen
    display.drawBitmap(0, 0, image_data_Saraarray2, 128, 64, 1);
    display.display();  
    Heltec.display->display();   
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(500);

    // Turn the screen and LED light OFF
    display.clearDisplay();  
    display.display();  
    Heltec.display->display();  
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500);
 } 
    




//Function to make the device become a digital signage display

void digitalsignage() {

webserver();

     // Clear the buffer.
    display.clearDisplay();  
    // Draw bitmap on the screen
    display.drawBitmap(0, 0, image_data_Saraarray3, 128, 64, 1);
    display.display();  
    Heltec.display->display();   
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(1000);
    
     // Clear the buffer.
    display.clearDisplay();  
    display.display();  
    Heltec.display->display();  
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500); 
    
     // Clear the buffer.
    display.clearDisplay();  
    // Draw bitmap on the screen
    display.drawBitmap(0, 0, image_data_Saraarray, 128, 64, 1);
    display.display();  
    Heltec.display->display();   
    digitalWrite(ledPin, HIGH); // turn the LED on
    delay(3000);
    
     // Clear the buffer.
    display.clearDisplay();  
    display.display();  
    Heltec.display->display();  
    digitalWrite(ledPin, LOW);  // turn the LED off
    delay(500); 

 
 digitalsignage(); 
 
} 




//Function to download the latest aeternity price and check if it changes 

void price() {

  webserver();
  Serial.println("Wait a bit...");
  delay(6000);
  Serial.println("Download2");
  download2();
  Serial.println("Download2 done");
  compare();
  price();

}



//Function to download the latest AENS name and check if it changes

void names() {

  webserver();
  Serial.println("Wait a bit (names)...");
  delay(6000);
  Serial.println("downloadnames2");
  downloadnames2();
  Serial.println("downloadnames2 done");
  comparenames();
  names();

}




//Function to download the latest aeternity wallet transactions

void transactions() {
 
  webserver();
  Serial.println("Wait a bit (tx)...");
  delay(6000);
  Serial.println("downloadtransactions2");
  downloadtransactions2();
  Serial.println("downloadtransactions2 done");
  comparetransactions();
  transactions();

}




// reset functions

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void stopit() {
ESP.restart();

}



// change from aeternity mainnet to the aeternity testnet 

void testnet() {
net = "testnet";

}




// Webserver and webinterface 

void webserver() {
  
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  Serial.println(F("new client"));

  client.setTimeout(5000); // default is 1000

  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(req);

  // Match the request
  int val;
  if (req.indexOf(F("/gpio/0")) != -1) {
    val = 0;
  } else if (req.indexOf(F("/gpio/1")) != -1) {
    val = 1;
  } else if (req.indexOf(F("/sound")) != -1) {
    val = 2;
    sound();
  } else if (req.indexOf(F("/price")) != -1) {
    val = 3;
    price();
  } else if (req.indexOf(F("/stopit")) != -1) {
    val = 4;
    resetFunc();  //call reset
    stopit();
  } else if (req.indexOf(F("/names")) != -1) {
    val = 5;
    names();
  } else if (req.indexOf(F("/transactions")) != -1) {
    val = 6;
    transactions();
  } else if (req.indexOf(F("/digitalsignage")) != -1) {
    val = 7;
    digitalsignage();
  } else if (req.indexOf(F("/testnet")) != -1) {
    val = 8;
    testnet();
  }
  else {
    Serial.println(F("invalid request"));
    val = digitalRead(LED_BUILTIN);
  }

  // Set LED according to the request
  digitalWrite(LED_BUILTIN, val);

  // read/ignore the rest of the request
  // do not client.flush(): it is for output only, see below
  while (client.available()) {
    // byte by byte is not very efficient
    client.read();
  }




// CSS to style the webinterface
            client.println("<style>html { font-family: Helvetica; color: black; display: inline-block; margin: 0px auto; background-color: #ffffff; text-align: center;}");
            client.println(".button { background-color: #F7296D; border: none; color: white; padding: 10px 40px;");
            client.println("text-decoration: none; font-size: 15px; margin: 2px; cursor: pointer;}");
            client.println("a {color: lightgrey; font-size: 16px;}");
            client.println(".button2 {background-color: #F7296D; font-size: 10px; margin: 2px;}");

            client.println(".collapsible { background-color: #000000; color: darkgrey; cursor: pointer; padding: 18px; width: 100%; border-style: solid; border: none; text-align: left; outline: none; font-size: 15px;}");
            client.println(".active, .collapsible:hover { background-color: #555;}");
            client.println(".content {  padding: 0 18px; display: none; overflow: hidden; background-color: #ffffff;}</style></head>");

        
            // Web Page Heading
            client.println("<body>");
           
            client.println("<a href=\"\">");
            client.println("<img src=\"https://i.imgur.com/6Rpz3U3.png\" alt=\"Logo and Home Button\" style=\"width:60%;height:auto;border:0;\"></a>");       
            client.println("<br><br />");


            // Display the users avatar image
            client.println("<table style=\"width:600px\">");
            client.println("<table align=\"center\">");
            client.println("<tr>");
            client.println("<td><img src=\"https://avatars.z52da5wt.xyz/" + wallet + "\" alt=\"Users avatar\" style=\"width:40px;height:auto;border:0;\"></a> &nbsp; </td>");

            // Display the users wallet adress     
            client.println("<td align=\"left\">");
            client.println("<p>Wallet: <b>" + wallet + "</b></p>");
  
            client.println("</td>");
            client.println("</tr></table>");
            client.println("<br><br />");



            // Collapsible settings menu
            client.println("<button class=\"collapsible\">FUNCTIONS</button>");
            client.println("<div class=\"content\">");
            

            client.println("<p>Choose one of the functions</p>");
            client.println("<br></br>");

            client.println("<p>Show the aeternity price and blink and beep when it changes</p>");
            client.println("<p><a href=\"/price\"><button class=\"button button3\">START</button></a>"); 

            client.println("<br></br>");

            client.println("<p>Show the latest registered (AENS) .chain names and blink and beep on changes </p>");           
            client.println("<p><a href=\"/names\"><button class=\"button button3\">START</button></a>");

            client.println("<br></br>");

            client.println("<p>Wallet transaction count, blink and bleep on changes </p>");
            client.println("<p><a href=\"/transactions\"><button class=\"button button3\">START</button></a>");

            client.println("<br></br>");

            client.println("<p>Digital Signage</p>");
            client.println("<p><a href=\"/digitalsignage\"><button class=\"button button3\">START</button></a>");

            client.println("<br></br>");
            client.println("<p>Switch to Testnet (Default is Mainnet) </p>");
            client.println("<p><a href=\"/testnet\"><button class=\"button button3\">TESTNET</button></a>");

            client.println("<br></br>");
            client.println("<p>Reset Device </p>");
            client.println("<p><a href=\"/stopit\"><button class=\"button button3\">RESET</button></a>");

            
            
            client.println("</div>");
            
            
            client.println("<button class=\"collapsible\">LIGHT</button>");
            client.println("<div class=\"content\">");
            
            // Display a button to test the notification light
     
            client.println("<p>Test notification light</p>");
                          
            client.println("<p><a href=\"/gpio/1\"><button class=\"button button3\">ON</button></a>");
            client.println("<p><a href=\"/gpio/0\"><button class=\"button button3\">OFF</button></a>");

                       
            client.println("</div>");
            
            client.println("<button class=\"collapsible\">SOUND</button>");
            client.println("<div class=\"content\">");            
            
            client.println("<p>Notification Sound</p>");
            client.println("<p><a href=\"/sound\"><button class=\"button button3\">Test</button></a>");
            
            client.println("</div>");

            client.println("<button class=\"collapsible\">TOOLS</button>");
            client.println("<div class=\"content\">");
            
            client.println("<p>Choose Tool</p>");
            client.println("<br></br>");
            
            // Tools button 
            client.println("<p>AEternity website</p>");
            client.println("<a href=\"https://aeternity.com\">");
            client.println("<img src=\"https://i.imgur.com/usYzNKx.png\" alt=\"Blinkit Logo and Home Button\" style=\"width:350px;height:auto;border:0;\"></a>");       
            client.println("<br><br />");

            // Tools buttons
            client.println("<p>AEternal Block Explorer</p>");
            client.println("<a href=\"https://explorer.aeternity.io\">");
            client.println("<img src=\"https://i.imgur.com/XwiSvh8.png\" alt=\"Blinkit Logo and Home Button\" style=\"width:350px;height:auto;border:0;\"></a>");       
            client.println("<br><br />");

            client.println("<br></br>");
            // Tools button 
            client.println("<p>AEKnow Block Explorer</p>");
            client.println("<a href=\"https://www.aeknow.org\">");
            client.println("<img src=\"https://i.imgur.com/BeykiKN.png\" alt=\"Blinkit Logo and Home Button\" style=\"width:350px;height:auto;border:0;\"></a>");       
            client.println("<br><br />");
            client.println("</div>");

            
            client.println("<button class=\"collapsible\">OTHER</button>");
            client.println("<div class=\"content\">");
                 
            client.println("&nbsp;"); //single emptyline             
            client.println("<p><a href=\"https://discord.gg/hnDfwbc\">Technical support</a></p>");            
            client.println("<br><br />");                                  
            client.println("</div>");


            
            
            // script for the collapsible menu
            client.println("<script>");
            client.println("var coll = document.getElementsByClassName(\"collapsible\"); ");
            client.println("var i; ");
            
            client.println("for (i = 0; i < coll.length; i++) { ");
            client.println("coll[i].addEventListener(\"click\", function() { ");
            client.println("this.classList.toggle(\"active\"); ");
            client.println("var content = this.nextElementSibling; ");
            client.println("if (content.style.display === \"block\") { ");
            client.println("content.style.display = \"none\"; ");
            client.println(" } else { ");
            client.println("content.style.display = \"block\"; ");
            client.println(" } ");
            client.println(" }); ");
            client.println(" } ");
            client.println(" </script>");

            client.println("<br><br />"); //single emptyline




  client.println("<p><a href=\"https://github.com/techtek\">Made by techtek</a></p>");   




            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop

     
  // The client will actually be *flushed* then disconnected
  // when the function returns and 'client' object is destroyed (out-of-scope)
  // flush = ensure written data are received by the other side
  Serial.println(F("Disconnecting from client"));

  
}





//run the webserver 

void loop() {

webserver();
  
}
