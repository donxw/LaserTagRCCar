// Visual Micro is in vMicro>General>Tutorial Mode
//
/*
    Name:       NodeMCUMotorShieldTest.ino
    Created:	9/26/2021 9:04:11 PM
    Author:     PAVGAMING\willi

    Board:  NodeMCU 1.0 
    Shield:  NodeMCU Motor Shield HW588A

    Wire Motor A to left motor
    Wire Motor B to right motor

    Shield I/O pins are
    Row closest to CPU = Digital
    Middle Row = 3.3V
    Outside Row = GND
*/

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <FastLED.h>

// Define User Types below here or use a .h file
//
#define DIRA 0  //D3
#define PWMA 5  //D1
#define DIRB 2  //D4
#define PWMB 4  //D2
#define CW 1
#define CCW 0

#define maxSpeed 255  // Max motor speed
#define deadBand 100  // Safe range to ignore round midpoint of joystick readings...
#define FORWARD 1
#define BACKWARD 2
#define DEBUG
//#define LEDPIN BUILTIN_LED

#define NEOPIN 14  //D5
#define N_LEDS 1
// Define the array of leds
CRGB leds[N_LEDS];

//  Global Variables
//
int LaserSensor = A0;
int SensorReading = 0;
int Laser = 12;  //D6
int HitCount = 0;

int dirMotorL = FORWARD;
int dirMotorR = FORWARD;
int motorSpeedL = 0;
int motorSpeedR = 0;
int speedDiff = 0;
const int valX_center = 1930;  // from testing the joystick center value
const int valY_center = 1900;
int full_range = 4095;  // full Joystick range from ESP32

//Set up MAC to send data to
// Concept B Contoller 08:3A:F2:69:CD:04 <- get from the Remote Control ESP32 Dev board
uint8_t mac_peer1[] = { 0x08, 0x3A, 0xF2, 0x69, 0xCD, 0x04 };

// Must match with the reciever on the remote control unit
struct SEND_DATA_STRUCTURE {
  int score;
};

SEND_DATA_STRUCTURE send;

void onDataSent(uint8_t* mac_addr, uint8_t sendStatus) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(sendStatus == 0 ? "Delivery Success" : "Delivery Fail");
}

// Set up data receiver

struct RECEIVE_DATA_STRUCTURE {
  int valX;
  int valY;
  int button;
};

RECEIVE_DATA_STRUCTURE received;
bool newMessage = false;

void onDataRecv(uint8_t* mac, uint8_t* incomingData, uint8_t len) {
  //Serial.println("Message received.");
  newMessage = true;
  // Transform the incoming data into our message structure
  memcpy(&received, incomingData, sizeof(received));
}

// Define Functions below here or use other .ino or cpp files
//
void playmelody();
void playmelody2();

// The setup() function runs once each time the micro-controller starts
void setup() {
  Serial.begin(115200);

  // Initialize Neopixel led
  //FastLED.addLeds<NEOPIXEL, NEOPIN>(leds, N_LEDS);  // GRB ordering is assumed
  FastLED.addLeds<WS2812, NEOPIN, RGB>(leds, N_LEDS);
  //FastLED.addLeds<WS2812, NEOPIN, BGR>(leds, N_LEDS);
  //FastLED.addLeds<WS2812, NEOPIN, GRB>(leds, N_LEDS);  // GRB ordering is typical
  //FastLED.addLeds<WS2812, NEOPIN, GBR>(leds, N_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(32);
  leds[0] = CRGB::Black;
  FastLED.show();
  leds[0] = CRGB::DarkGreen;
  FastLED.show();

  // Laser ams Reciever
  pinMode(Laser, OUTPUT);
  pinMode(LaserSensor, INPUT);

  // Setup ESPNOW
  WiFi.disconnect();
  ESP.eraseConfig();

  // Wifi STA Mode
  WiFi.mode(WIFI_STA);

  // Get Mac Add  uncomment for debug
  Serial.print("\n");
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nRC ESP-Now Receiver");

  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }

  // Intialize ESPNow message
  received.valX = valX_center;
  received.valY = valY_center;
  received.button = true;

  // Set ESPNow Role
  //esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  //
  // Register the receiver and sender callback functions
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_recv_cb(onDataRecv);
  esp_now_register_send_cb(onDataSent);

  // Register peer
  esp_now_add_peer(mac_peer1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  // Setup Motor Shield Pins
  pinMode(DIRA, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMB, OUTPUT);

  playmelody();

  send.score = 0;
  esp_now_send(mac_peer1, (uint8_t*)&send, sizeof(send));

  // turn on built in LED
  //  pinMode(LEDPIN, OUTPUT);
  //  digitalWrite(LEDPIN, LOW);

  // plotter logo
  Serial.print(" ValY ValX Button ");

  // laser on
  digitalWrite(Laser, HIGH);
}

