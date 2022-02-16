void setup() {
  // put your setup code here, to run once:
  byte lectura = 0;
  for(int i=0; i< 8; i++){
    lectura = digitalRead(i); //Cargamos en una variable byte el valor capturado por la entrada digital i
    // Mostramos el valor de la entrada digital
    Serial.print("Estado del boton: ");
    Serial.println(lectura);
    delay(100); // Pausamos 100 ms entre una carga y otra de la variable tipo byte que se captura
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}
