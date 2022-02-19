String incomingByte = String(999);   // for incoming serial data
//int i;
void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}
void loop() {

  // send data only when you receive data:
  //for (i=0;i<3;i++){     
  if (Serial.available() > 0) {
      // read the incoming byte:  
      Serial.readBytes(incomingByte, 3);
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte);
  }
  //}
}
