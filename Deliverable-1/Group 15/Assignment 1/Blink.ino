const byte ledPin = 13;

void setup() {
  while (!Serial); // wait for Serial to be initialized
  Serial.begin(115200);
  delay(1000);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  
  Serial.println("Started");
}

void loop() {
   Serial.println("new iteration");
   digitalWrite(ledPin, HIGH);
   delay(100);
   digitalWrite(ledPin, LOW);   
   delay(500); 
}
