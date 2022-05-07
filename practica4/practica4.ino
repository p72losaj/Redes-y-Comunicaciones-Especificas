/*
 * Practica 4 de Redes y Comunicaciones Especificas
 * Autor: Jaime Lorenzo Sanchez
 * 
 */
// include the SD library:
#include <SPI.h>
#include <SD.h>
File myFile;  //variables para definir el fichero (puntero de comienzo del fichero abierto
String Fichero = "datos.txt"; // Nombre del fichero
const int chipSelect = 4;
int identificador = 0; // Identificador de la captura
int pin_analogico; // Puerto de entrada analogico
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
  // Eliminacion del fichero
  // borrar_fichero();
  // Creamos el fichero
  crearFichero();  
  
}

void loop() {
  // nothing happens after setup finishes.
  menu();
  // Esperamos a que el usuario indique una opcion
  while(Serial.available() == 0){;}
  int opcion = Serial.readString().toInt(); // La cadena obtenida la transformamos en un entero
  Serial.println(opcion);
  // Conversion A/D de señal analogica
  if(opcion == 1){
    identificador = identificador + 1;
    // Seleccionar el puerto de entrada analógico mediante el monitor
    Serial.print("Introduce el puerto de entrada analogico: ");
    // Esperamos a que el usuario introduzca el puerto de entrada analogico
    while(Serial.available() == 0){;}
    // Obtenemos el puerto analogico mediante el canal Serial
    String puerto = Serial.readString();
    pin_analogico = puerto.toInt();
    // Mostramos el pin analogico
    Serial.println(puerto);
    // Seleccionar el número de muestras.
    Serial.print("Introduce el numero de lecturas del pin analogico: ");
    // Esperamos a que el usuario introduzca el numero de lecturas
    while(Serial.available() == 0){;}
    // Obtenemos el numero de lecturas del pin analogico
    lecturas = Serial.readString().toInt();
    // Mostramos el numero de lecturas del pin analogico
    Serial.println(lecturas);
    // Reservamos la memoria del vector de valores cuantificados
    muestras = (int*) malloc (sizeof(int)* lecturas);
    // Reservamos la memoria del vector de valores de voltaje
    muestras2 = (int*) malloc (sizeof(int)* lecturas);
    /*
     * Mostrar la captura por pantalla del monitor, tanto la información cuantificada como la información convertida a 
     * valores de voltaje. Para ello se debe introducir el valor máximo y mínimo del valor de voltaje de la señal analógica 
     * y dividirla entre 2^10 = 1024 
     * (número total de elementos que cuantificamos: [(Vmax - Vmin)/1024] * Valor cuantificado (obtenido de la captura)
     */
     // Obtenemos los valores del puerto analogico
     for(int i=0; i < lecturas; i++){
        // Almacenamos el valor cuantificado en el vector muestras
        muestras[i] = analogRead(pin_analogico);
        // Almacenamos el valor del voltaje obtenido en el vector de voltajes
        muestras2[i] = ((5-0)%1024) * muestras[i];
     }
     // Mostramos la información cuantificada
     Serial.println("Mostrando la información obtenida");
     Serial.println("Lectura Valor_estratificado Valor_Voltaje(Voltios)");
     for(int i=0; i<lecturas; i++){
      // Mostramos la lectura actual
      Serial.print(i+1);
      // Mostramos el valor estratificado
      Serial.print(" ");
      Serial.print(muestras[i]);
      // Mostramos el valor en voltaje
      Serial.print(" ");
      Serial.println(muestras2[i]);
     }
     
  }
  // Guardar la informacion obtenida en el fichero
  else if(opcion == 2){
    // Almacenamos la informacion en el fichero
    guardarInformacion();
    // Liberamos la memoria del vector de valores cuantificados
    free(muestras);
    Serial.println("Se ha liberado la memoria del vector de valores cuantificados");
    // Liberamos la memoria del vector de voltajes
    free(muestras2);
    Serial.println("Se ha liberado la memoria del vector de voltajes");
  }
  // Ver contenido tarjeta microSD
  else if(opcion == 3){
    Serial.print("Leyendo datos del fichero ");
    Serial.println(Fichero);
    leerFichero();
  }
}

void guardarInformacion(){
  myFile = SD.open(Fichero,FILE_WRITE);
  if (myFile) {
    String linea = "";
    String aux = "";
    String aux2 = "";
    // Obtenemos el identificador
    linea = linea + String(identificador);
    linea = linea + " ";
    // Obtenemos el numero de muestras
    linea = linea + String(lecturas) + " ";
    // Obtenemos los valores estratificados y de voltaje obtenidos
    for(int i=0; i < lecturas; i++){
      aux = aux + String(muestras[i])+",";
      aux2 = aux2 + String(muestras2[i])+",";
    }
    linea = linea + aux + " " + aux2 + " ;";
    Serial.println("Almacenando en el fichero la linea: ");
    Serial.println(linea);
    // Almacenamos la linea en el fichero
    myFile.println(linea);
    // Cerramos el fichero 
    myFile.close();
  } else {
    // si el fichero no existe muestra el error
    Serial.print("error abriendo ");
    Serial.println(Fichero);
  }  
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

void borrar_fichero() {
  if (SD.exists(Fichero)) {
    Serial.print("Borrando  ");
    Serial.println(Fichero);
    SD.remove(Fichero);
    Serial.print(Fichero);
    Serial.println(" borrado.");
  } else {
    Serial.print(Fichero);
    Serial.println(" no existe.");
  }
}

void crearFichero(){
  if (SD.exists(Fichero)) {
    Serial.print(Fichero);
    Serial.println(" exists.");
  } else {
    Serial.print("Creando ");
    Serial.println(Fichero);
    myFile = SD.open(Fichero, FILE_WRITE);
    // Escribimos la primera linea del fichero -> Identificador NumeroMuestras ValoresEstratificados ValoresVoltaje;
    String linea = "";
    linea = linea + "Identificador";
    linea = linea + " Numero_Muestras ";
    linea = linea + "Valores_Estratificados";
    linea = linea + " Valores_Voltaje;";
    myFile.println(linea);
    // Cerramos el fichero
    myFile.close(); 
    Serial.print(Fichero);
    Serial.println(" creado");
  }
}

void leerFichero() {
  myFile = SD.open(Fichero);
  if (myFile) {
    Serial.println("El contenido de fichero es:");
    while (myFile.available()) {
      Serial.write(myFile.read());
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
