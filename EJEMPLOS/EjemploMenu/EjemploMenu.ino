/*******************************************************
*** Asignatura: Redes de Comunicaciones Específicas ***
********************************************************/

char opcion;
char valor;
int puerto;
int val;

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600); 
  while(!Serial){
  ; 
  }
}

void loop () {
  menu();
  while(opcion<49 || opcion>51){
    if(Serial.available() > 0){
        opcion = Serial.read();
      }  
  }
  
  switch(opcion){    
    case '1':
      Serial.println(opcion);
      Serial.print("Captar valor/es de monitor serie\n");
      leer();
      break;

    case '2':
      Serial.println(opcion);
      Serial.print("Mostrar valor/es por el monitor serie\n");
      mostrar();
      break;
      
    case '3':
      Serial.println(opcion);
      Serial.print("Seleccionar puerto digital, captar un valor y mostrarlo por el puerto 13\n");
      muestrear_puerto();
      break;
    }
    opcion = 0;
    delay(100);
}

void menu() {
  Serial.println("\n");
  Serial.println("(1) Captar valor/es de monitor serie");
  Serial.println("(2) Mostrar valor/es por el monitor serie");
  Serial.println("(3) Seleccionar puerto digital, captar un valor y mostrarlo por el puerto 13");
  Serial.print("Elige una opcion:");
}

void leer() {
  do {
    valor = Serial.read();
  } while (valor < 0);
  Serial.println("Valor del monitor guardado");
}

void mostrar() {
  Serial.print("El valor es: ");
  Serial.println(valor);  
}

void muestrear_puerto() {
  Serial.print("Selecciona puerto: ");
  while(puerto<48 || puerto>57){
    if(Serial.available() > 0){
        puerto = Serial.read();
      }  
  }
  puerto = puerto - 48;
  Serial.println(puerto);
  pinMode(puerto, INPUT);
  val = digitalRead(puerto);
  Serial.println(val);
  digitalWrite(13, val);
}
