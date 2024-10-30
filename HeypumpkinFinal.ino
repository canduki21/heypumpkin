#include "SoftwareSerial.h"
#include <Servo.h>

#define ARDUINO_RX 4 // should connect to TX of the Serial MP3 Player module
#define ARDUINO_TX 3 // connect to RX of the module
SoftwareSerial myMP3(ARDUINO_RX, ARDUINO_TX);

Servo myServo; 
Servo myServo2; // Create a second Servo object
bool audioPlayed1 = false; // Flag for the first audio
bool audioPlayed2 = false; // Flag for the second audio
bool audioPlayed3 = false;
bool audioPlayed4 = false;
void setup() {
  
  myMP3.begin(9600);
  delay(500); // Allow everything to settle down
  
  // Select the TF Card
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x03); // Number of bytes excluding start and end byte
  myMP3.write(0x35); // Command: Select TF Card
  myMP3.write(0x01); // Data: TF Card
  myMP3.write(0xEF); // End byte
  delay(20);

  // Attach the first servo to pin 5 and set it to 0 degrees
  myServo.attach(5);
  myServo.write(90); // Initial position
  delay(1000); // Wait for 1 second

  // LEFT ARM
  if (!audioPlayed1) {
    
    myMP3.write(0x7E); // Start byte
    myMP3.write(0x04); // Number of bytes excluding start and end byte
    myMP3.write(0x41); // Command: Play song
    myMP3.write((byte)0x00); // First byte of data: root directory
    myMP3.write(0x03); // First file on the card
    myMP3.write(0xEF); // End byte

    audioPlayed1 = true; // Set the flag to indicate audio has been played
  }

  // Wait for the duration of the MP3 file
  delay(2000); // Adjust this if the first audio file is longer

  // Move the first servo
  myServo.write(80); // Move the servo
  delay(800); // Wait for the movement
  myServo.write(90); // Return to initial position
  delay(3000); // Allow some time before next action




  // RIGHT ARM
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x03); // Number of bytes excluding start and end byte
  myMP3.write(0x35); // Command: Select TF Card
  myMP3.write(0x01); // Data: TF Card
  myMP3.write(0xEF); // End byte
  delay(20);


  // Play the second song
  if (!audioPlayed2) {
    Serial.println("Play sound 2");
    myMP3.write(0x7E); // Start byte
    myMP3.write(0x04); // Number of bytes excluding start and end byte
    myMP3.write(0x41); // Command: Play song
    myMP3.write((byte)0x00); // First byte of data: root directory
    myMP3.write(0x02); // Second file on the card
    myMP3.write(0xEF); // End byte

    audioPlayed2 = true; // Set the flag to indicate second audio has been played
  }

  // Wait for the duration of the second MP3 file
  delay(2000); // Adjust this if the second audio file is longer
 myServo2.attach(6);
  myServo2.write(80); // Move the second servo
  delay(800); // Wait for the movement
   myServo2.detach();  
delay(3000);



  // led ON 
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x03); // Number of bytes excluding start and end byte
  myMP3.write(0x35); // Command: Select TF Card
  myMP3.write(0x01); // Data: TF Card
  myMP3.write(0xEF); // End byte
  delay(20);


  // Play the second song
  if (!audioPlayed3) {
    Serial.println("Play sound 2");
    myMP3.write(0x7E); // Start byte
    myMP3.write(0x04); // Number of bytes excluding start and end byte
    myMP3.write(0x41); // Command: Play song
    myMP3.write((byte)0x00); // First byte of data: root directory
    myMP3.write(0x05); // Second file on the card
    myMP3.write(0xEF); // End byte

    audioPlayed2 = true; // Set the flag to indicate second audio has been played
  }
delay(2000);
 pinMode(7, OUTPUT);
digitalWrite(7, HIGH);   
delay(3000);
  

// led OFF
  myMP3.write(0x7E); // Start byte
  myMP3.write(0x03); // Number of bytes excluding start and end byte
  myMP3.write(0x35); // Command: Select TF Card
  myMP3.write(0x01); // Data: TF Card
  myMP3.write(0xEF); // End byte
  delay(20);


  // Play the second song
  if (!audioPlayed4) {
    Serial.println("Play sound 2");
    myMP3.write(0x7E); // Start byte
    myMP3.write(0x04); // Number of bytes excluding start and end byte
    myMP3.write(0x41); // Command: Play song
    myMP3.write((byte)0x00); // First byte of data: root directory
    myMP3.write(0x04); // Second file on the card
    myMP3.write(0xEF); // End byte

    audioPlayed4 = true; // Set the flag to indicate second audio has been played
  }
delay(2000);
 pinMode(7, OUTPUT);
digitalWrite(7, LOW);  



 }

void loop() {
    
} 
