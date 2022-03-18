/**
 * PRACTICA 1
 * DISENAR UN PROGRAMA QUE CAPTURE DATOS DE LOS PUERTOS DE ENTRADA DIGITALES
 * REALIZADO POR JAIME LORENZO SANCHEZ
 */

String vector[100]; // Array que almacena la informacion
int puerto; // Numero de puerto
int capturas = 0; // Numero de capturas del canal
int canales; // Numero de canales
String texto;

void setup() {
  Serial.begin(9600); // inicio del terminal
  while(!Serial){;}
}

void loop(){
  // Obtenemos el numero de canales
  Serial.print("Introduce el numero de canales: ");
  // Esperamos a que el usuario introduzca el numero de canales
  while(Serial.available() == 0){;}
  canales = Serial.read(); // Leemos el numero de canales
  Serial.println(canales);
  // Obtenemos el numero de canales
  Serial.print("Introduce el numero de muestras: ");
  // Esperamos a que el usuario introduzca el numero de canales
  while(Serial.available() == 0){;}
  capturas = Serial.read(); // Leemos el numero de canales
  Serial.println(capturas);
  while(Serial.available() == 0){;}
}

/*
void loop() {
  // El numero de canales debe ser especificado por el usuario
  Serial.print("Introduce el numero de canales a utilizar: ");
  while(Serial.available() == 0){;}   // Esperamos a que el usuario introduzca el numero de canales
  canales = Serial.read();
  Serial.println(canales);// Mostramos el numero de canales
  Serial.flush();// Limpiamos el buffer
  /*
  // El numero de capturas para cada canal (puerto) debe ser especificado por el usuario.
  Serial.print("Introduce el numero de capturas por canal: ");
  while(Serial.available() == 0){
      if(Serial.available() > 0){
        capturas = Serial.read(); // Leemos el numero de muestras  
        Serial.println(capturas);// Mostramos el numero de muestras
      }
  } // Esperamos a que el usuario introduzca el numero de capturas por canal
  
  // La informacion se debe almacenar en un array donde se indique el canal y las muestras capturadas para ese canal.
  for(int i=0; i<canales; i++){ // Para cada canal
    texto = texto + i; // Almacenamos el numero del canal
    for(int j=0; j<capturas; j++){ // Obtenemos las muestras del canal
      int lectura = digitalRead(i); // Leemos el canal
      texto = texto + "," + lectura; // Almacenamos la muestra capturada del canal
    }
    vector[i] = texto; // Almacenamos el canal como las muestras capturadas por el canal
    Serial.println("Canal y muestras: " + texto + " ; ");
    Serial.println("######################");
    texto = " ";// Limpiamos el texto
    // Se debe poder especificar un tiempo de espera entre la captura de un canal y otro mediante la función delay(milisegundos)
    delay(3000);
  }
}
*/
