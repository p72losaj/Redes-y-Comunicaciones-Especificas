#include <SPI.h>
#include <SD.h>
/**

***Redes y comunicaciones específicas***
ALUMNO: Jaime Lorenzo Sanchez

*/

//FUNCIONAMIENTO

/**
Primero en el receptor, tiene que darle la opción 1, para tomar esperar al emisor que mande los datos.
Posteriormente el emisor, tiene que entrar en el menú y darle al 1, para empezar enviar los valores

*/


/**
Se nos plantean la siguiente cuestión

 "Comprobar si hay pérdida de datos o no. Justificar la respuesta de si hay o no pérdida de datos."

Es más fiable la opción de enviar la información almacenada en un vector, ya que el delay de conexión es minima y es mucho más fiable
que si no utilizamos el vector. Ya que la muestra que se toma y a la vez se envia, existe un delay, y podemos encontrarnos que el receptor
no alcanza a obtener todos los valores enviados, por esta misma cuestión, a veces pasa que los últimos valores que imprime el receptor son 0
pero no es porque el emisor le haya enviado un 0, es que el emisor ya ha mandado los 40 valores, y el receptor habido valores que no lo ha cogido
y lo rellena con un 0.

Por lo tanto podemos concluir que a la hora de trabajar con medidas, debemos de ser precisos y primero almacenarlos en un array, para poder manipularlos o incluso
para trasportar dicha información. Aún así, se puede representar un margen de error, pero respecto a la otra opción dicho margen es casi nulo.


**/


int captura[40] = {0}; // Vector de capturas
int puntero = '1'; // Variable de control
int control=1; //Variable de control
File myFile;  //variables para definir el fichero (puntero de comienzo del fichero abierto
String Fichero1 = "captura1.txt";//Fichero que se almacenara las muestras recibidas por un vector
String Fichero2 = "captura2.txt";//Se almacenara las muestras enviadas directamente sin tener que pasarlas por un vector
const int chipSelect = 4;
int opcion; //Variable de control
int llave; //Variable de control//
//Variables de los ficheros para mostrar su contenido
Sd2Card card;
SdVolume volume;
SdFile root;



void setup() {
  Serial1.begin(9600);
  Serial.begin(9600);
  while (!Serial) {;}
  // inicializando la tarjeta SD
  Serial.print("Inicializando SD card...");

  if (!SD.begin(chipSelect)) 
  {
    Serial.println("inicialización fallida!");
    return;
  }
  Serial.println("inicializada.");
  
 
}

void loop() {
  if (opcion == 0) {
    menu();
    opcion = 1;
    delay(1000);
  }

  while (Serial.available() > 0) {
    opcion = Serial.read();
    delay (1000);
    switch (opcion) {
      case '1':
        Serial.println(F("Opcion 1 elegida\n"));
        delay(1000); 
        //En la opcion 1: En el primer apartado recibiremos las muestras en un vector, para luego guardarlo en un fichero .txt
        do{
          if (puntero == '1' && Serial1.available()) {
            Serial.println("\nCapturas con vector: ");
            for (int i = 1; i < 40; i++) {
              delay(500);
              captura[i] = Serial1.parseInt();
              Serial.print("Captura ");
              Serial.print(i);
              Serial.print(": ");
              Serial.println(captura[i]);
            }
            escribir_fichero1();
            puntero = '2';
            delay(100);
          }
          //En el segundo apartado recibiremos las muestras sin guardarlas en un vector, para luego guardarlo en un fichero.txt
          if (puntero == '2' && Serial1.available() > 0) {
            delay(3000);
            int control=1;
            Serial.println("\nCapturas sin vector: ");
            for (int i = 1; i < 40; i++) {
              escribir_fichero2();
            }
            llave = 1;
          }
        }while(llave != 1);
        opcion = 0;
        break;
      case '2'://En esta opción leemos la información que almacena el fichero1
        Serial.println(F("Opcion 2 elegida\n"));
        leer_fichero(Fichero1);
        opcion = 0;
        break;
      case '3'://En esta opción leemos la información que almacena el fichero2
        Serial.println(F("Opcion 3 elegida\n"));
        leer_fichero(Fichero2);
        opcion = 0;
        break;
      case '4'://Por último en esta opción muestra el contenido de la tarjeta SD
        Serial.println(F("Opcion 4 elegida\n"));
        ver_contenido_sd();
        opcion = 0;
        break;
      default:
        opcion = 0;
        break;
    }
  }
}
//Función de Menu
void menu(){
  Serial.print("\n");
  Serial.println("************************************");
  Serial.println("     MENU PRINCIPAL     ");
  Serial.println("************************************"); 
  Serial.write("1.- Capturar señal | se usara dos .txts\n");
  Serial.write("2.- Ver contenido captura1.txt\n");
  Serial.write("3.- Ver contenido captura2.txt\n");
  Serial.write("4.- Listado ficheros SD");
  Serial.write("\nIndica la opcion: ");
}

void escribir_fichero1() {
//En esta función hace la impreso del fichero1 desde un vector.
  myFile = SD.open(Fichero1, FILE_WRITE);
  if (myFile) {
    myFile.print("\nCaptura con Vector: ");
    //Escribe en el fichero los datos capturados dependiendo de la iteracion
    for (int i = 1; i < 40; i++) {
      Serial.println(captura[i]);
      myFile.print(captura[i]);
        myFile.print("/");
    }
    myFile.close();
  }
  else {//Importante cerrar el fichero
    Serial.print("Error al abrir ");
    Serial.println(Fichero1);
  }
}

void escribir_fichero2() { 
//Esta función se utiliza para escribir en el fichero = capturas2.txt, es diferente a fichero1 porque se imprime los valores sin estar en un vector

  myFile = SD.open(Fichero2, FILE_WRITE);
  if (myFile) {
    if(control==1){
      myFile.print("\nCaptura sin Vector: ");
      control=0;
    }
    delay(200);
    int captura = Serial1.parseInt();
    Serial.println(captura);
    myFile.print(captura);
    myFile.print("/");
    myFile.close();
  }
  else {//Importante cerrar el fichero
    Serial.println("Error al abrir ");
    Serial.println(Fichero2);
  }
  delay(500);
}

void leer_fichero(String Fich) {
//Usamos esta función para leer el fichero
  myFile = SD.open(Fich);
  if (myFile) {
    Serial.println(Fich);
    Serial.println("El contenido de fichero es:");
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // cerramos el fichero, muy importante:
    myFile.close();
  } else {
    // si el fichero no existe muestra el error
    Serial.print("error abriendo ");
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
