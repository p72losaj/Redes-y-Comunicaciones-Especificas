/**

***Redes y comunicaciones específicas***
ALUMNO: Jaime Lorenzo Sanchez

*/

/*  Programa para enviar y recibir caraceres a través del puerto de comunicaciones inálmbrica del Xbee
 *  En los monitores/hiperterminales se introduce los caracteres y se pulsa la tecla intro para envdiar
 */
char byte1='0';
int maxa=0; //Variable donde se almacena el maximo
int mini=0; //Donde se almacena el minimo
float media=0; //La media, importante que sea float para dar exactitud
int contador=0; //El contador, es para saber que valor es el que envia el emisor y donde guardarlo
int imprimir_valores=0; // Es la variable donde controla, la impresión de los valores sin entrar en bucle
void setup()
{
  Serial.begin(9600);//abre el puerto Serie, configura los datos a 9600 bps.
  Serial1.begin(9600);//abre el puerto Serie1, configura los datos a 9600 bps.
  while (!Serial) {
    ; //Espera la conexión con la terminal
  }
  pinMode(LED_BUILTIN, OUTPUT); // Inicializamos el led13
  Serial.print("->SOY EL RECEPTOR\n");
} 
 
 
void loop()
{   
  delay(1000);

  if(Serial1.available()) //verificar si el puerto del Xbee tiene algún caracter
  {
    if(contador==0){
      byte1 = Serial1.read(); //recibir carácter del puerto del Xbee
      if(byte1=='z'){//Si recibimos una 'Z' es que el emisor va a mandar los valores en un orden en concreto
        contador=1; //Pasamos al contador 1, que es que va a recibir el maximo
        maxa=0;//inicializamos las variables
        mini=0;
      }
     }
     else if(contador>0 and contador<5){
     if(contador==3){//Recibo la media cuando el contador sea igual a 3
      float aux2 = Serial1.parseFloat();
        media=aux2;
        contador=4;
      }
      
      if(contador==2){//Recibo el minimo cuando el contador sea 2
       int aux = Serial1.parseInt();
          mini=aux;
          contador=3;
      }

      if(contador==1){//Recibo el maximo cuando el contador sea 1.
        int aux = Serial1.parseInt();
        maxa=aux;
        contador=2;
      }
      
        if(contador==4){
          //Por último recibe un "espacio" el receptor del emisor que significa que ha terminado la secuencia de enviar.
        contador=0;
        imprimir_valores=1;
      
       }     
     } 

    //Hacemos la impresión de los valores
    if(imprimir_valores==1){
     Serial.write("--------------------------------------\n");
     Serial.print("\nValor Recogido Max: ");
     Serial.print(maxa);
     Serial.print("\nValor Recogido Min: ");
     Serial.print(mini);
     Serial.print("\nValor Recogido Media: ");
     Serial.print(media);
     Serial.print("\n");
     imprimir_valores=0;
     
     //Controlamos si se activa el led13 dependiendo si la diferencia es mayor que media.
     int diferencia= maxa-mini;
      if(diferencia > media){
         Serial.print("-> (maximo-minimo) > media ");
         Serial.print("\nEl led 13 se activa ");
         digitalWrite(LED_BUILTIN, HIGH);
       }else{
        //Si no es mayor que la media apaga el led 13.
         Serial.print("-> (maximo-minimo) < media ");
         Serial.print("\nEl led 13 se desactiva\n ");
         digitalWrite(LED_BUILTIN, LOW);
       }
     Serial.write("\n--------------------------------------\n");
     }
    }
  
 
} 
