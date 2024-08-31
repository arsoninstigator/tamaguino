#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);

const int button1Pin = 9;
const int button2Pin = 8;
const int button3Pin = 7;

const int sound = 6;

int button1State = 0;
int button2State = 0;
int button3State = 0;

// making sprites


// splash 48x26
const unsigned char splash1 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x39, 0xc0, 0x00,
0x00, 0x00, 0x00, 0x39, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
0x00, 0x00, 0x00, 0x00, 0x07, 0xb9, 0xce, 0x78, 0x0f, 0xc0, 0x0f, 0xf9, 0xcf, 0xfc, 0x1f, 0xe0,
0x1f, 0xf9, 0xcf, 0xfe, 0x3f, 0xf0, 0x3c, 0x79, 0xcf, 0x1e, 0x38, 0x78, 0x38, 0x39, 0xce, 0x0e,
0x70, 0x38, 0x38, 0x39, 0xce, 0x0e, 0x70, 0x38, 0x38, 0x39, 0xce, 0x0e, 0x70, 0x38, 0x38, 0x39,
0xce, 0x0e, 0x70, 0x38, 0x38, 0x39, 0xce, 0x0e, 0x70, 0x38, 0x3c, 0x79, 0xce, 0x0e, 0x78, 0x70,
0x1f, 0xf9, 0xce, 0x0e, 0x3f, 0xf0, 0x0f, 0xf9, 0xce, 0x0e, 0x1f, 0xe0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x02, 0x00, 0x10, 0x00, 0x10, 0x25, 0x37, 0x53, 0x90, 0xe1, 0xb8, 0x29, 0x22,
0x51, 0xd0, 0x93, 0x90, 0x19, 0x22, 0x52, 0x50, 0x92, 0x10, 0x11, 0x23, 0x73, 0xd0, 0xf1, 0x98,
0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
//splash dino 80x40
const unsigned char splash2 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x39, 0xff, 0xe0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
0xe1, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfe, 0x3e, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x5e, 0xc1, 0xde, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7d, 0x80, 0x2f,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x07, 0xf4,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf5, 0xe0, 0x1f, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
0xaa, 0xbc, 0x7f, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3d, 0x55, 0x5f, 0xff, 0xa0, 0x00, 0x00,
0x00, 0x00, 0x00, 0xea, 0xaa, 0xaf, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x03, 0xd5, 0x55, 0xff,
0xfe, 0x80, 0x00, 0x00, 0x00, 0x00, 0x07, 0xab, 0xae, 0xbf, 0xfd, 0x00, 0x00, 0x00, 0x00, 0x00,
0x1f, 0x5f, 0xdf, 0xff, 0xfa, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xee, 0xfb, 0x6f, 0xf4, 0x00,
0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xf7,
0xff, 0xff, 0xd0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x00, 0x00,
0x00, 0x1f, 0xff, 0xff, 0xff, 0xfd, 0xc0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xdf, 0xff, 0xfe, 0xfe,
0x80, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xef, 0xef, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff,
0x9f, 0xdf, 0xff, 0xbf, 0x00, 0x00, 0x00, 0xff, 0xff, 0xfc, 0x1f, 0xa1, 0xfc, 0x7f, 0x80, 0x00,
0x0f, 0xff, 0xff, 0xe0, 0x1f, 0xb0, 0x03, 0xbf, 0x80, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x0f, 0xc0,
0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc8, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};


// front grass 32x10
const unsigned char grass_front [] PROGMEM = {
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x08, 0x89, 0xc0, 0x48, 0x5c, 0x50, 0x84,
0x9c, 0x48, 0x50, 0x22, 0x88, 0x80, 0x44, 0x22, 0x40, 0x84, 0x2e, 0x21, 0x49, 0x24, 0xa4, 0xb1,
};
//grass 2 (dino walking on) 4x8
const unsigned char grass [] PROGMEM = {
0xff, 0xee, 0xbb, 0x55, 0xaa, 0x11,
};

