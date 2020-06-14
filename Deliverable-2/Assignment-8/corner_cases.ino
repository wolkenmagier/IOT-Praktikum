
// Someone briefly looks out of the room and turns back
void peekOutOfRoom(uint8_t param) {
    Serial.print("Peak out ");Serial.println(param);

    for (; param > 0; param--) {
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(500);
    }
}

// Someone walks up to the barriers from outside and turns around
void halfEnter(uint8_t param) {
    Serial.print("Half Enter ");Serial.println(param);
    for (; param > 0; param--) {
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(500);
        digitalWrite(triggerOut, LOW);
    }
}

// Someone walks up to the barriers from inside and turns around
void halfLeave(uint8_t param) {
    Serial.print("Half Leave ");Serial.println(param);
    for (; param > 0; param--) {
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(500);
    }
}

// Someone is almost inside the room but turns back
void almostEnter(uint8_t param) {
    Serial.print("Almost Enter ");Serial.println(param);
    for (; param > 0; param--) {
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(500);
    }
}

// Someone almost leaves the room completely but turns back
void almostLeave(uint8_t param) {
     Serial.print("Almost Leave ");Serial.println(param);

    for (; param > 0; param--) {
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(500);
    }
}

// Someone almost enters, steps back, but then enters
void unsureEnter(uint8_t param) {
    Serial.print("Unsure Enter ");Serial.println(param);

    for (; param > 0; param--) {
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
    }
}

// Someone almost leaves the room completely but turns back
void unsureExit(uint8_t param) {
    Serial.print("Unsure Exit ");Serial.println(param);

    for (; param > 0; param--) {
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
        digitalWrite(triggerIn, HIGH);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
        digitalWrite(triggerOut, HIGH);
        mydelay(50);
        digitalWrite(triggerIn, LOW);
        mydelay(50);
        digitalWrite(triggerOut, LOW);
        mydelay(50);
    }
}


//Someone is trying to manipulate the count by waving their arm through the barrier towards the inside
//Sequence is not possible if a person enters
void manipulationEnter(uint8_t param){ 
    Serial.print("Manipulation Enter ");Serial.println(param);
    while (param!=0){
      digitalWrite(triggerOut,HIGH);
      mydelay(15);
      digitalWrite(triggerOut,LOW);
      mydelay(15);
      digitalWrite(triggerIn,HIGH);
      mydelay(15);
      digitalWrite(triggerIn,LOW);
      mydelay(500);
      param--;
    }
}

//Someone is trying to manipulate the count by waving their arm through the barrier towards the outside
void manipulationLeave(uint8_t param){   
    Serial.print("Manipulation Leave ");Serial.println(param);
    while (param!=0){
      digitalWrite(triggerIn,HIGH);
      mydelay(15);
      digitalWrite(triggerIn,LOW);
      mydelay(15);
      digitalWrite(triggerOut,HIGH);
      mydelay(15);
      digitalWrite(triggerOut,LOW);
      mydelay(500);
      param--;
    }
}

//Someone is standing in the inside barrier, making counting impossible
void obstructionInside(uint8_t param){ 
  Serial.println("Obstruction Inside");
  digitalWrite(triggerIn,HIGH);
  mydelay(6000);
  digitalWrite(triggerOut,HIGH);
  mydelay(3000);
  // Resolve obstruction
  digitalWrite(triggerIn,LOW);
  digitalWrite(triggerOut,LOW);
  Serial.println("Obstruction inside resolved");
  mydelay(500);
}

//Someone is standing in the outside barrier, making counting impossible
void obstructionOutside(uint8_t param){
  Serial.println("Obstruction Outside");
  digitalWrite(triggerOut,HIGH);
  mydelay(6000);
  digitalWrite(triggerIn,HIGH);
  mydelay(3000);
  // Resolve obstruction
  digitalWrite(triggerOut,LOW);
  digitalWrite(triggerIn,LOW);
  Serial.println("Obstruction outside resolved");
  mydelay(500);
}

//Someone is peeking in and then leaving with another person coming from inside
void pickUpFriend(uint8_t param){
    Serial.print("Pick up Friend ");Serial.println(param);
    while (param!=0){
      digitalWrite(triggerOut,HIGH);
      mydelay(3000);
      digitalWrite(triggerIn,HIGH);
      mydelay(50);
      digitalWrite(triggerOut,LOW);
      mydelay(50);
      digitalWrite(triggerIn,LOW);
      mydelay(50);
      digitalWrite(triggerOut,HIGH);
      mydelay(50);
      digitalWrite(triggerOut,LOW);
      mydelay(500);
      param--;
    }
}
