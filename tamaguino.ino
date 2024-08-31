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