//trees
const unsigned char trees [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x10, 0x05, 0x00, 0x00, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x15, 0x00,
0x00, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x55, 0x40, 0x00, 0x55, 0x40, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x54, 0x15, 0x04, 0x40, 0x15, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x02, 0xa0, 0x00, 0x00, 0x01, 0x10, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
0x00, 0x28, 0x84, 0x24, 0x40, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x82, 0x00,
0x00, 0x01, 0x10, 0x00, 0x04, 0x40, 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x20, 0x00, 0x00, 0x00,
0x41, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x04, 0x40, 0x00, 0x88, 0x82, 0x40, 0x91, 0x04, 0x24,
0x41, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x44, 0x44, 0x11, 0x04, 0x10, 0x11, 0x04, 0x01, 0x00, 0x00,
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x02, 0x10, 0x00, 0x80, 0x00, 0x00, 0x08, 0x00, 0x04,
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x04, 0x00, 0x08, 0x00, 0x20, 0x00, 0x01, 0x00,
0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
};

const unsigned char mountains [] PROGMEM = {
0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04,
0x00, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
0x03, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f,
0x07, 0x74, 0x07, 0x80, 0x10, 0x00, 0x00, 0x80, 0x00, 0x06, 0x80, 0x00, 0x00, 0x00, 0x00, 0xd5,
0x0e, 0xc2, 0x0d, 0xc0, 0x28, 0x01, 0x01, 0xc1, 0x00, 0x1f, 0x40, 0x00, 0x00, 0x00, 0x01, 0x28,
0x1d, 0x13, 0x1b, 0x60, 0x54, 0x03, 0x83, 0xa3, 0x80, 0x36, 0x20, 0x00, 0x00, 0x00, 0x06, 0xd0,
0x3a, 0x41, 0xb4, 0x30, 0xe2, 0xcc, 0xf7, 0x57, 0xc0, 0xd8, 0x10, 0x00, 0x00, 0x00, 0x19, 0x20,
0x68, 0x84, 0x49, 0x19, 0xa1, 0x36, 0x5d, 0x2a, 0xa1, 0xa0, 0x10, 0x00, 0x00, 0x00, 0xe6, 0x40,
0xd2, 0x10, 0xa4, 0x0c, 0x80, 0x8c, 0x1a, 0x15, 0x57, 0x40, 0x88, 0x00, 0x00, 0x1f, 0x38, 0x80,
0x49, 0x08, 0x00, 0x06, 0x02, 0xc0, 0x24, 0x18, 0x0b, 0x80, 0x05, 0x0b, 0x8c, 0xe0, 0x23, 0x00,
0xa0, 0x20, 0x00, 0x11, 0x00, 0x00, 0x48, 0x84, 0x84, 0x02, 0x20, 0x5d, 0xf3, 0x00, 0xcd, 0xc0,
0x50, 0x00, 0x04, 0x04, 0x01, 0x44, 0x00, 0x00, 0x08, 0x00, 0x00, 0x30, 0x04, 0x07, 0x10, 0x20,
0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x40, 0x40, 0x00, 0x10,
0x40, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x81, 0x00, 0x00, 0x00, 0x01, 0x11, 0x01, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x00, 0x20, 0x02,
};


const unsigned char cloud2 [] PROGMEM = {
0x04, 0x70, 0x18, 0x00, 0x6e, 0xfb, 0x7c, 0xee, 0xff, 0xff, 0xfd, 0xff, 0x6f, 0xfb, 0x38, 0xee,
0x07, 0x70, 0x52, 0x00,
};


