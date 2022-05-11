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
  pinMode(LED_BUILTIN, OUTPUT); // Inicializamos el led13
  Serial.println("BIENVENIDO. SOY EL RECEPTOR");
}

void loop() {
  // put your main code here, to run repeatedly:

}
