/*
 * Practica 4 de Redes y Comunicaciones Especificas
 * Autor: Jaime Lorenzo Sanchez
 * 
 */
// include the SD library:
#include <SPI.h>
#include <SD.h>
File myFile;  //variables para definir el fichero (puntero de comienzo del fichero abierto
String Fichero = "datos_conversion_AD.txt"; // Nombre del fichero
const int chipSelect = 4;
int identificador = 0; // Identificador de la captura
int pin = 0; // Puerto de entrada analogico
int lecturas = 0; // Numero de muestras del canal
int* muestras; // Vector de muestras de datos cuantificados
int* muestras2; // Vecotr de muestras en voltaje

void setup() {
  Serial.begin(9600);
  while(!Serial){;}
  
  // inicializando la tarjeta SD
  Serial.print("Inicializando SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("inicialización fallida!");
    return;
  }
  Serial.println("inicializada.");
  // Creamos el fichero
  crearFichero();
  // Leemos los datos del fichero
  leerFichero();
}

void loop() {
  // nothing happens after setup finishes.
  //menu();
  // Esperamos a que el usuario indique una opcion
  //while(Serial.available() == 0){;}
  //int opcion = Serial.readString().toInt(); // La cadena obtenida la transformamos en un entero
  //Serial.print(opcion);
  
}

void menu(){
  Serial.println("");
  Serial.println("************************************");
  Serial.println("     MENU PRINCIPAL TARJETA SD:     ");
  Serial.println("************************************"); 
  Serial.write("1.- Conversion A/D de señal analogica\n");
  Serial.write("2.- Guardar el vector en un fichero\n");
  Serial.write("3.- Ver contenido tarjeta microSD\n");
  Serial.write("Indica la opcion: ");
}

void crearFichero(){
  if (SD.exists(Fichero)) {
    Serial.print(Fichero);
    Serial.println(" exists.");
  } else {
    Serial.print("Creando ");
    Serial.println(Fichero);
    myFile = SD.open(Fichero, FILE_WRITE);
    // Escribimos la primera linea del fichero -> Identificador Numero de muestras Valores estratificados Valores voltaje
    myFile.write("Identificador Numero de muestras Valores estratificados Valores voltaje");
    myFile.close(); 
    Serial.print(Fichero);
    Serial.println(" creado");
  }
}

void leerFichero() {
  myFile = SD.open(Fichero);
  if (myFile) {
    Serial.println(Fichero);
    Serial.println("El contenido de fichero es:");
    while (myFile.available()) {
      Serial.println(myFile.read());
    }
    // cerramos el fichero, muy importante:
    myFile.close();
  } else {
    // si el fichero no existe muestra el error
    Serial.print("error abriendo ");
    Serial.println(Fichero);
  }  
}

/**
 * Explicaciones:
 * Para guardar los datos del vecotr, emplearía capturar todas las muestras en un vector y 
 * después guardar todos los datos del vector en un fichero, debido a que de ese modo 
 * se utiliza menos memoria (no se está comprobando la existencia del fichero cada vez que se 
 * almacena un valor en el mismo)
 */
