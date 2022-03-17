#include <Adafruit_GrayOLED.h>
#include <gfxfont.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
//#include <Vector2.hpp>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>


// Declare LCD object for software SPI
// Adafruit_PCD8544(CLK,DIN,D/C,CE,RST);
Adafruit_PCD8544 display = Adafruit_PCD8544(7, 6, 5, 4, 3);

//mario position
bool gg;
unsigned int lives = 3;
unsigned int score;
unsigned long playerX;
unsigned long playerY;
unsigned int mapWidth;
unsigned int i;
unsigned int minY;
unsigned int mapType;

unsigned int mapWidth1;
unsigned int mapWidth2;
bool yesCol;
bool didFall;
unsigned int dist;

//inputx
bool mvmt;
unsigned int jump;
bool iteration;
int statusA;
signed int VRx = A1;
signed int VRy = A0;
 unsigned int xPosition;
 unsigned int xPosition2;
unsigned int yPosition;
signed int xDir;
signed int offset;
signed int yoffset;
int last_posX;
bool inAir;
int last_posY;

unsigned int yDir;
unsigned int start;
unsigned int rBound;
unsigned int moveDir;
unsigned int jmpFrame;
#define a2 A2
#define a3 A3

unsigned int xMax  = display.width()/2+2;
unsigned int xMin  = 0;



const unsigned char map1 [] PROGMEM = {
  0xff, 
  0x89, 
  0x89, 
  0xff, 
  0x91, 
  0x91, 
  0x91, 
  0xff};

const unsigned char map2 [] PROGMEM = {
0xff, 
0x47, 
0x47, 
0x47, 
0x47, 
0xff, 
0x26, 
0x26};

const unsigned char MarioLeft [] PROGMEM = {
0x00, 0x00, 0x07, 0xe0, 0x18, 0x10, 0x23, 0xc8, 0x1d, 0x38, 0x21, 0x64, 0x22, 0x64, 0x1f, 0x18, 
  0x08, 0x30, 0x07, 0xc8, 0x09, 0x84, 0x0f, 0xf4, 0x0d, 0x88, 0x0e, 0x48, 0x04, 0x30, 0x03, 0xe0
};

const unsigned char clearFrame [] PROGMEM = {
  0x00, 0x00, 
  0x00, 0x00 
};

const unsigned char marioJump [] PROGMEM = {
  0x07, 0xce, 
  0x08, 0x31, 
  0x11, 0xc9, 
  0x1e, 0xba, 
  0x26, 0x86, 
  0x26, 0x46, 
  0x18, 0xfc, 
  0x0c, 0x14, 
  0x3f, 0xe8, 
  0x71, 0x9e, 
  0x89, 0x69, 
  0x8b, 0xf1, 
  0x7f, 0xf2, 
  0x8f, 0xf2, 
  0x9f, 0x8c, 
  0x6e, 0x00
};

const unsigned char marioWalk [] PROGMEM = {
  0x07, 0xc0, 
  0x08, 0x38, 
  0x13, 0xc4, 
  0x1c, 0xb8, 
  0x26, 0x84, 
  0x26, 0x44, 
  0x18, 0xf8, 
  0x1c, 0x10, 
  0x63, 0xf8, 
  0x91, 0x9c, 
  0x8b, 0xfa, 
  0x4f, 0x6a, 
  0x3f, 0xf4, 
  0x4f, 0xc4, 
  0x44, 0x88, 
  0x38, 0x70
};

const unsigned char coin [] PROGMEM = {
  0x38, 0x44, 0x54, 0x92, 0x92, 0x96, 0x44, 0x38
};

const unsigned char marioLeft [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x18, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x08, 0x30, 
  0x07, 0xc8, 
  0x09, 0x84, 
  0x0f, 0xf4, 
  0x0d, 0x88, 
  0x0e, 0x48, 
  0x04, 0x30, 
  0x03, 0xe0  
};

