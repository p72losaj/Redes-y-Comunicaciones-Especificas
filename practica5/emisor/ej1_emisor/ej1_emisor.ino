/**
 * REDES Y COMUNICACIONES ESPECIFICAS
 * Autor: Jaime Lorenzo Sanchez
 */

// Variables globales

int puerto = 0; // Puerto digital de escucha
char pin; // Valor de escucha del puerto digital

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600); //abre el puerto Serie1, configura los datos a 9600 bps.
  for (int i=0; i<=7; i++){pinMode(i,INPUT);} // Inicializamos los pines del 0 al 7 ambos incluidos.}
  //Esperar la conexion con el serial
  while(!Serial){;}
  Serial.println("BIENVENIDO. SOY EL EMISOR");
}

void loop() {
  // put your main code here, to run repeatedly:
  // Introducimos el puerto de escucha
  Serial.print("Introduce el puerto de escucha: ");
  // Esperamos a que el usuario introduzca el puerto de escucha
  while(Serial.available() == 0){;}
  // Obtenemos el puerto de escucha
  puerto = Serial.parseInt();
  // Mostramos el puerto de escucha
  Serial.println(puerto);
  // Recibimos la escucha del puerto digital
  pin = digitalRead(puerto);
  // Mostramos el valor obtenido del puerto digital en formato binario
  Serial.print("Lectura recibida: ");
  Serial.println(pin,BIN);
  // Enviamos el valor de la señal por el canal Serial1
  Serial1.println(pin,BIN);
}