// walking sprites
// walk right
const unsigned char dinoWalk0 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x60, 0x00,
0x00, 0x00, 0x1f, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xb8, 0x00, 0x00, 0x00, 0x7b, 0xff,
0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xd8, 0x00, 0x00, 0x03, 0xff, 0x7f, 0xe0, 0x00, 0x00, 0x0f,
0xf7, 0xde, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xbc, 0x7a, 0x00, 0x00,
};
const unsigned char dinoWalk1 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x60, 0x00,
0x00, 0x00, 0x1f, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x37, 0xff, 0xb8, 0x00, 0x00, 0x00, 0x7f, 0xff,
0xfc, 0x00, 0x00, 0x00, 0xff, 0x7f, 0xd8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f,
0xbf, 0xda, 0x00, 0x00, 0x00, 0x7f, 0xf8, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x30, 0x18, 0x00, 0x00,
};
const unsigned char dinoWalk2 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x60, 0x00,
0x00, 0x00, 0x1b, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xb8, 0x00, 0x00, 0x00, 0x7f, 0x7f,
0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xd8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f,
0xbf, 0xfa, 0x00, 0x00, 0x00, 0x7f, 0x78, 0x3c, 0x00, 0x00, 0x00, 0x00, 0xf4, 0x5e, 0x00, 0x00,
};
// walk left
const unsigned char dinoWalk3 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0xe0, 0x00, 0x00,
0x00, 0x0f, 0x8f, 0xf8, 0x00, 0x00, 0x00, 0x1d, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xde,
0x00, 0x00, 0x00, 0x1b, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xfe, 0xff, 0xc0, 0x00, 0x00, 0x00,
0x7b, 0xef, 0xf0, 0x00, 0x00, 0x00, 0x3c, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x5e, 0x3d, 0x00, 0x00,
};
const unsigned char dinoWalk4 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0xe0, 0x00, 0x00,
0x00, 0x0f, 0x8f, 0xf8, 0x00, 0x00, 0x00, 0x1d, 0xff, 0xec, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xfe,
0x00, 0x00, 0x00, 0x1b, 0xfe, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
0x5b, 0xfd, 0xf0, 0x00, 0x00, 0x00, 0x3c, 0x1f, 0xfe, 0x00, 0x00, 0x00, 0x18, 0x0c, 0x00, 0x00,
};
const unsigned char dinoWalk5 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0xe0, 0x00, 0x00,
0x00, 0x0f, 0x8f, 0xd8, 0x00, 0x00, 0x00, 0x1d, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0xfe,
0x00, 0x00, 0x00, 0x1b, 0xff, 0xff, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00,
0x5f, 0xfd, 0xf0, 0x00, 0x00, 0x00, 0x3c, 0x1e, 0xfe, 0x00, 0x00, 0x00, 0x7a, 0x2f, 0x00, 0x00,
};

const unsigned char dinoJump [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xc0, 0x60, 0x00,
0x00, 0x00, 0x1f, 0xf1, 0xf0, 0x00, 0x00, 0x00, 0x3b, 0xff, 0xb8, 0x00, 0x00, 0x00, 0x7f, 0xdf,
0xfc, 0x00, 0x00, 0x00, 0xff, 0xff, 0xd8, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x0f,
0xff, 0xfe, 0x00, 0x00, 0x00, 0x7d, 0xf8, 0x1f, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x07, 0x80, 0x00,

};

const unsigned char obstacle1 [] PROGMEM = {
0x00, 0x00, 0x1e, 0x00, 0x2f, 0x00, 0x5e, 0x80, 0x5f, 0xc0, 0xb7, 0xc0,
};

const unsigned char obstacle2 [] PROGMEM = {
0x14, 0x00, 0x08, 0x00, 0x52, 0x00, 0x34, 0x00, 0x69, 0x40, 0xf0, 0x80,
};

const unsigned char poop [] PROGMEM = {
0x80, 0x88, 0x01, 0x81, 0x02, 0xe0, 0x27, 0x10, 0x0b, 0xf0, 0x1c, 0x08,
};


#define WALKSIZE 6
const unsigned char* dinoWalk[WALKSIZE] = {
      dinoWalk0,dinoWalk1,dinoWalk2,
      dinoWalk3,dinoWalk4,dinoWalk5
    };
int walkPos=0;
int walkXPos=0;
bool walkAnimReverse=false;
bool walkRight=false;
int walkDirOffset=2;


const unsigned char eating1 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 0x00,
0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00,
0x00, 0x03, 0x7c, 0x7f, 0xfe, 0x00, 0x00, 0x02, 0xf9, 0xff, 0xfe, 0x00, 0x00, 0x0c, 0xf3, 0xff,
0xff, 0x00, 0x00, 0x1f, 0xf4, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xf0, 0x7f, 0xff, 0xc0, 0x00, 0xff,
0xf8, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0,
0x1f, 0xe7, 0xff, 0xe0, 0xff, 0xe0, 0x3f, 0xdf, 0xff, 0xde, 0xff, 0xf0, 0x7f, 0xbf, 0xff, 0xbf,
0x7f, 0xf0, 0x7f, 0x7f, 0xfe, 0x77, 0xbf, 0xf8, 0x7f, 0x7f, 0xf9, 0xf7, 0xbf, 0xfc, 0x3f, 0xff,
0xe7, 0xef, 0xbf, 0xfe, 0x5f, 0xfe, 0x1f, 0x1f, 0xbf, 0xff, 0x67, 0xf1, 0xf9, 0x1f, 0xbf, 0xff,
0x38, 0x0f, 0xe8, 0x3f, 0xbf, 0xff, 0x1f, 0xff, 0xe0, 0x3f, 0xbf, 0xff, 0x0e, 0xfe, 0x40, 0xbf,
0x6f, 0xff, 0x04, 0x54, 0x00, 0xff, 0x57, 0xff, 0x00, 0x10, 0x01, 0xfe, 0xab, 0xff, 0x00, 0x18,
0x01, 0xfd, 0x55, 0xff, 0x00, 0x18, 0x05, 0xfa, 0xaa, 0xff, 0x00, 0x1d, 0x27, 0xf1, 0x55, 0x5f,
0x00, 0x0f, 0x7f, 0xe0, 0xaa, 0xaf, 0x00, 0x07, 0xff, 0x80, 0x55, 0x57, 0x00, 0x03, 0xfe, 0x00,
0x2a, 0xab, 0x00, 0x01, 0xf0, 0x00, 0x15, 0x55, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x00, 0x00,
0x00, 0x00, 0x05, 0x55, 0x00, 0x00, 0x00, 0x00, 0x02, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55,

};

