/*
* Lampada Inteligente
* Derick Abreu Montagna e Edmiel Loiola de Oliveira 
* 
* É um projeto proposto pela disciplina de sistemas embarcados para obter a nota da M2, de maneira, que é proposto a realização de uma lampada inteligente com sensor de presença
* e sensor de luminosidade.
* 21/10/2020
*/

/// Bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/// Definindo constante 
#define ledPin 21 //Pino digital para o LED
#define ldrPin 35 //Pino analogico para o LDR
#define pinoPIR 19 //Pino digital para o sensor de presença
#define BLYNK_PRINT Serial
WidgetLED statusLed(V0);

int ldrValor = 0; //Valor lido do LDR
int randNumber = 0;
int manual_order = 0;

/// Estas são as declarações relacionadas ao the Blynk App
char auth[] = "_qtOUSD-l2L7iMNt5x955DfegMSkXSEi";
char ssid[] = "GVT-A6E1";                         
char pass[] = "1965002410";                   

// Configurando portas virtuais Blynk App
BLYNK_CONNECTED(){
  Blynk.syncAll();
}

BLYNK_WRITE(V1){
  switch (param.asInt()){
    case 1: {
      modoInteligente();
      Blynk.syncVirtual(V1);
      break;
    }
    case 2:{
      modoFerias();
      Blynk.syncVirtual(V1);
      break;
    }
    case 3:{
      modoManual();
      Blynk.syncVirtual(V1);
      break;
    }
  }
}

BLYNK_WRITE(V3){
    manual_order = param.asInt();
    Blynk.syncVirtual(V3); 
}

/// Funções
void modoInteligente(){
  ldrValor = analogRead(ldrPin); // Valor entre 0 e 4095
  Blynk.virtualWrite(V4, ldrValor); 
  Blynk.virtualWrite(V5, digitalRead(pinoPIR)); // Delay entre medições, pode ir de 5 - 300 segundos / O alcance de detecção pode ir 3 a 7 metros / Ajustado manualmente no sensor
  if ((ldrValor>= 1600) && (digitalRead(pinoPIR) == HIGH)){
    statusLed.on();
    digitalWrite(ledPin, HIGH);
  }
  else {
    statusLed.off();
    digitalWrite(ledPin, LOW);
  }
}

void modoFerias(){
  ldrValor = analogRead(ldrPin); // Valor entre 0 e 4095
  Blynk.virtualWrite(V4, ldrValor);
  randNumber = random(0, 100); // Numero aleatorio entre 0 e 99
  Blynk.virtualWrite(V2, randNumber);
  if (ldrValor>= 1600 && randNumber >= 90){
    if(digitalRead(ledPin) == LOW){
      statusLed.on();
      digitalWrite(ledPin, HIGH); 
    }
    else{
      statusLed.off();
      digitalWrite(ledPin, LOW);
    }
  }
  else if (ldrValor <= 1600){
    digitalWrite(ledPin, LOW);
  }
}

void modoManual(){
  Blynk.syncVirtual(V3); 
  if (manual_order == 1) {
      statusLed.on();
      digitalWrite(ledPin, HIGH);
    }
    else {
      statusLed.off();
      digitalWrite(ledPin, LOW);
    }
}

/// Programa principal
void setup() {
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída
 pinMode(pinoPIR, INPUT); //define o pinoPIR como saida
 Serial.begin(115200); //Inicia a comunicação serial
 Blynk.begin(auth, ssid, pass);
}

void loop(){
  Blynk.run(); // Para o App se comunicar a todo instante
}