// Add the main program code into the continuous loop() function
void loop() {

  SensorReading = analogRead(LaserSensor);
  //Serial.println("Analog value : ");
  //Serial.println(SensorReading);
  if (SensorReading > 1020) {
    playmelody();
    Serial.println("Hit");
    HitCount++;
    send.score = HitCount;
    esp_now_send(mac_peer1, (uint8_t*)&send, sizeof(send));
    //    if (HitCount <= 3) {
    //      leds[0] = CRGB::DarkSeaGreen;
    //      FastLED.show();
    //    }
    if (HitCount == 4) {
      leds[0] = CRGB::LawnGreen;
      FastLED.show();
    }
    if (HitCount == 7) {
      leds[0] = CRGB::Orange;
      FastLED.show();
    }
    if (HitCount == 10) {
      leds[0] = CRGB::Red;
      FastLED.show();
      //spin motor
      digitalWrite(DIRA, CCW);  //Left Motor CCW for Forward
      analogWrite(PWMA, 220);
      digitalWrite(DIRB, CCW);  //Right Motor CCW for Backward
      analogWrite(PWMB, 220);
      playmelody2();
      //motor off
      analogWrite(PWMA, 0);
      analogWrite(PWMB, 0);
      // laser off
      digitalWrite(Laser, LOW);
    }
  } else {
    // nothing
  }

  // uncomment define DEBUG to run
#ifdef DEBUG
  if (newMessage == true) {
    Serial.print(received.valY);
    Serial.print(" ");
    Serial.print(received.valX);
    Serial.print(" ");
    Serial.print(received.button * 1000);
    Serial.print("\n");
    newMessage = false;
  }
#endif  // DEBUG
  // map joystick Y-axis to motor speed (deadband may not be needed since accounted for in sender)
  motorSpeedL = motorSpeedR = 0;
  if (received.valY < (valY_center - deadBand)) {
    motorSpeedL = map(received.valY, 0, valY_center, -maxSpeed, 0);
    motorSpeedR = motorSpeedL;
    Serial.println(motorSpeedL);
  } else if (received.valY > (valY_center + deadBand)) {
    motorSpeedL = map(received.valY, valY_center, full_range, 0, maxSpeed);
    motorSpeedR = motorSpeedL;
  }

  // determine speed difference in motors from joystick X-axis value
  speedDiff = 0;
  if (received.valX < valX_center - deadBand) {
    speedDiff = map(received.valX, 0, valX_center, -maxSpeed / 1, 0);
  } else if (received.valX > valX_center + deadBand) {
    speedDiff = map(received.valX, valX_center, full_range, 0, maxSpeed / 1);
  }

  // set Motor Speeds
  motorSpeedL += speedDiff;
  motorSpeedR -= speedDiff;

  dirMotorL = motorSpeedL < 0 ? BACKWARD : FORWARD;  //LEFT MOTOR_CH_A CCW IS FORWARD
  dirMotorR = motorSpeedR < 0 ? BACKWARD : FORWARD;  //RIGHT MOTOR_CH_B CW IS FORWARD

  // limit Motor Speeds to max value allowed
  motorSpeedL = abs(motorSpeedL);
  motorSpeedR = abs(motorSpeedR);
  if (motorSpeedL > maxSpeed) motorSpeedL = maxSpeed;
  if (motorSpeedR > maxSpeed) motorSpeedR = maxSpeed;

  // set Left motor speed & direction
  //dirMotorL == FORWARD ? M1.setmotor(_CCW, motorSpeedL) : M1.setmotor(_CW, motorSpeedL);
  if (dirMotorL == FORWARD) {
    digitalWrite(DIRA, CCW);  //Left Motor CCW for Forward
    analogWrite(PWMA, motorSpeedL);
  } else {
    digitalWrite(DIRA, CW);  //Left Motor CW for Reverse
    analogWrite(PWMA, motorSpeedL);
  }

  // set Right motor speed & direction
  //dirMotorR == FORWARD ? M2.setmotor(_CW, motorSpeedR) : M2.setmotor(_CCW, motorSpeedR);
  if (dirMotorR == FORWARD) {
    digitalWrite(DIRB, CW);  //Left Motor CW for Forward
    analogWrite(PWMB, motorSpeedR);
  } else {
    digitalWrite(DIRB, CCW);  //Left Motor CCW for Reverse
    analogWrite(PWMB, motorSpeedR);
  }

  // beep on button push
  if (received.button == false) {
    playmelody();
    Serial.println("beep beep");
    received.button = true;
  }



  delay(100);  //update @ 10Hz
}


