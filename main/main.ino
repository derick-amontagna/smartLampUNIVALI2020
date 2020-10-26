/*
* Lampada Inteligente
* Derick Abreu Montagna e Edmiel Loiola de Oliveira 
* 
* É um projeto proposto pela disciplina de sistemas embarcados para obter a nota da M2, de maneira, que é proposto a realização de uma lampada inteligente com sensor de presença
* e sensor de luminosidade.
* 21/10/2020
*/

// Bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Definindo constante 
#define ledPin 21 //Pino digital para o LED
#define ldrPin 35 //Pino analogico para o LDR
#define pinoPIR 19 //Pino digital para o sensor de presença
#define BLYNK_PRINT Serial
WidgetLED statusLed(V0);

int ldrValor = 0; //Valor lido do LDR
int randNumber = 0;
int manual_order = 0;

/** Estas são as declarações relacionadas ao the Blynk App**/
char auth[] = "_qtOUSD-l2L7iMNt5x955DfegMSkXSEi";
char ssid[] = "GVT-A6E1";                         
char pass[] = "1965002410";                   

/// Configurando portas virtuais Blynk App
BLYNK_WRITE(V1){
  switch (param.asInt()){
    case 1: {
      modoInteligente();
      break;
    }
    case 2:{
      modoFerias();
      break;
    }
    case 3:{
      modoManual();
      break;
    }
  }
}

BLYNK_WRITE(V3){
    manual_order = param.asInt(); 
}

/// Funções
void modoInteligente(){
  ldrValor = analogRead(ldrPin);
  if ((ldrValor>= 900) && (digitalRead(pinoPIR) == HIGH)){
    statusLed.on();
    digitalWrite(ledPin, HIGH);
  }
  else {
    statusLed.off();
    digitalWrite(ledPin, LOW);
  }
}

void modoFerias(){
  ldrValor = analogRead(ldrPin);
  randNumber = random(10, 100); // Numero aleatorio entre 10 e 99
  Blynk.virtualWrite(V2, randNumber);
  if (ldrValor>= 900 && randNumber >= 50){
    statusLed.on();
    digitalWrite(ledPin, HIGH);
    delay(3000);
  }
  else {
    statusLed.off();
    digitalWrite(ledPin, LOW);
  }
}

void modoManual(){
  if (manual_order == 1) {
      statusLed.on();
      digitalWrite(ledPin, HIGH);
    }
    else {
      statusLed.off();
      digitalWrite(ledPin, LOW);
    }
}


void setup() {
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída
 pinMode(pinoPIR, INPUT); //define o pinoPIR como saida
 Serial.begin(115200); //Inicia a comunicação serial
 Blynk.begin(auth, ssid, pass);
}

void loop(){
  Blynk.run(); 
}
