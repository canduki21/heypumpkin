#include "SoftwareSerial.h"
#include <Servo.h>
#include <Adafruit_NeoPixel.h>

#define ARDUINO_RX 4 // TX of the module
#define ARDUINO_TX 3 // RX of the module
#define PIN 10       // the NeoPixel strip in 9 
#define NUMPIXELS 25 // Number of NeoPixels
int ledPin1 = 7;
int ledPin2 = 8;

// Initializing the mp3 and pixels
SoftwareSerial myMP3(ARDUINO_RX, ARDUINO_TX);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Servo positions
Servo myServo; 
Servo myServo2; 

// Audios
bool audioPlayed1 = false; // Hey Candela, I'm a pumpkin
bool audioPlayed2 = false; // Moving left arm
bool audioPlayed3 = false; // Moving right arm
bool audioPlayed4 = false; // Turning off the lights
bool audioPlayed5 = false; // Turning on the lights
bool audioPlayed6 = false; // Halloween mode
bool audioPlayed7 = false; // America mode
bool audioPlayed8 = false; // Telling a joke
bool audioPlayed9 = false; // Saying bye 
bool audioPlayed10 = false; // Info about NFC and GitHub 
bool audioPlayed11 = false; // 
bool audioPlayed12 = false; // 
bool audioPlayed13 = false; // 
bool audioPlayed14 = false; // 

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  strip.begin(); // Initialize the NeoPixel strip
  changeStripColor(strip.Color(255, 255, 255)); // White
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

  // Attach the first servo to pin 5 and set it to 90 degrees
  myServo.attach(5);
  myServo.write(90); // Initial position
  delay(1000); // Wait for 1 second

  // Play audios and change LED colors
  playAudioSequence();
}

void loop() {
}

void playAudioSequence() {
  // LEFT ARM
  if (!audioPlayed1) {
    playAudio(0x02);  // Play 1st audio
    audioPlayed1 = true; 
    delay(4000); 
  }
  changeStripColor(strip.Color(0, 255, 0)); // Green
  delay(3000); // Wait for 2 seconds

  // RIGHT ARM
  if (!audioPlayed2) {
    playAudio(0x03); // Play the second song
    audioPlayed2 = true; 
  }
  delay(1000);
  myServo2.attach(6);
  myServo2.write(20); // Move the second servo
  delay(3000); // Wait for the movement
  myServo.write(60); // Move the servo
  delay(3000); // Wait for the movement
  myServo.write(90);
  myServo2.detach(); // Return to initial position
  delay(3000);

  // LED OFF
  changeStripColor(strip.Color(255, 100, 0)); // Orange
  delay(1000); // Wait for 1 second

  if (!audioPlayed3) {
    playAudio(0x04); // Play the third song
    audioPlayed3 = true; 
  }
  delay(4000);
  changeStripColor(strip.Color(153, 0, 153)); // Purple
  delay(2000);
  
  if (!audioPlayed4) {
    playAudio(0x05); // Play the fourth song
    audioPlayed4 = true; 
  }
  delay(2000);
  
  if (!audioPlayed5) {
    playAudio(0x06); // Play the fifth song
    audioPlayed5 = true; 
  }
  delay(3000);
  
  if (!audioPlayed6) {
    playAudio(0x07); // Play the sixth song
    audioPlayed6 = true; 
  }
  delay(3000);
  
  if (!audioPlayed7) {
    playAudio(0x01); // Play the seventh song
    audioPlayed7 = true; 
    delay(4000);
    myServo2.attach(6);
    myServo2.write(0); // Move the second servo
    delay(3000); // Wait for the movement
    myServo.write(30); // Move the servo
    delay(3000); // Wait for the movement
    myServo.write(90);
    myServo2.detach(); // Return to initial position
    delay(2000);
  }
  
  if (!audioPlayed8) {
    playAudio(0x08); // Play the eighth song
    audioPlayed8 = true; 
  }
  delay(3000);

  if (!audioPlayed9) {
    playAudio(0x09); // Play the ninth song
    audioPlayed9 = true; 
  }
  delay(3000);

  if (!audioPlayed10) {
    playAudio(0x0A); // Play the tenth song
    audioPlayed10 = true; 
  }
  delay(3000);

  if (!audioPlayed11) {
    playAudio(0x0B); // Play the eleventh song
    audioPlayed11 = true; 
  }
  delay(3000);

  if (!audioPlayed12) {
    playAudio(0x0C); // Play the twelfth song
    audioPlayed12 = true; 
  }
  delay(5000);
  
  if (!audioPlayed13) {
    playAudio(0x0D); // Play the thirteenth song
    audioPlayed13 = true; 
    startFlickering(); // Start flickering after this audio
  }
  delay(1000);
  
  if (!audioPlayed14) {
    playAudio(0x0E); // Play the fourteenth song
    audioPlayed14 = true; 
  }
  delay(3000);
}

// Function to set all NeoPixels to a specific color
void changeStripColor(uint32_t color) {
  for (int i = 0; i < NUMPIXELS; i++) {
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

// Function to flicker LEDs
void startFlickering() {
  for (int i = 0; i < 10; i++) { // Flicker 10 times
    changeStripColor(strip.Color(random(0, 255), random(0, 255), random(0, 255))); // Random vibrant colors
    delay(random(100, 500)); // Random delay between 100ms to 500ms
  }
  changeStripColor(strip.Color(0, 0, 0)); // Turn off LEDs after flickering
}
