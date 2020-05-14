#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET 4 // Reset pin # (or -1 if sharing Arduino reset pin)

int count = 0;

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
  
}

void loop() {
 char Str4[] = "IOT Praktikum";
 count++;
 showRoomState(count);
 delay(1000);
}