const unsigned char marioWalkLeft [] PROGMEM = {
 0x03, 0xe0, 
 0x1c, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x78, 0x3e, 
  0x97, 0xc9, 
  0x99, 0x89, 
  0x5f, 0xca, 
  0x36, 0xfc, 
  0x2f, 0xfc, 
  0x23, 0xf2, 
  0x11, 0x22, 
  0x0e, 0x1c
};

const unsigned char marioJumpLeft [] PROGMEM = {
  0x73, 0xe0, 
  0x8c, 0x10, 
  0x93, 0x88, 
  0x5d, 0x78, 
  0x61, 0x64, 
  0x62, 0x64, 
  0x3f, 0x18, 
  0x28, 0x30, 
  0x17, 0xfc, 
  0x79, 0x8e, 
  0x96, 0x91, 
  0x8f, 0xd1, 
  0x4f, 0xfe, 
  0x4f, 0xf1, 
  0x31, 0xf9, 
  0x00, 0x76  
};

const unsigned char marioStandLeft [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x18, 0x10, 
  0x23, 0xc8, 
  0x1d, 0x38, 
  0x21, 0x64, 
  0x22, 0x64, 
  0x1f, 0x18, 
  0x08, 0x30, 
  0x07, 0xc8, 
  0x09, 0x84, 
  0x0f, 0xf4, 
  0x0d, 0x88, 
  0x0e, 0x48, 
  0x04, 0x30, 
  0x03, 0xe0
};

const unsigned char block1 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x26, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x1a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x18, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x01, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x80, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x20, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x42, 0x60, 0x00, 0x08, 0x4c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0xa0, 0x00, 
  0x10, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x81, 0x10, 0x00, 0x30, 0x22, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x80, 0x18, 0x00, 0xf0, 0x03, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x08, 0x00, 0x04, 
  0x01, 0x00, 0x00, 0x80, 0x01, 0x4a, 0xa4, 0x00, 0x08, 0x00, 0x02, 0x01, 0x00, 0x00, 0x40, 0x01, 
  0x4a, 0xa4, 0x00, 0x08, 0x00, 0x02, 0x01, 0x00, 0x00, 0x40, 0x01, 0x4a, 0xa4, 0x00, 0x0c, 0x00, 
  0x04, 0x01, 0x80, 0x00, 0x80, 0x01, 0x4a, 0xa4, 0x00, 0x03, 0xff, 0xf8, 0x00, 0x7f, 0xff, 0x00, 
  0x01, 0x4a, 0xa4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x4a, 0xa4, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
  0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0
};

const unsigned char block2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char Mario [] PROGMEM = {
  0x00, 0x00, 
  0x07, 0xe0, 
  0x08, 0x18, 
  0x13, 0xc4, 
  0x1c, 0xb8, 
  0x26, 0x84, 
  0x26, 0x44, 
  0x18, 0xf8, 
  0x0c, 0x10, 
  0x13, 0xe0, 
  0x21, 0x90, 
  0x2f, 0xf0, 
  0x11, 0xb0, 
  0x12, 0x70, 
  0x0c, 0x20, 
};


struct Collisions {
  unsigned int xCor;
  unsigned int yCor;  
};

struct Collisions allCol[4];
struct Collisions coinCol[4];

void checkCollisions() {
  Serial.println("Collision Start");
  for (unsigned int l = 0; l<4; l++) {
    Serial.println("Collsion1");

    //if ((coinCol[l].xCor == last_posX) && (coinCol[l].yCor == last_posY) )
    if ((coinCol[l].xCor == last_posX)) {
        if (coinCol[l].xCor != 0 ) {
          score += 2;
        }
        coinCol[l].xCor = 0;
        coinCol[l].yCor = 84;
        Serial.println("Score");
        Serial.println(score);
    }
    
    //Serial.println(last_posX);
    if ((allCol[l].xCor == last_posX) || (allCol[l].xCor+16 >= last_posX)) {
      Serial.println("Collsion2");
      if (allCol[l].yCor > last_posY-1) {
        Serial.println("Collision Detected");
        
        //a elevated platform is present
        minY = allCol[l].yCor;
        yesCol = 1;
        break;
      }
      
    }
    else {
      yesCol = 0;    
    }
       
  }
  
}

