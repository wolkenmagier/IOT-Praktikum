#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


volatile uint8_t count = 0;
int state = 0;

void setup() {
  // put your setup code here, to run once:
 count = 0;
 state = 0; 
 
 //state 0: initial state.
 //state 1: When at outer sensor.
 //state 2: when at inner sensor.
 //state 0 --> 1 --> 2 count++
 //state 0 --> 2 --> 1 count--

 const byte interruptOuter = 10; //Grey, EINT2
 pinMode(interruptOut, INPUT_PULLDOWN);
 attachInterrupt(digitalPinToInterrupt(interruptOuter), outerSensor, HIGH);

 const byte interruptInner = 11; //Grey, EINT0
 pinMode(interruptInner, INPUT_PULLDOWN);
 attachInterrupt(digitalPinToInterrupt(interruptInner), innerSensor, HIGH);

 SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
 __DSB();
 __WFI();
}

void (outerSensor){
  
  if(state == 0){
    state = 1;
  
  } else if(state == 2){
      count--;
      state = 0;

    } else if(state == 1){
        //something wrong.
      }
}

void (innerSensor){
  if(state == 0){
    state = 2;
    
  } else if(state == 1){
      count++;
      state = 0;
  } else if(state == 2){
      //something wrong.
  }
}

void loop() {
  
}
