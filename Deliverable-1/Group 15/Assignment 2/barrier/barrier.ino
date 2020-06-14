#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

volatile uint8_t count = 0;
int state = 0;
const byte interruptOuter = 9; //Grey, EINT2
const byte interruptInner = 11; //Grey, EINT7
int block = 0;
unsigned long lastInterrupt;
void showRoomState(int count){
 Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 
  // put your main code here, to run repeatedly:
 if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address for 128x64
 Serial.println(F("SSD1306 allocation failed"));
 for(;;); // Don't proceed, loop forever
 }
 display.setTextColor(SSD1306_WHITE); // Draw white text
 display.cp437(true); // Use full 256 char 'Code Page 437' font
 display.clearDisplay();
 display.write("G15");
 display.setCursor(0, 30); //(x,y)
 display.setTextSize(2);
 display.print(count);

 // Show the display buffer on the screen. You MUST call display() after
 // drawing commands to make them visible on screen!
 display.display();
}

void setup() {
  // put your setup code here, to run once:
 count = 0;
 state = 0; 
 block = 0;
 //state 0: initial state.
 //state 1: When at outer sensor.
 //state 2: when at inner sensor.
 //state 0 --> 1 --> 2 count++
 //state 0 --> 2 --> 1 count--

  
 pinMode(interruptOuter, INPUT_PULLDOWN);
 attachInterrupt(digitalPinToInterrupt(interruptOuter), outerSensor, HIGH);

 
 pinMode(interruptInner, INPUT_PULLDOWN);
 attachInterrupt(digitalPinToInterrupt(interruptInner), innerSensor, HIGH);

// SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
// __DSB();
// __WFI();
}

void outerSensor(){
  if (millis() - lastInterrupt > 10){
    if(state == 0){
      state = 1;
      Serial.print("Person Entering");
      Serial.print(" - Block:");
      Serial.println(block);
      lastInterrupt = millis();
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
      return;
    
    } else if(state == 2){
        count--;
        state = 0;
        block = 1;
        Serial.print("Person Exited");
        Serial.print(" - Block:");
        Serial.println(block);
        lastInterrupt = millis();
//        REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//        REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
        
        return;
  
      } else if(state == 1){
          //something wrong.
          return;
        }
  }
  else
  {
    block = 1;
  }
}

void innerSensor(){
  if (millis() - lastInterrupt > 10){
    if(state == 0){
      state = 2;
      Serial.print("Person Exiting");
      Serial.print(" - Block:");
      Serial.println(block);
      lastInterrupt = millis();
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
      return;
      
    } else if(state == 1){
        block = 1;
        count++;
        state = 0;
        Serial.print("Person Entered");
        Serial.print(" - Block:");
        Serial.println(block);
        lastInterrupt = millis();
//        REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//        REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
        
        return;
    } else if(state == 2){
        //something wrong.
        return;
    }
   }
   else{
     block = 0;
   }
}

void loop() {
  showRoomState(count);
  delay(1000);
}
