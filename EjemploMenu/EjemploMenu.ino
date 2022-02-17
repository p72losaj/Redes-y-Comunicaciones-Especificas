char opcion; 
char valor;
int puerto;
int val;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  while(!Serial){;}
}

void loop() {
  // put your main code here, to run repeatedly:

}
