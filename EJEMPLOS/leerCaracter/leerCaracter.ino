int opcion = 1;   // for incoming serial data

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
}

void loop() {

opcion = Serial.read();

switch (opcion) {
    case 1:
      //do something when var equals 1
      Serial.println("Opción 1");
      break;
    case 2:
      //do something when var equals 2
      Serial.println("Opción 2");
      break;
  }
  delay(3000);
}