/**
   # Colors
  CRGB::AliceBlue KEYWORD2
  CRGB::Amethyst  KEYWORD2
  CRGB::AntiqueWhite  KEYWORD2
  CRGB::Aqua  KEYWORD2
  CRGB::Aquamarine  KEYWORD2
  CRGB::Azure KEYWORD2
  CRGB::Beige KEYWORD2
  CRGB::Bisque  KEYWORD2
  CRGB::Black KEYWORD2
  CRGB::BlanchedAlmond  KEYWORD2
  CRGB::Blue  KEYWORD2
  CRGB::BlueViolet  KEYWORD2
  CRGB::Brown KEYWORD2
  CRGB::BurlyWood KEYWORD2
  CRGB::CadetBlue KEYWORD2
  CRGB::Chartreuse  KEYWORD2
  CRGB::Chocolate KEYWORD2
  CRGB::Coral KEYWORD2
  CRGB::CornflowerBlue  KEYWORD2
  CRGB::Cornsilk  KEYWORD2
  CRGB::Crimson KEYWORD2
  CRGB::Cyan  KEYWORD2
  CRGB::DarkBlue  KEYWORD2
  CRGB::DarkCyan  KEYWORD2
  CRGB::DarkGoldenrod KEYWORD2
  CRGB::DarkGray  KEYWORD2
  CRGB::DarkGreen KEYWORD2
  CRGB::DarkKhaki KEYWORD2
  CRGB::DarkMagenta KEYWORD2
  CRGB::DarkOliveGreen  KEYWORD2
  CRGB::DarkOrange  KEYWORD2
  CRGB::DarkOrchid  KEYWORD2
  CRGB::DarkRed KEYWORD2
  CRGB::DarkSalmon  KEYWORD2
  CRGB::DarkSeaGreen  KEYWORD2
  CRGB::DarkSlateBlue KEYWORD2
  CRGB::DarkSlateGray KEYWORD2
  CRGB::DarkTurquoise KEYWORD2
  CRGB::DarkViolet  KEYWORD2
  CRGB::DeepPink  KEYWORD2
  CRGB::DeepSkyBlue KEYWORD2
  CRGB::DimGray KEYWORD2
  CRGB::DodgerBlue  KEYWORD2
  CRGB::FireBrick KEYWORD2
  CRGB::FloralWhite KEYWORD2
  CRGB::ForestGreen KEYWORD2
  CRGB::Fuchsia KEYWORD2
  CRGB::Gainsboro KEYWORD2
  CRGB::GhostWhite  KEYWORD2
  CRGB::Gold  KEYWORD2
  CRGB::Goldenrod KEYWORD2
  CRGB::Gray  KEYWORD2
  CRGB::Green KEYWORD2
  CRGB::GreenYellow KEYWORD2
  CRGB::Honeydew  KEYWORD2
  CRGB::HotPink KEYWORD2
  CRGB::IndianRed KEYWORD2
  CRGB::Indigo  KEYWORD2
  CRGB::Ivory KEYWORD2
  CRGB::Khaki KEYWORD2
  CRGB::Lavender  KEYWORD2
  CRGB::LavenderBlush KEYWORD2
  CRGB::LawnGreen KEYWORD2
  CRGB::LemonChiffon  KEYWORD2
  CRGB::LightBlue KEYWORD2
  CRGB::LightCoral  KEYWORD2
  CRGB::LightCyan KEYWORD2
  CRGB::LightGoldenrodYellow  KEYWORD2
  CRGB::LightGreen  KEYWORD2
  CRGB::LightGrey KEYWORD2
  CRGB::LightPink KEYWORD2
  CRGB::LightSalmon KEYWORD2
  CRGB::LightSeaGreen KEYWORD2
  CRGB::LightSkyBlue  KEYWORD2
  CRGB::LightSlateGray  KEYWORD2
  CRGB::LightSteelBlue  KEYWORD2
  CRGB::LightYellow KEYWORD2
  CRGB::Lime  KEYWORD2
  CRGB::LimeGreen KEYWORD2
  CRGB::Linen KEYWORD2
  CRGB::Magenta KEYWORD2
  CRGB::Maroon  KEYWORD2
  CRGB::MediumAquamarine  KEYWORD2
  CRGB::MediumBlue  KEYWORD2
  CRGB::MediumOrchid  KEYWORD2
  CRGB::MediumPurple  KEYWORD2
  CRGB::MediumSeaGreen  KEYWORD2
  CRGB::MediumSlateBlue KEYWORD2
  CRGB::MediumSpringGreen KEYWORD2
  CRGB::MediumTurquoise KEYWORD2
  CRGB::MediumVioletRed KEYWORD2
  CRGB::MidnightBlue  KEYWORD2
  CRGB::MintCream KEYWORD2
  CRGB::MistyRose KEYWORD2
  CRGB::Moccasin  KEYWORD2
  CRGB::NavajoWhite KEYWORD2
  CRGB::Navy  KEYWORD2
  CRGB::OldLace KEYWORD2
  CRGB::Olive KEYWORD2
  CRGB::OliveDrab KEYWORD2
  CRGB::Orange  KEYWORD2
  CRGB::OrangeRed KEYWORD2
  CRGB::Orchid  KEYWORD2
  CRGB::PaleGoldenrod KEYWORD2
  CRGB::PaleGreen KEYWORD2
  CRGB::PaleTurquoise KEYWORD2
  CRGB::PaleVioletRed KEYWORD2
  CRGB::PapayaWhip  KEYWORD2
  CRGB::PeachPuff KEYWORD2
  CRGB::Peru  KEYWORD2
  CRGB::Pink  KEYWORD2
  CRGB::Plaid KEYWORD2
  CRGB::Plum  KEYWORD2
  CRGB::PowderBlue  KEYWORD2
  CRGB::Purple  KEYWORD2
  CRGB::Red KEYWORD2
  CRGB::RosyBrown KEYWORD2
  CRGB::RoyalBlue KEYWORD2
  CRGB::SaddleBrown KEYWORD2
  CRGB::Salmon  KEYWORD2
  CRGB::SandyBrown  KEYWORD2
  CRGB::SeaGreen  KEYWORD2
  CRGB::Seashell  KEYWORD2
  CRGB::Sienna  KEYWORD2
  CRGB::Silver  KEYWORD2
  CRGB::SkyBlue KEYWORD2
  CRGB::SlateBlue KEYWORD2
  CRGB::SlateGray KEYWORD2
  CRGB::Snow  KEYWORD2
  CRGB::SpringGreen KEYWORD2
  CRGB::SteelBlue KEYWORD2
  CRGB::Tan KEYWORD2
  CRGB::Teal  KEYWORD2
  CRGB::Thistle KEYWORD2
  CRGB::Tomato  KEYWORD2
  CRGB::Turquoise KEYWORD2
  CRGB::Violet  KEYWORD2
  CRGB::Wheat KEYWORD2
  CRGB::White KEYWORD2
  CRGB::WhiteSmoke  KEYWORD2
  CRGB::Yellow  KEYWORD2
  CRGB::YellowGreen KEYWORD2
  **/
