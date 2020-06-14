volatile bool inFlag=false, outFlag=false;
volatile uint8_t count = 0;
int state = 0;
const byte interruptOuter = 9; //Grey, EINT2
const byte interruptInner = 11; //Grey, EINT7
int block = 0;
unsigned long lastInterrupt;
//void out(){
//  if (inFlag) {
//    count--;
//    inFlag=false;
//  } else {
//    outFlag=true;
//  }
//}
//
//void in(){
//  if (outFlag) {
//    count++;
//    outFlag=false;
//  } else {
//    inFlag=true;
//  }
//}

void out(){
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

void in(){
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
