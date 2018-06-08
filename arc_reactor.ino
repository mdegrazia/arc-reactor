#include "Adafruit_FreeTouch.h"
#include "FastLED.h"

#define NEOPIXEL_SM_PIN 0
#define NEOPIXEL_LG_PIN 1


const byte interruptPin = 2;
volatile byte state = LOW;


#define NUM_LEDS_LG    24
#define NUM_LEDS_SM    16

#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

CRGB leds_sm[NUM_LEDS_SM];
CRGB leds_lg[NUM_LEDS_LG];

int BRIGHTNESS=150;


long oldState = 0;
int gHue=0;

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

unsigned long button_time = 0;  
unsigned long last_button_time = 0;
int x = 0;

int buttonPressCount=0;
volatile bool buttonPressed = false;
void setup() {
  Serial.begin(115200);
    
 
  // initialize the SWITCH pin as an input.
  
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  pinMode(LED_BUILTIN, OUTPUT);

   FastLED.addLeds<WS2812, NEOPIXEL_SM_PIN, COLOR_ORDER>(leds_sm, NUM_LEDS_SM);  // Set up neopixels with FastLED
   FastLED.addLeds<WS2812, NEOPIXEL_LG_PIN, COLOR_ORDER>(leds_lg, NUM_LEDS_LG);  // Set up neopixels with FastLED
   
   FastLED.setBrightness(BRIGHTNESS);
   FastLED.setMaxPowerInVoltsAndMilliamps(3,350);  //Constrain FastLED's power usage
   blue();
}

void loop() {

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button went from off to on:
      buttonPushCounter++;
      Serial.println("on");
      Serial.print("number of button pushes: ");
      Serial.println(buttonPushCounter);
    } else {
      // if the current state is LOW then the button went from on to off:
      Serial.println("off");
    }
    // Delay a little bit to avoid bouncing
    delay(50);
  }
  // save the current state as the last state, for next time through the loop
  lastButtonState = buttonState;

if (buttonPushCounter == 5){
  buttonPushCounter = 0;
}
switch(buttonPushCounter){
        case 0:
          blue();
          break;
        case 1:
          sinelon();
          break; 
          
        case 2:
          sinelon2();
          break;
        case 3:
          rainbow();
          break;
        case 4:
          dark();
          break;
}
  
 
}

void blink() {
 
 // read the pushbutton input pin:
 buttonState = digitalRead(interruptPin);
 buttonPressed = true; 
}

void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
 for(int i = 0; i < NUM_LEDS_LG; i++) { 
  leds_lg[i] = CRGB::Red; 
  if (buttonPressed == true){
              buttonPressed = false;
              break;
  }
 }


  fadeToBlackBy( leds_sm, NUM_LEDS_SM, 20);
  int pos2 = beatsin16( 13, 0, NUM_LEDS_SM-1 );
  leds_sm[pos2] += CHSV( gHue, 255, 192);
  FastLED.show();
  
  
  delay(20);
}

void sinelon2()
{
  // a colored dot sweeping back and forth, with fading trails
 for(int i = 0; i < NUM_LEDS_SM; i++) { 
  leds_sm[i] = CRGB::Red; 
  if (buttonPressed == true){
              buttonPressed = false;
              break;
  }
 }


  fadeToBlackBy( leds_lg, NUM_LEDS_LG, 20);
  int pos2 = beatsin16( 13, 0, NUM_LEDS_LG-1 );
  leds_lg[pos2] += CHSV( gHue, 255, 192);
  FastLED.show();
  
  delay(20);
}



void rainbow() 
{
  // FastLED's built-in rainbow generator
  fill_rainbow(leds_lg, NUM_LEDS_LG, gHue, 7);
  fill_rainbow(leds_sm, NUM_LEDS_SM, gHue, 7);
  FastLED.show();
  
  delay(20);
}

void dark()
{ 
  for(int i = 0; i < NUM_LEDS_SM; i++) { 
  leds_sm[i] = CRGB::Black; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);

  }

for(int i = 0; i < NUM_LEDS_LG; i++) { 
  leds_lg[i] = CRGB::Black; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);

  }

}

void blue()
{ 
  for(int i = 0; i < NUM_LEDS_SM; i++) { 
  leds_sm[i] = CRGB::Blue; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);
  }

  for(int i = 0; i < NUM_LEDS_LG; i++) { 
  leds_lg[i] = CRGB::Blue; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);
}
}


void red()
{ 
  for(int i = 0; i < NUM_LEDS_SM; i++) { 
  leds_sm[i] = CRGB::Red; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);
  }

  for(int i = 0; i < NUM_LEDS_LG; i++) { 
  leds_lg[i] = CRGB::Red; 
  FastLED.show();
  if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
  delay(20);
}

}
void chase(){
  for(int dot = 0; dot < NUM_LEDS_LG; dot++) { 
            leds_lg[dot] = CRGB::Blue;
            FastLED.show();
            // clear this led for the next time around the loop
            leds_lg[dot] = CRGB::Black;
            if (buttonPressed == true){
              buttonPressed = false;
              break;
            }
            delay(30);
        }
}


