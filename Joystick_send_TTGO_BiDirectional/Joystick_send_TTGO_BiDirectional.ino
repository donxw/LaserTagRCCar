/* Joystick

This program simply captures joystick every 10ms and sends to RCCar via espnow

for ttgo t display esp32
int const JOYSTICK_BTN = 17;
int const JOYSTICK_AXIS_X = 33;
int const JOYSTICK_AXIS_Y = 36;

On ESP32:
These pins do not support analog input when WiFi is in use: 00, 02, 04, 12, 13, 14, 15, 25, 26,
These ones do: 32, 33, 34, 35, 36, 39, Use one of these last 6 to connect your sensor.

For the TTGO T-Display, use board ESP32 Dev Module

*/

// TFT Display Libraries
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();  // tft instance
uint16_t fg = TFT_WHITE;
uint16_t bg = TFT_BLACK;
#define GFXFF 1
#define CF_NB07 &NotoSans_Bold7pt7b
#define CF_NB08 &NotoSans_Bold8pt7b
#define CF_NB15 &NotoSans_Bold15pt7b
#define CF_NB36 &NotoSans_Bold36pt7b


// ESP Now Libraries
#include <WiFi.h>
#include <esp_now.h>

// Sender MAC
// Car B 84:CC:A8:9A:EB:BB <- get from target car ESP8266 devboard
uint8_t mac_peer1[] = { 0x84, 0xCC, 0xA8, 0x9A, 0xEB, 0xBB };

esp_now_peer_info_t peer1;

struct SEND_DATA_STRUCTURE {
  //put your variable definitions here for the data you want to send
  //THIS MUST BE EXACTLY THE SAME ON THE OTHER ARDUINO
  int valX;
  int valY;
  int button;
};

//give a name to the group of data
SEND_DATA_STRUCTURE myMessage;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  //Serial.print("\r\nLast Packet Send Status:\t");
  //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// Set up Receiver - MUST MATCH SEND_DATA_STRUCTURE FROM 8266 STATION

struct RECEIVE_DATA_STRUCTURE {
  int score;
};

RECEIVE_DATA_STRUCTURE received;
bool newMessage = false;

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  memcpy(&received, incomingData, sizeof(received));
  newMessage = true;
  //Serial.println("newMessage received");
}

//ttgo t display - if WiFi.h is used, then only ADC0 (GPIO36), ADC3 (39), ADC4 (32), ADC5 (33) can be used.
int const JOYSTICK_BTN = 17;
int const JOYSTICK_AXIS_X = 33;
int const JOYSTICK_AXIS_Y = 36;

//===============================================================================
//  Initialization
//===============================================================================

void setup() {

  //Set all button pins as inputs with internal pullup resistors enabled.
  pinMode(JOYSTICK_BTN, INPUT_PULLUP);

  Serial.begin(9600);

  tft.begin();
  tft.setRotation(0);
  tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
  tft.fillScreen(TFT_DARKGREEN);
  tft.setFreeFont(CF_NB36);
  // set middle center font datum
  tft.setTextDatum(MC_DATUM);
  tft.setTextPadding(80);
  tft.drawString("?", 65, 120);

  WiFi.mode(WIFI_STA);

  // Get Mac Add
  Serial.print("\n");
  Serial.print("Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println("\nRC ESP-Now Receiver");

  // Initializing the ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Problem during ESP-NOW init");
    return;
  }

  memcpy(peer1.peer_addr, mac_peer1, 6);
  peer1.channel = 0;
  // Register the peer
  Serial.println("Registering a peer 1");
  if (esp_now_add_peer(&peer1) == ESP_OK) {
    Serial.println("Peer 1 added");
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}
//===============================================================================
//  Main
//===============================================================================
void loop() {
  // Check each button input and print the status to the Serial Monitor Window
  //Serial.print("\tJOYSTICK BTN="), Serial.print(digitalRead(JOYSTICK_BTN));
  myMessage.button = digitalRead(JOYSTICK_BTN);

  // Print the full X/Y joystick values (0-1023)
  //myMessage.valX = map(analogRead(JOYSTICK_AXIS_X), 0, 4096, 0, 1024);
  myMessage.valX = analogRead(JOYSTICK_AXIS_X);
  //Serial.print("\tX="), Serial.print(myMessage.valX);  //esp32 range - map to use with arduino uno reciever

  //myMessage.valY = map(analogRead(JOYSTICK_AXIS_Y), 0, 4096, 0, 1024);
  myMessage.valY = analogRead(JOYSTICK_AXIS_Y);
  //Serial.print("\tY="), Serial.println(myMessage.valY);

  esp_now_send(NULL, (uint8_t *)&myMessage, sizeof(myMessage));

  // Check if a new message has been received

  if (newMessage == true) {
    newMessage = false;
    Serial.printf("Score: %d \n", received.score);
    int life = 10 - received.score;
    Serial.printf("life: %d \n", life);
    if (life >= 7) {
      tft.setTextColor(TFT_WHITE, TFT_DARKGREEN);
      tft.fillScreen(TFT_DARKGREEN);
      tft.setFreeFont(CF_NB36);
      // set middle center datum
      tft.setTextDatum(MC_DATUM);
      tft.setTextPadding(80);
      tft.drawNumber(life, 65, 120);
    }
    if (life < 7 && life >= 4) {
      tft.setTextColor(TFT_WHITE, TFT_GREEN);
      tft.fillScreen(TFT_GREEN);
      tft.setFreeFont(CF_NB36);
      // set middle center datum
      tft.setTextDatum(MC_DATUM);
      tft.setTextPadding(80);
      tft.drawNumber(life, 65, 120);
    }
    if (life < 4 && life >= 1) {
      tft.setTextColor(TFT_WHITE, TFT_ORANGE);
      tft.fillScreen(TFT_ORANGE);
      tft.setFreeFont(CF_NB36);
      // set middle center datum
      tft.setTextDatum(MC_DATUM);
      tft.setTextPadding(80);
      tft.drawNumber(life, 65, 120);
    }
    if (life <= 0) {
      tft.setTextColor(TFT_WHITE, TFT_RED);
      tft.fillScreen(TFT_RED);
      tft.setFreeFont(CF_NB36);
      // set middle center datum
      tft.setTextDatum(MC_DATUM);
      tft.setTextPadding(80);
      tft.drawNumber(life, 65, 120);
    }
  }

  delay(50);
}
