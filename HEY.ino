#include "SoftwareSerial.h"
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define ARDUINO_RX 4 // TX of the module
#define ARDUINO_TX 3 // RX of the module
#define PIN 9       // the NeoPixel strip in 9 
#define NUMPIXELS 25 // Number of NeoPixels
int ledPin1 = 7;
int ledPin2 = 8;
//Initializing the mp3 and pixels
SoftwareSerial myMP3(ARDUINO_RX, ARDUINO_TX);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Servo positions
Servo myServo; 
Servo myServo2; 

//Audios
bool audioPlayed1 = false; // Hey Candela, im a pumpkin
bool audioPlayed2 = false; // Moving left arm
bool audioPlayed3 = false; // Moving right arm
bool audioPlayed4 = false; // turnin off the lights
bool audioPlayed5 = false; // turning on the lightd
bool audioPlayed6 = false; //halloween mode
bool audioPlayed7 = false; //america mode
bool audioPlayed8 = false; //telling a joke
bool audioPlayed9 = false; //saying bye 
bool audioPlayed10 = false; // info about nfc and github 


void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  strip.begin();      // Initialize the NeoPixel strip
  strip.show();       // Update the strip to turn off all pixels

changeStripColor(strip.Color(255, 0, 0)); // Red
  delay(1000);


  myMP3.begin(9600);
  delay(500); 
  
  // Select the TF Card
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x03); // Number of bytes excluding start and end byte
  myMP3.write(0x35); // Command: Select TF Card
  myMP3.write(0x01); // TF Card
  myMP3.write(0xEF); // End byte
  delay(20);

  // Attach the first servo to pin 5 and set it to 0 degrees
  myServo.attach(5);
  myServo.write(90); // Initial position
  delay(1000); // Wait for 1 second


  // LEFT ARM
  if (!audioPlayed1) {
    playAudio(0x03);  // Play 1st audio
    audioPlayed1 = true; 
  }

  delay(2000); 

  // Move the first servo
  myServo.write(80); // Move the servo
  delay(1000); // Wait for the movement
  myServo.write(90); // Return to initial position
  delay(3000); // Allow some time before next action


  // Change LEDs to another color before playing the second audio
  changeStripColor(strip.Color(0, 0, 255)); // Blue
  delay(1000); // Wait for 1 second

  // RIGHT ARM
  if (!audioPlayed2) {
    playAudio(0x02); // Play the second song
    audioPlayed2 = true; // Set the flag to indicate second audio has been played
  }

  // Wait for the duration of the second MP3 file
  delay(2000); // Adjust this if the second audio file is longer
  myServo2.attach(6);
  myServo2.write(80); // Move the second servo
  delay(800); // Wait for the movement
  myServo2.detach();  
  delay(3000);

  // led OFF
  changeStripColor(strip.Color(255, 140, 0)); // Orange
  delay(1000); // Wait for 1 second

  if (!audioPlayed3) {
    playAudio(0x04); // Play the third song
    audioPlayed3 = true; // Set the flag to indicate third audio has been played
  }
  delay(2000);

  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);   
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW); 
  delay(3000);
  

  // led ON
  changeStripColor(strip.Color(255, 0, 255)); // Purple
  delay(1000); // Wait for 1 second

  if (!audioPlayed4) {
    playAudio(0x05); // Play the fourth song
    audioPlayed4 = true; // Set the flag to indicate fourth audio has been played
  }
  delay(4000);

   pinMode(8, OUTPUT);
  digitalWrite(8, HIGH); 
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH); 

}

void loop() {    
}

// Function to set all NeoPixels to a specific color
void changeStripColor(uint32_t color) {
  for(int i=0; i<NUMPIXELS; i++) {
    strip.setPixelColor(i, color); 
  }
  strip.show(); 

  digitalWrite(ledPin1, HIGH);
 digitalWrite(ledPin2, HIGH);
}

// Function to play an audio file
void playAudio(byte trackNumber) {
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x04); // Number of bytes excluding start and end byte
  myMP3.write(0x41); // Command: Play song
  myMP3.write((byte)0x00); // First byte of data: root directory
  myMP3.write(trackNumber); // Specific file on the card
  myMP3.write(0xEF); // End byte
}

