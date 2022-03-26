/**
 * PRACTICA 1
 * DISENAR UN PROGRAMA QUE CAPTURE DATOS DE LOS PUERTOS DE ENTRADA DIGITALES
 * REALIZADO POR JAIME LORENZO SANCHEZ
 */
// Vector de informacion
String texto;
// Numero de capturas del canal introducido por el usuario
int capturas = 0;
// Array de los puertos de entrada digitales
int pinEntrada[11] = {2,3,4,5,6,7,8,9,10,11,12};
// Numero de canales o puertos introducido por el usuario
int canales = 0; 

void setup() {
  Serial.begin(9600); // inicio del terminal
  while(!Serial){;}
}

void loop() {  
  // El numero de canales debe ser especificado por el usuario
  Serial.print(" Introduce el numero de canales a utilizar: ");
  // Esperamos a que el usuario introduzca el numero de canales
  while(Serial.available() == 0){;}   
  // Leemos el numero de canales introducido por el usuario
  canales = Serial.readString().toInt();
  // El numero de canales debe estar dentro del rango [1,11]
  while(canales < 1 or canales > 11){
    // Volvemos a pedir el numero de canales
    Serial.println("Introduce un numero de canales superior a 0 e inferior a 12");
    // Esperamos a que el usuario introduzca el numero de canales
    while(Serial.available() == 0){;}
    // Almacenamos el nuevo numero de canales
    canales = Serial.readString().toInt();
  }
  // Mostramos el numero de canales introducido por el usuario
  Serial.println(canales); 
  // Limpiamos el buffer
  Serial.flush();
  // El numero de capturas para cada canal (puerto) debe ser especificado por el usuario.
  Serial.print("Introduce el numero de capturas por canal: ");
  // Esperamos a que el usuario introduzca el numero de capturas por canal
  while(Serial.available() == 0){;}
  // Leemos el numero de muestras del canal
  capturas = Serial.readString().toInt();
  // Mostramos el numero de capturas
  Serial.println(capturas);  
  // La informacion se debe almacenar en un array donde se indique el canal y las muestras capturadas para ese canal.
  for(int i=0; i<canales; i++){
    String copia, muestras;
    String canal = String(pinEntrada[i]);
    copia = canal;
    for(int j=0; j<capturas; j++){
      // Capturamos el dato del canal
      int lectura = digitalRead(pinEntrada[i]); 
      // Almacenamos la muestra del canal
      muestras = muestras + lectura + ";";
    }
    // Almacenamos la informacion
    // Mostramos la informacion obtenida
    Serial.println("Canal: " + canal + "\n\tMuestras del canal: " + muestras);
    // Almacenamos la informacion obtenida
    texto = canal + muestras;
    // Se debe poder especificar un tiempo de espera entre la captura de un canal y otro mediante la función delay(milisegundos)
    delay(3000);
  }
}
