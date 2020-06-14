volatile bool inFlag=false, outFlag=false;
int state = 0;
int block = 0;
unsigned long lastInterrupt = 0;
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
      lastInterrupt = millis();
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
      return;
    
    } else if(state == 2){
        count--;
        state = 0;
        block = 1;
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
      lastInterrupt = millis();
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT2;
//      REG_EIC_INTFLAG = EIC_INTFLAG_EXTINT7;
      return;
      
    } else if(state == 1){
        block = 1;
        count++;
        state = 0;
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
