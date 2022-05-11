/**
 * REDES Y COMUNICACIONES ESPECIFICAS
 * Autor: Jaime Lorenzo Sanchez
 */
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600); //abre el puerto Serie1, configura los datos a 9600 bps.
  //Esperar la conexion con el serial
  while(!Serial){;}
  Serial.println("BIENVENIDO. SOY EL RECEPTOR");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Comprobamos si el puerto del Xbee tiene algún caracter
  if(Serial1.available()) 
  {
    // Obtenemos el carácter del puerto del Xbee
    char byte1 = Serial1.read(); 
    // Imprimimos el caracter
    Serial.print(byte1); 
  } 
}