const unsigned char eating2 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 0x00,
0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00,
0x00, 0x03, 0x7c, 0x7f, 0xfe, 0x00, 0x00, 0x02, 0xf9, 0xff, 0xfe, 0x00, 0x00, 0x0c, 0xf3, 0xff,
0xff, 0x00, 0x00, 0x1f, 0xf4, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xf0, 0x7f, 0xff, 0xc0, 0x00, 0xff,
0xf8, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0,
0x1f, 0xe7, 0xff, 0xe0, 0xff, 0xe0, 0x3f, 0xdf, 0xff, 0xde, 0xff, 0xf0, 0x7f, 0xbf, 0xff, 0xbf,
0x7f, 0xf0, 0x7f, 0x7f, 0xfe, 0x77, 0xbf, 0xf8, 0x7f, 0x7f, 0xf9, 0xf7, 0xbf, 0xfc, 0x3f, 0xff,
0xe7, 0xef, 0xbf, 0xfe, 0x5f, 0xfe, 0x1f, 0x1f, 0xbf, 0xff, 0x67, 0xf1, 0xf9, 0x1f, 0xbf, 0xff,
0x38, 0x0f, 0xe8, 0x3f, 0xbf, 0xff, 0x1f, 0xff, 0xe1, 0x7f, 0x3f, 0xff, 0x0e, 0xfe, 0x41, 0xfe,
0xef, 0xff, 0x04, 0xd4, 0x0b, 0xfd, 0x57, 0xff, 0x00, 0xd4, 0x0f, 0xfa, 0xab, 0xff, 0x00, 0x60,
0x9f, 0xf5, 0x55, 0xff, 0x00, 0x75, 0xff, 0xca, 0xaa, 0xff, 0x00, 0x3f, 0xff, 0x05, 0x55, 0x5f,
0x00, 0x1f, 0xfc, 0x02, 0xaa, 0xaf, 0x00, 0x07, 0xc0, 0x01, 0x55, 0x57, 0x00, 0x00, 0x00, 0x00,
0xaa, 0xab, 0x00, 0x00, 0x00, 0x00, 0x15, 0x55, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x00, 0x00,
0x00, 0x00, 0x05, 0x55, 0x00, 0x00, 0x00, 0x00, 0x02, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55,

};
const unsigned char eating3 [] PROGMEM = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff,
0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 0x00,
0x7f, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x01, 0xff, 0xff, 0xfc, 0x00,
0x00, 0x03, 0x7c, 0x7f, 0xfe, 0x00, 0x00, 0x02, 0xf9, 0xff, 0xfe, 0x00, 0x00, 0x0c, 0xf3, 0xff,
0xff, 0x00, 0x00, 0x1f, 0xf4, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xf0, 0x7f, 0xff, 0xc0, 0x00, 0xff,
0xf8, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xe0,
0x1f, 0xe7, 0xff, 0xe0, 0xff, 0xe0, 0x3f, 0xdf, 0xff, 0xde, 0xff, 0xf0, 0x7f, 0xbf, 0xff, 0xbf,
0x7f, 0xf0, 0x7f, 0x7f, 0xfe, 0x77, 0xbf, 0xf8, 0x7f, 0x7f, 0xf9, 0xf7, 0xbf, 0xfc, 0x3f, 0xff,
0xe7, 0xef, 0xbf, 0xfe, 0x5f, 0xfe, 0x1f, 0xdf, 0xbf, 0xff, 0x67, 0xf1, 0xff, 0x3f, 0xbf, 0xff,
0x38, 0x0f, 0xfc, 0xff, 0xbf, 0xff, 0x1f, 0xff, 0xf3, 0xff, 0x3f, 0xff, 0x0f, 0xff, 0xcf, 0xfe,
0xef, 0xff, 0x00, 0x38, 0x3f, 0xf9, 0x57, 0xff, 0x07, 0x83, 0xff, 0xea, 0xab, 0xff, 0x01, 0xff,
0xfe, 0x15, 0x55, 0xff, 0x00, 0xff, 0xf0, 0x0a, 0xaa, 0xff, 0x00, 0x3f, 0xc0, 0x05, 0x55, 0x5f,
0x00, 0x00, 0x00, 0x02, 0xaa, 0xaf, 0x00, 0x00, 0x00, 0x05, 0x55, 0x57, 0x00, 0x00, 0x00, 0x02,
0xaa, 0xab, 0x00, 0x00, 0x00, 0x01, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0xaa, 0xaa, 0x00, 0x00,
0x00, 0x00, 0x55, 0x55, 0x00, 0x00, 0x00, 0x00, 0x0a, 0xaa, 0x00, 0x00, 0x00, 0x00, 0x01, 0x55,

};


