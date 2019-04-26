#include <WS2812FX.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN    6

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 9

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
unsigned long time;
unsigned int effects[] = {1,   8,9,10,11,12,15,49,   19,20,21,22,23,45,46,50,55,   25,26,27,28,29,34,35,51,   3,4,5,6,7,13,14,16,17,18,30,31,32,33,36,37,38,40,41,42,43,44,47,51,52,53,54};
unsigned int arrIndex;
unsigned int calm_start = 1;
unsigned int calm_end = 7;
unsigned int psycho_start = 8;
unsigned int psycho_end = 16;
unsigned int strobo_start = 17;
unsigned int strobo_end = 24;
unsigned int run_start = 25;
unsigned int run_end = sizeof(effects)/sizeof(arrIndex)-1;

unsigned int startIndex;
unsigned int endIndex;

#define NOT_CONNECTED 0
#define CALM 1
#define PSYCHO 2
#define STROBO 3
#define RUN 4

unsigned int mode;

void setup() {
  ws2812fx.init();
  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(400);
  arrIndex = 0;
  ws2812fx.setMode(effects[arrIndex]);
  arrIndex++;
  ws2812fx.start();
  Serial.begin(9600);
  mode = RUN;
  time = millis();
}

void loop() {
  ws2812fx.service();
  if(millis()-time>8000){
    time=millis();
    if(mode==NOT_CONNECTED){
      startIndex=0;
      endIndex=0;
    }else if(mode==CALM){
      startIndex=calm_start;
      endIndex=calm_end;
    }else if(mode==PSYCHO){
      startIndex=psycho_start;
      endIndex=psycho_end;
    }else if(mode==STROBO){
      startIndex=strobo_start;
      endIndex=strobo_end;
    }else if(mode==RUN){
      startIndex=run_start;
      endIndex=run_end;
    }
    if((arrIndex>endIndex)||(arrIndex<startIndex)){
      arrIndex=startIndex;
    }
    ws2812fx.setMode(effects[arrIndex]);
    Serial.print("Effect number: ");
    Serial.print(effects[arrIndex]);
    Serial.print(" (");
    Serial.print(arrIndex);
    Serial.println(")");
    arrIndex++;
  }
}

