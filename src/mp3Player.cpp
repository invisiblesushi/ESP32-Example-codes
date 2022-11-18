#include <Arduino.h>
#include <Audio.h>
#include <SD.h>
#include <FS.h>

// SD card connections
#define SD_CS 5
#define SD_MOSI 23
#define SD_MISO 19
#define SD_CLK 18

// Max98357 I2S connections
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_LRC 25

// Audio object
Audio audio;

void setup() {
  // Initialize serial port
  Serial.begin(115200);

  // Initialize SD card
  pinMode(SD_CS, OUTPUT);      
  digitalWrite(SD_CS, HIGH); 
  SPI.begin(SD_CLK, SD_MISO, SD_MOSI);

  if(!SD.begin(SD_CS))
  {
    Serial.println("Error accessing microSD card");
    while(true); 
  }

  // Setup I2S 
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    
  // Set Volume
  audio.setVolume(64); //{ 0, 1, 2, 3, 4 , 6 , 8, 10, 12, 14, 17, 20, 23, 27, 30 ,34, 38, 43 ,48, 52, 58, 64}

  // Play mp3
  audio.connecttoFS(SD, "/sample.mp3");
}


void loop() {
  audio.loop();
}