void drawPlayer() {
//  if (yesCol) {
//              Serial.println("yesCol");
//              playerY = minY;
//              last_posY = minY;
//            }
           
  //non jumping animations
  if (!inAir) {
    
    if (xDir == 0) {
        display.drawBitmap(last_posX, last_posY,  Mario, 16, 16, 1);  

//        display.drawBitmap(21, 18,  Mario, 16, 16, 1); 
//        display.drawBitmap(45, 10,  Mario, 16, 16, 1);   
//        display.drawBitmap(20, 25,  Mario, 16, 16, 1); 
//        Serial.println(last_posX);
//        Serial.println(last_posY);
          
      }
    //walking to the right
    
    else if (xDir == 1) {
      display.drawBitmap(last_posX, last_posY,  marioWalk, 16, 16, 1);
      
       if (!yesCol) {
              Serial.println("!yesCol");
              if (mapType == 2) {
                Serial.println("fall");
                last_posY = display.height();
                gg = 1;
              }
            }
 
//      Serial.println(last_posX);
      xDir = 0;
      //dist++;
    }
    //walking to the left
    else {
      if (!mvmt) {
        display.drawBitmap(last_posX, last_posY,  marioStandLeft, 16, 16, 1);
         if (!yesCol) {
              Serial.println("!yesCol");
              if (mapType == 2) {
                Serial.println("fall");
                last_posY = display.height();
                gg = 1;
              }
            }
 
      }
      else {
        display.drawBitmap(last_posX, last_posY,  marioWalkLeft, 16, 16, 1);  
        mvmt = 0;
         if (!yesCol) {
              Serial.println("!yesCol");
              if (mapType == 2) {
                Serial.println("fall");
                last_posY = display.height();
                gg = 1;
              }
            }
 
       // dist--;
      }     
    }
  }
  else {
    if (jmpFrame <= 2) {
//      Serial.println("first 2 jmp frame should display twice: ");
//      Serial.println(last_posY);
      
      if ((xDir == 1) || (xDir == 0)) {
//         Serial.println("Display Jump");
        display.drawBitmap(last_posX, last_posY,  marioJump, 16, 16, 1);
      }
      if (xDir == -1) {
//        Serial.println("Jump Left 1");
//        Serial.println(last_posX);
        display.drawBitmap(last_posX, last_posY,  marioJumpLeft, 16, 16, 1);
      }
      
      jmpFrame += 2;  
      }
   // }
    //jmpFrame++;
    if (jmpFrame > 2) {
//      Serial.println("last 2 jmp frame should display twice: ");
      
      if (jmpFrame == 4) {
        //Serial.println("jmp=2");
        yDir = 0;
      }
       // reset y movement
      jmpFrame += 2; 
      //Serial.println(jmpFrame); 
      
//      last_posY += 10;
      if (yesCol) {
        Serial.println("yesCol");
        playerY = minY;
        last_posY = minY;
      }
      if (!yesCol) {
        Serial.println("!yesCol");
        if (mapType == 2) {
          Serial.println("fall");
          last_posY = display.height();
          gg = 1;
        }
      }
//      Serial.println(last_posY);
      
//      if ((xDir == 1) || (xDir == 0)) {
////        Serial.println("Draw final col");
////        Serial.println(minY);
//        display.drawBitmap(last_posX, last_posY,  marioJump, 16, 16, 1);
//      }
//      if (xDir == -1) {
////        Serial.println("Jump Left 2");
////        Serial.println(last_posX);
//        display.drawBitmap(last_posX, last_posY,  marioJumpLeft, 16, 16, 1);
//      }
      
      if (jmpFrame >= 8) {
        inAir = 0;
        jmpFrame = 0;
      }
    }
  }
  //Serial.println("Player Drawn");
}

