#include <SPI.h>
#include <SD.h>
/**
 * REDES Y COMUNICACIONES ESPECIFICAS
 * Autor: Jaime Lorenzo Sanchez
 * Funcionamiento:
 * 1- En el receptor, tiene que esperar a que el emisor mande los datos.
 * 2- El emisor tiene que empezar a enviar los datos
 */


/**
Se nos plantean la siguiente cuestión
"Comprobar si hay pérdida de datos o no. Justificar la respuesta de si hay o no pérdida de datos."

Es más fiable la opción de enviar la información almacenada en un vector, ya que el delay de conexión es minima y es mucho más fiable
que si no utilizamos el vector. Ya que la muestra que se toma y a la vez se envia, existe un delay, y podemos encontrarnos que el 
receptor no alcanza a obtener todos los valores enviados, por esta misma cuestión, a veces pasa que los últimos valores que imprime 
el receptor son 0 pero no es porque el emisor le haya enviado un 0, es que el emisor ya ha mandado los 40 valores, y en el receptor 
no ha recogido valores y lo rellena con un 0.

Por lo tanto podemos concluir que a la hora de trabajar con medidas, debemos de ser precisos y primero almacenarlos en un array, 
para poder manipularlos o incluso para trasportar dicha información. Aún así, se puede representar un margen de error, 
pero respecto a la otra opción dicho margen es casi nulo.
**/

int* vector = (int*) malloc (sizeof(int)* 40);
int puntero = '1'; // Variable de control
int control=1; //Variable de control
File myFile;  // Fichero
String Fichero1 = "captura1.txt";//Fichero que se almacenara las muestras recibidas por un vector
String Fichero2 = "captura2.txt";//Se almacenara las muestras enviadas directamente sin tener que pasarlas por un vector
const int chipSelect = 4;
int llave; // Variable de control
//Variables de los ficheros para mostrar su contenido
Sd2Card card;
SdVolume volume;
SdFile root;

void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  while (!Serial) {;}
  // inicializando la tarjeta SD
  Serial.print("Inicializando SD card");
  if (!SD.begin(chipSelect)) 
  {
    Serial.println("inicialización fallida!");
    return;
  }
  Serial.println("Tarjeta SD inicializada.");
}

void loop() {
  // put your main code here, to run repeatedly:
  menu();
  // Esperamos a que el usuario indique una opcion
  while(Serial.available()==0){;}
  // Obtenemos la opcion seleccionada por el usuario
  int opcion = Serial.parseInt();
  // Mostramos la opcion seleccionada
  Serial.println(opcion);
  // Captura de la señal
  if(opcion == 1){
    if(Serial1.available()){
        String linea = ""; // Linea a almacenar en el fichero de texto captura2.txt
        // Obtenemos las capturas enviadas por el emisor
        Serial.println("Obteniendo capturas enviadas por el emisor");
        // Obtenemos las capturas
        for(int i=0; i < 40; i++){
          int captura = Serial1.parseInt();
          // Almacenamos la captura en un vector
          vector[i] = captura;
          // Almacenamos la captura del vector en la cadena linea
          linea = linea + String(captura);
        }
        // Almacenamos las capturas en el fichero de texto captura2.txt
        escribir_fichero2(linea);
        // Almacenamos los datos del vector en el fichero de texto captura1.txt
        escribir_fichero1();
    }
  }
  // Ver contenido del fichero captura1.txt
  else if(opcion == 2){
    leer_fichero(Fichero1);
  }
  // Ver contenido del fichero captura2.txt
  else if(opcion == 3){
    leer_fichero(Fichero2);
  }
  // Ver listado de ficheros almacenados en la tarjeta SD
  else if(opcion == 4){
    ver_contenido_sd();
  }
}

// Funciones auxiliares

void menu(){
  Serial.println("************************************");
  Serial.println("     MENU PRINCIPAL     ");
  Serial.println("************************************"); 
  Serial.println("1. Capturar señal | se usara dos ficheros de texto");
  Serial.println("2. Ver contenido fichero captura1.txt");
  Serial.println("3. Ver contenido fichero captura2.txt");
  Serial.println("4. Ver listado de ficheros almacenados en la tarjeta SD");
  Serial.print("Indica la opcion: ");
}

// Funcion que almacena los datos de un vector en un fichero de texto

void escribir_fichero1() {
  // Abrimos el fichero en modo escritura
  myFile = SD.open(Fichero1, FILE_WRITE);
  if (myFile) {
    Serial.println("Almacenando los datos del vector en el fichero de texto");
    // Obtenemos los datos del fichero de texto
    String linea2 = "";
    for (int i = 0; i < 40; i++) {
      linea2 = linea2 + String(vector[i]) + ",";
    }
    // Escribimos los datos del vector en el fichero de texto
    myFile.println(linea2);
    // Cerramos el fichero de texto
    myFile.close();
    // Liberamos la memoria del vector
    free(vector);
  }
  else{
    Serial.println("Se ha producido un error al abrir el fichero de texto");
  }
}

// Funcion que escribe los datos de las capturas en el fichero de texto capturas2.txt

void escribir_fichero2(String linea) { 
  // Abrimos el fichero de texto en formato escritura
  myFile = SD.open(Fichero2, FILE_WRITE);
  if (myFile) {
    Serial.println("Almacenando los datos en el fichero de texto capturas2.txt");
    myFile.println(linea);
    // Cerramos el fichero de texto
    myFile.close();
  }
  else 
  {
    Serial.println("Se ha producido un error al abrir el fichero de texto capturas2.txt");
  }
}

void leer_fichero(String Fich) {
  // Abrimos el fichero en modo lectura
  myFile = SD.open(Fich);
  if (myFile) {
    Serial.print("Mostrando el contenido del fichero: ")
    Serial.println(Fich);
    
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // cerramos el fichero
    myFile.close();
  } 
  else {
    Serial.print("Se ha producido un error al abri el fichero: ");
    Serial.println(Fich);
  }  
}

void ver_contenido_sd() {
	//Es la función para ver el contenido del directorio principal de la SD
  Serial.print("\nInicializando la SD card...");
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("Inicialización fallida. Puedo haber ocurrido uno de los siguientes errores:");
    Serial.println("* ha insertado la tarjeta SD?");
    Serial.println("* problemas de comunicación?");
    Serial.println("* cambia la selección del chipSelect pin acorde con la shield");
    return;
  } else {
    Serial.println("Comunicación correcta y la tarjeta está presente.");
  }
  if (!volume.init(card)) {
    Serial.println("No se encuentra la partición FAT16/FAT32.\nAsegúrese de que la tarjeta estaá formateada");
    return;
  }
	//Imprimimos el contenido de la SD
  Serial.println("\nListado de ficheros:\n");
  Serial.print("nombre          fecha       hora     tamaño en bytes\n");
  root.openRoot(volume);
  root.ls(LS_R | LS_DATE | LS_SIZE);
  Serial.println("");
}
