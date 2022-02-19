void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  DDRD = B11111111; // Utilizamos D pues es del 0 al 7 y B porque es binario
  byte valor;
  valor = digitalRead(0); 
  Serial.println(valor);
}

void loop() {
  // put your main code here, to run repeatedly:
}
