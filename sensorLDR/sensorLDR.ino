/*
* Lampada Inteligente
* Derick Abreu Montagna e Edmiel Loiola de Oliveira 
* 
* É um projeto proposto pela disciplina de sistemas embarcados para obter a nota da M2, de maneira, que é proposto a realização de uma lampada inteligente com sensor de presença
* e sensor de luminosidade.
* 21/10/2020
*/

//Sensor de luz com LDR
 
const int ledPin = 21; //Led no pino 7
const int ldrPin = 35; //LDR no pino analígico 8
int ldrValor = 0; //Valor lido do LDR
 
void setup() {
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída
 Serial.begin(115200); //Inicia a comunicação serial
}
 
void loop() {
 ///ler o valor do LDR
 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 //se o valor lido for maior ou igual que 1500, liga o led
 if (ldrValor >= 900) digitalWrite(ledPin,HIGH);
 // senão, apaga o led
 else digitalWrite(ledPin,LOW);
 delay(100);
}