const unsigned char* eating[4] = {
      eating1,eating2,eating3,eating2
    };

const unsigned char apple [] PROGMEM = {
0x00, 0x01, 0xf0, 0x00, 0x07, 0xe0, 0x00, 0x0f, 0xe0, 0x3f, 0x1f, 0xc0, 0x00, 0xdf, 0x80, 0x00,
0x20, 0x00, 0x0f, 0xd7, 0xf0, 0x3f, 0xff, 0xfc, 0x7f, 0xff, 0xfe, 0x78, 0xff, 0xfe, 0xf0, 0x7f,
0xff, 0xe0, 0x7f, 0xff, 0xe0, 0xff, 0xff, 0xf1, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xff, 0xfe, 0x7f, 0xff, 0xfe, 0x3f, 0xff, 0xfc, 0x1f,
0xff, 0xf8, 0x0f, 0xff, 0xf0, 0x07, 0xc3, 0xe0,
};


const unsigned char steak [] PROGMEM = {
0x0f, 0xe0, 0x00, 0x3f, 0xf8, 0x00, 0x31, 0xfe, 0x00, 0x6e, 0x7f, 0x00, 0xd1, 0x7f, 0x80, 0xa0,
0xbf, 0x80, 0xa0, 0xbf, 0xc0, 0xa0, 0xbf, 0xc0, 0xd1, 0x3f, 0xc0, 0xae, 0xff, 0xe0, 0xd1, 0xff,
0xe0, 0xef, 0xff, 0xe0, 0x77, 0xff, 0xf0, 0x7b, 0xff, 0xd0, 0x3d, 0xff, 0x78, 0x1e, 0xf9, 0xfe,
0x0f, 0x67, 0xff, 0x07, 0x7f, 0xff, 0x03, 0x9f, 0xfc, 0x03, 0xc3, 0xf9, 0x01, 0xf8, 0xc3, 0x00,
0xff, 0x1e, 0x00, 0x1f, 0xfe, 0x00, 0x01, 0xfc,
};

//ground
int grassXPos=0;
float treesXPos=-20;
//sky
float couldsXPos=0;
const int sunRadius=3;
bool sunOrMoon = false;
const int moonShadow=2;
float sunXPos=-2*sunRadius;
//clouds
const int cloud1Width=32;
float cloud1XPos=display.width()+cloud1Width;
int stars [6][2];


// menus
bool menuOpened = false;
int menu=0;
int subMenu=1;
bool menuDepth=false;
bool justOpened=false;
#define MENUSIZE 8
#define STRING_SIZE 11

const char mainMenu[MENUSIZE][8][STRING_SIZE] PROGMEM = {
  {"food","apple","steak","water",NULL},
  {"game",NULL},
  {"sleep",NULL},
  {"clean",NULL},
  {"doctor",NULL},
  {"discipline",NULL},
  {"stats","hunger","happiness","health","discipline","weight","age",NULL},
  {"settings","sound",
    //"something",
    NULL
  },
};

/* ------- PET STATS ------- */

float hunger=100;
float happiness=100;
float health=100;
float discipline=100;
float weight=1;
float age=0;

//settings
bool soundEnabled=true;

int action=0;
int setting=0;

bool notification = false;
int notificationBlink=0;
bool dead=false;

bool sleeping=false;

