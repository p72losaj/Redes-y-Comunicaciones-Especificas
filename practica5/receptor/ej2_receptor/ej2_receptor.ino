/**
***Redes y comunicaciones específicas***
ALUMNO: Jaime Lorenzo Sanchez
*/

/*  Programa para enviar y recibir caraceres a través del puerto de comunicaciones inalambrica del Xbee
 *  En los monitores/hiperterminales se introduce los caracteres y se pulsa la tecla intro para envdiar
 */

// Variables globales
char byte1='0'; //Variable que almacena el valor que se recibe

void setup()
{
  Serial.begin(9600);//abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {; }
  Serial.println("BIENVENIDO. SOY EL RECEPTOR");
} 
 
 
void loop()
{   
  if(Serial1.available()) //verificar si el puerto del Xbee tiene algún caracter
  {
   byte1 = Serial1.read(); //recibir carácter del puerto del Xbee
   Serial.print(byte1); //imprimir en el monitor/hiperterminal el carácter
 } 
 
} 
