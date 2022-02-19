char datos; // Datos serial recibidos
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Abrimos datos serial, poniendo los ratios de datos del serial a 9600 bps
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 1){ // Solo enviamos datos cuando recibimos datos
      datos = Serial.read(); // Leemos los bytes recibidos
      Serial.print("Datos recibidos: ");
      Serial.println(datos);
   }
   Serial.println("Continuamos la ejecucion");
   delay(100); // Espera de 100 ms
}