//game
bool game=false;
bool paused=false;
bool gameOver=false;
int score = 0;
int hiScore = 0;
int level=0;
bool newHiScore = false;
bool jumping=false;
bool jumpUp=true;
int jumpPos=0;
bool obstacle1show = false;
bool obstacle2show = false;
int obstacle1XPos = 0;
int obstacle2XPos = 0;


float poopometer=0;
int poops [3] = {
  0,0,0,
};

#define ACTIVATED LOW

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);

  digitalWrite(button1Pin, HIGH);
  digitalWrite(button2Pin, HIGH);
  digitalWrite(button3Pin, HIGH);
  // pinMode(button1Pin, INPUT_PULLUP)

  pinMode(sound, OUTPUT);

  pinMode(13,OUTPUT);

  randomSeed(analogRead(0));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3d);
  display.clearDisplay();

  // splash
  display.setTextColor(WHITE);
  display.print(F(" anoushka presents"));
  display.drawBitmap(15, 24, splash1 , 48, 26, WHITE);
  display.drawBitmap(48, 24, splash2 , 80, 40, WHITE);
  display.display();

  //splash tone

  tone(sound,500,200);
  delay(200);
  tone(sound,1000,200);
  delay(400);
  tone(sound,700,200);
  delay(200);
  tone(sound,1100,200);

  delay(2200);
  // end splash


  display.clearDisplay();

}


void loop() {

  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);

      if(!dead){
          /* -------- MODIFY PET STATS -------- */
          // TODO: different gradients regarding to age
          if(sleeping){
            hunger-=0.00005;
            poopometer+=0.00005;
            if(happiness-0.0001>0){
              happiness-=0.0001;
            }
            health-=0.00005+countPoops()*0.0001;
            if(discipline-0.0001>0){
              discipline-=0.0001;
            }
          }else{
            hunger-=0.00025;
            poopometer+=0.00025;
            if(happiness-0.0002>0){
              happiness-=0.0002;
            }
            health-=0.0001+countPoops()*0.0001;
            if(discipline-0.0002>0){
              discipline-=0.0002;
            }
            //discipline-=0.02;
          }
          age+=0.0000025;
      
          //diarrhea :) for testing
          //poopometer+=0.005;
      
          //health-=1;
          //health-=countPoops()*0.0001;
          //health-=countPoops()*0.05;
      
          if(poopometer>=10){
            poopometer=countPoops();
            poops[round(poopometer)]=random(20,display.width()+32);
            if(soundEnabled){
              tone(sound,200,50);
            }
            poopometer=0;
          }

      if((hunger>19.99975 && hunger<20.00025) || (happiness>19.9998 && happiness<20.0002) || (health>19.9999 && health<20.0001) && soundEnabled){
            if(soundEnabled){
              tone(sound,200,50);
            }
          }
      
      
          if(hunger<=20 || countPoops()>0 || happiness<=20 || health<=20){
            notification=true;
          }
          if(hunger>20 && countPoops()==0 && happiness>20 && health>20){
            notification=false;
            digitalWrite(13,LOW);
          }
      
          if(hunger<=0 || health<=0 || happiness<=0){
            dead=true;
            if(soundEnabled){
              tone(sound,500,500);
              delay(550);
              tone(sound,400,500);
              delay(550);
              tone(sound,300,600);
            }
          }


    display.clearDisplay();
    display.setCursor(0,0);

 /* ------- BUTTON PRESS ACTIONS ------- */

    /* ------- BUTTON 1 - MENU ------- */
    if(button1State==ACTIVATED){

      // JUMP IN GAME
      if(game){

        if(!jumping && !paused){
          if(soundEnabled){
            tone(sound,200,50);
          }
          jumping=true;
        }

      }else{
        // MENU

        if(soundEnabled){
          tone(sound,300,80);
        }

        if(!menuOpened){
          menuOpened=true;
        }else{
          if(menuDepth){

            if((const char*)pgm_read_word(&(mainMenu[menu][subMenu+1]))==NULL){
              subMenu=1;
            }else{
              ++subMenu;
            }
            setting=100*(menu+1)+subMenu;
          }else{
            if(menu==MENUSIZE-1){
              menu=0;
            }else{
              ++menu;
            }

            if((const char*)pgm_read_word(&(mainMenu[menu][1]))!=NULL){
              subMenu=1;

              justOpened=true;
            }
            setting=100*(menu+1)+subMenu;
          }
        }

        delay(60);

      }


