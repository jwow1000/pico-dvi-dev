// Double-buffered 8-bit Adafruit_GFX-compatible framebuffer for PicoDVI.
// Animates without redraw flicker. Requires Adafruit_GFX >= 1.11.4

#include <PicoDVI.h>

// 8 bit double buffer
DVIGFX8 display(DVI_RES_320x240p60, true, adafruit_feather_dvi_cfg);

int16_t w,h;
int16_t count, bigCount;
float speed;
int8_t dir; 

// colors
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0 
#define WHITE    0xFFFF

void setup() { // Runs once on startup
  if (!display.begin()) { // Blink LED if insufficient RAM
    pinMode(LED_BUILTIN, OUTPUT);
    for (;;) digitalWrite(LED_BUILTIN, (millis() / 500) & 1);
  }
  
  w = display.width();
  h = display.height();
  dir = 1;
  speed = 1;
  
}

void loop() {
  count = count + (speed*dir);
  if( count > (w-10) ){
    dir = -1;
  }
  if(count<10){
    dir = 1;
  }
  // Clear back framebuffer and draw circle
  display.fillScreen(0);
  display.setColor(1, color_mixer(count,2,200));
  display.fillCircle(count, h/2, 20, 1);
  
  // Swap front/back buffers, do not duplicate current screen state to next frame,
  // we'll draw it new from scratch each time.
  display.swap();
}

uint16_t color_mixer(int int_r, int int_g, int int_b) {
  uint16_t mixed = ((int_r & 0xf8) << 8) + ((int_g & 0xfc) << 3) + (int_b >>3);
  return mixed;
}
