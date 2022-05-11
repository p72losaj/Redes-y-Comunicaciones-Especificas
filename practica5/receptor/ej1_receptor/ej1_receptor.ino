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
  // Inicializamos el led 13
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("BIENVENIDO. SOY EL RECEPTOR");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Comprobamos si el puerto del Xbee tiene algun caracter
  if(Serial1.available()){
    // Recibimos el caracter del puerto del Xbee
    char byte1 = Serial.read();
    // Imprimimos el caracter leido
    Serial.print("Valor recibido del puerto del Xbee: ");
    Serial.println(byte1);
    // Verificamos que no se inicie un bucle de impresion
    int bucle = 0;
    // Comprobamos si se enciende o se apaga el led
    if(byte1 == '1' and bucle == 0){
      // Encendemos el led
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Se ha encendido el led 13");
      bucle = 1;
    }
    else{
      // Apagamos el led
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println("Se ha apagado el led 13");
      bucle = 1;
    }
  }
}
