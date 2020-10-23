/*
* Lampada Inteligente
* Derick Abreu Montagna e Edmiel Loiola de Oliveira 
* 
* É um projeto proposto pela disciplina de sistemas embarcados para obter a nota da M2, de maneira, que é proposto a realização de uma lampada inteligente com sensor de presença
* e sensor de luminosidade.
* 21/10/2020
*/

//Sensor de luz com LDR
 
const int ledPin = 19; //Led no pino 7
const int ldrPin = 35; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR

const int pinoPIR = 19; //PINO DIGITAL UTILIZADO PELO SENSOR DE PRESENÇA
const int pinoLED = 21; //PINO DIGITAL UTILIZADO PELO LED
 
void setup() {
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída

 pinMode(pinoLED, OUTPUT); //DEFINE O PINO COMO SAÍDA
 pinMode(pinoPIR, INPUT); //DEFINE O PINO COMO ENTRADA
  
 Serial.begin(115200); //Inicia a comunicação serial
}
 
void loop() {
 ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 //se o valor lido for maior ou igual que 1500, liga o led
 if (ldrValor>= 1500) digitalWrite(ledPin,HIGH);
 // senão, apaga o led
 else digitalWrite(ledPin,LOW);
 delay(100);

 if(digitalRead(pinoPIR) == HIGH){ //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
    digitalWrite(pinoLED, HIGH); //ACENDE O LED
 }else{ //SENÃO, FAZ
  digitalWrite(pinoLED, LOW); //APAGA O LED
 }
 
}