void drawMap() {
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("score: ");
   display.print(score);
  
  if (dist < 23) {
    display.drawBitmap(mapWidth+6, -24,  block2, 84, 84, BLACK);

    
    for (unsigned int v = 0; v<2; v++) {
      display.drawBitmap(coinCol[v].xCor, coinCol[v].yCor,  coin, 8, 8, BLACK);
    }

    
  }
  if ((dist > 23)) {
      display.drawBitmap(mapWidth+8, -24,  block2, 84, 84, BLACK);
      display.drawBitmap(mapWidth+76, -24,  block1, 84, 84, BLACK);
  }
}



typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
} task;

const unsigned short tasksNum = 1;
task tasks[tasksNum];

enum Player_States {Player_init,Player_draw,Player_movement, Player_Move,Player_yMove, Player_update, Player_gg,Player_win};

int TickFct_Player(int state) { 
  switch(state) {
    case Player_init:
    
    break;

    case Player_update:
       
       display.clearDisplay(); 

       //game win 
       if (dist == 46) {
        state = Player_win;
        break;
       }

       if (digitalRead(a3) == HIGH) {
          state = Player_init;
          break;
       }

       

        drawMap();
        drawPlayer();

        if (gg) {
          state = Player_gg;
          break;
        }

        //mid Air
        if (yDir == 1) {
          state = Player_Move;
//          Serial.println("Mid air");
          break;
        }
//       Serial.println("y:");
//       Serial.println(last_posY);
        //movement is present
        //Serial.println(xPosition);
        if (digitalRead(a2) == HIGH) {
          Serial.println("HIGH");
          delay(300);
          if (digitalRead(a2) == LOW) {
            Serial.println("LOW");
            yDir = 1; //recognize a jump is happening 
            inAir = 1;
            state = Player_Move;
            //break;
            
          }
          //mvmt = 1;
        }
        
        if ((analogRead(VRx) > 900)) {
          Serial.println("Right Joystick Detected");
          dist++;
          if (dist>23) {
            mapType = 0;
            last_posY = display.height()-18;
          }
          //Serial.println(dist);
          xDir = 1;
          mvmt = 1;
          state = Player_Move;
          //break;
        }
        
        if (analogRead(VRx) < 100) {
          xDir = -1;
          if (dist > 8) {
            dist--;
          }
          mvmt = 1;
          //Serial.println(dist);
          state = Player_Move;
          
          break;  
        }

       

    break;

    case Player_draw:

    break;

//    case Player_movement:
//       //Serial.println("Player_movement1");
//
//      //todo: input controls
//      xPosition = analogRead(VRx);
//      yPosition = analogRead(VRy);
//      //Serial.println(xPosition);
//      //start = 0;
//      
//      
//      //right movement
//      if (xPosition > 800) {
//        break;
//      }
//
//      if (xPosition < 450) {
//        Serial.println("xmove1L");
//        xDir = -1; // movement left
//        //Serial.println(xDir);
//        mvmt = 1;
//        //mvmt = 1;
//        state = Player_Move;
//        break;
//
//        
//      }
//      Serial.println("y dire: ");
//     // Serial.print(xDir);
//      if (digitalRead(a2) == HIGH) {
//        Serial.println("Jump Detected");
//        yDir = 1;
//        mvmt = 1;
//        state = Player_yMove;
//        break;
//      }
//      xDir = 0;
//      moveDir = 0;
//      state = Player_draw;
//    break;
//
//    case Player_yMove:
//    break;

    default:
    break;
    }




    

  switch(state) {
    case Player_init:

      //default position left of the screen
      //Serial.println("Player_init2");
    //display.clearDisplay();
    
    
    
      Serial.println("Successful init");
      
      playerX = 1;
      playerY = 25;
      minY = playerY;
      last_posY = playerY;

      gg = 0;
      mapWidth = 0;
      mapType = 2;
      yesCol = 1;
      didFall = 0;
      dist = 10;
      //lives = 3;
      mvmt = 0;
      jump = 0;
      iteration = 0;
      statusA = 0;
      VRx = A1;
      VRy = A0;
       xPosition = 0;
       xPosition2 = 0;
       yPosition = 0;
      xDir = 0;
      offset = 4;
       yoffset = 8;
      last_posX = 1;
      inAir = 0;
      last_posY;
      
       yDir=0;
       start = 0;
       rBound = 80;
       moveDir = 0;
       jmpFrame = 0;
       score = 0;
       
       allCol[0].xCor = 1;
      allCol[0].yCor = 25; 
      allCol[1].xCor = 25;
      allCol[1].yCor = 17;
      allCol[2].xCor = 45;
      allCol[2].yCor = 10;

      //COINS
      coinCol[0].xCor = 33;
      coinCol[0].yCor = 17; 
      coinCol[1].xCor = 57;
      coinCol[1].yCor = 10;
//      coinCol[2].xCor = 45;
//      coinCol[2].yCor = 10;

      state = Player_update;
    break;

    case Player_draw:
      
      state = Player_movement;
    break;

    case Player_Move:
        //Serial.println("Calculate Movement");
        //last_posX = ((playerX*0.6)/8);
        if ((xDir != 0) || ((xDir == -1) && (mvmt == 0))) {
          Serial.println("Distance: ");
          Serial.println(dist);
//          Serial.println("X: ");
//          Serial.println(last_posX);
          if ((dist > 8) && (dist < 23)) {
//            Serial.println("yur");
            offset *= xDir;
            last_posX = playerX+offset;
//            if (mapType == 2) {
//              for (unsigned int v = 0; v<2; v++) {
//                display.drawBitmap(coinCol[v].xCor, coinCol[v].yCor,  coin, 8, 8, BLACK);
//                coinCol[v].xCor = coinCol[v].xCor + offset;
//                coinCol[v].yCor = coinCol[v].yCor + offset;
//              }
//            }
    //        last_posX *= xDir;
            playerX = last_posX;
            offset *= xDir;
          }
          
          if (dist>23) {
//            if ((dist == 47) || (dist == 42)) {
//            minY = display.height()-18;
//            if (dist == 42) {
//              mapWidth = 0;
//            }
            if (xDir == 1) {
              mapWidth-=4;
            }
            if (xDir == -1) {
//              Serial.println("print back");
              mapWidth+=4;
            }
          }
        }

        if (yDir == 1) {
//          Serial.println("Calculate Y");
//          Serial.println(last_posY);
//          Serial.println(playerY);
          //offset *= yDir;
          last_posY = playerY-(yoffset);
//          Serial.println(last_posY);
          playerY = last_posY;
//          Serial.println(last_posY);
          //offset *= yDir;  
        }
        checkCollisions();
        state = Player_update;
        //Serial.println(last_posX);
    break;

    case Player_gg:

      if (lives > 0) {
        display.clearDisplay();
         display.println(" ");
      display.print("   lives: ");
      display.print(lives);
      display.display();
      delay(1500);
      lives--;
//      gg = 0;
      }
      else {
        display.clearDisplay();
        display.println(" ");
        display.println("   Lose!");
        display.println("   reset to");
        display.println("   continue");
        while (digitalRead(a3) == LOW) {
          display.display();
        }
        lives = 3;
      }
//      lives = 3;
      gg = 0;
      state = Player_init;

   break;

   case Player_win:
    display.println(" ");
    display.println("   You win!");
    display.println("   reset to");
    display.println("   continue");
    while (digitalRead(a3) == LOW) {
    display.display();
    }
    state = Player_init;
   break;

    default:
    break;
    }

    return state;
}
 
 

    
  


void setup() {
   xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(a2, INPUT);
  pinMode(a3, INPUT);
  
  i = 0;
  tasks[i].state = Player_init;
  tasks[i].period = 50;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &TickFct_Player; 
  
  // Print a message to the LCD.
  //lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // print the number of seconds since reset:
   Serial.begin(9600);

  //Initialize Display
  display.begin();
  


  // you can change the contrast around to adapt the display for the best viewing!
  display.setContrast(57);

  if (statusA == 0) {
  display.clearDisplay();
    statusA++;
  }
  //Serial.println("start");
  
  for (i = 0; i < tasksNum; ++i) {
    if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
    }
  }
  delay(200);
}
