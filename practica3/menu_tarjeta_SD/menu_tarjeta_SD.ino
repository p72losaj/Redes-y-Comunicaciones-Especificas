/*
  Redes de Comunicaciones Específicas

 Este ejemplo muestra cómo se crea y borra
 ficheros en la tarjeta SD. También lista el contenido
 de directorios y el contenido de ficheros

 SD card utiliza los siguientes pines para utilizar 
   el bus SPI:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
 */

// include the SD library:
#include <SPI.h>
#include <SD.h>

// variables de los ficheros y el root
File myFile;  //variableas para definir el fichero (puntero de comienzo del fichero abierto

String Fichero = "";
String file = "";
char valor[] = "Hola Mundo";

// variables de configuración de la tarjeta SD utilizada por las funciones
Sd2Card card;
SdVolume volume;
SdFile root;

// cambia este parámetro según que tipo de Shields utilizas;
// Arduino Ethernet shield: pin 4
// Adafruit SD shields and modules: pin 10
// Sparkfun SD shield: pin 8
const int chipSelect = 4;

// control de bucles
char opcion = '0';

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  
  // inicializando la tarjeta SD
  Serial.print("Inicializando SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("inicialización fallida!");
    return;
  }
  Serial.println("inicializada.");

  // reservando memoria para el nombre delfichero
  Fichero.reserve(12);
  file.reserve(12);
}

void loop() {
  // nothing happens after setup finishes.
  menu_SD();
  do{
     while (Serial.available()){
      opcion = Serial.read();
     }
  }while ((opcion < 49) || (opcion >53));
  switch(opcion){
    case '1':
      Serial.write("1\n");
      info_SD();
      opcion = "0";
      break;          
    case '2':
      Serial.write("2\n");
      Fichero = nombre_fichero();
      crear_fichero();
      opcion = "0";
      break;
    case '3':
      Serial.write("3\n");
      Fichero = nombre_fichero();
      borrar_fichero();
      opcion = "0";
      break;
    case '4':
      Serial.write("4\n");
      Fichero = nombre_fichero();
      leer_fichero();
      opcion = "0";
      break;
    case '5':
      Serial.write("5\n");
      Fichero = nombre_fichero();
      escribir_fichero();
      opcion = "0";
      break;  
  }
}

void menu_SD(){
  Serial.println("");
  Serial.println("************************************");
  Serial.println("     MENU PRINCIPAL TARJETA SD:     ");
  Serial.println("************************************"); 
  Serial.write("1.- Listar ficheros de la Tarjeta SD\n");
  Serial.write("2.- Crear un fichero de la Tarjeta SD\n");
  Serial.write("3.- Borrar un fichero de la Tarjeta SD\n");
  Serial.write("4.- Leer contenido de un fichero de la Tarjeta SD\n");
  Serial.write("5.- Escribir datos tipo caracter en un fichero de la Tarjeta SD\n");
  Serial.write("Indica la opcion: ");
}

String nombre_fichero() {
  file = "";
  Serial.print("Nombre del fichero (máx 12 caracteres: ");
  do {
    if (Serial.available()){
       file = Serial.readString();
       Serial.println(file);
    }
  }while (file.length() == 0);
  return file;
}

void listar_ficheros(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no hay ficheros
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      listar_ficheros(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}

void crear_fichero() {
  if (SD.exists(Fichero)) {
    Serial.print(Fichero);
    Serial.println(" exists.");
  } else {
    Serial.print("Creando ");
    Serial.println(Fichero);
    myFile = SD.open(Fichero, FILE_WRITE);
//    for (int i=0;i<10;i++){
//      myFile.write(datos[i]);
//    }
    myFile.close(); 
    Serial.print(Fichero);
    Serial.println(" creado");
  }
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

void leer_fichero() {
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

void escribir_fichero() {
  // Abrir archivo y escribir valor
  myFile = SD.open(Fichero, FILE_WRITE);
    if (myFile){
        myFile.println(*valor);
        myFile.close();
    }
    else {
      Serial.println("Error al abrir el archivo");
    }
  //myFile.close();
  delay(500);
}

void info_SD() {
  Serial.print("\nInicializando la SD card...");

  // mientras se inicializa la tarjeta
  // se realiza un test de la tarjeta SD
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("Inicialización fallida. Puedo haber ocurrido uno de los siguientes errores:");
    Serial.println("* ha insertado la tarjeta SD?");
    Serial.println("* problemas de comunicación?");
    Serial.println("* cambia la selección del chipSelect pin acorde con la shield");
    return;
  } else {
    Serial.println("Comunicación correcta y la tarjeta está presente.");
  }

  // muestra el tipo de tarjeta
  Serial.print("\nTipo de tarjeta: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1:
      Serial.println("SD1");
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println("SD2");
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println("SDHC");
      break;
    default:
      Serial.println("Desconocida");
  }

  // Verificar el volumen de la partición - debe ser tipo FAT16 o FAT32
  if (!volume.init(card)) {
    Serial.println("No se encuentra la partición FAT16/FAT32.\nAsegúrese de que la tarjeta estaá formateada");
    return;
  }

  // muestra el tipo y tamaño del volumen
  uint32_t volumesize;
  Serial.print("\nEl tipo de volumen es FAT");
  Serial.println(volume.fatType(), DEC);
  Serial.println();
  
  // Los bloques SD card son siempre de 512 bytes
  volumesize = volume.blocksPerCluster();    
  volumesize *= volume.clusterCount();       
  volumesize *= 512;                            
  Serial.print("Tamaño del volumen (bytes): ");
  Serial.println(volumesize);
  Serial.print("Tamaño del volumen (Kbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Tamaño (Mbytes): ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.println("\nListado de ficheros:\n");
  Serial.print("nombre          fecha       hora     tamaño en bytes\n");
  root.openRoot(volume);

  // listado de todos los ficheros de la tarjeta
  root.ls(LS_R | LS_DATE | LS_SIZE);
}
