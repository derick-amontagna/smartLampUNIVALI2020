/*
* Lampada Inteligente
* Derick Abreu Montagna e Edmiel Loiola de Oliveira 
* 
* É um projeto proposto pela disciplina de sistemas embarcados para obter a nota da M2, de maneira, que é proposto a realização de uma lampada inteligente com sensor de presença
* e sensor de luminosidade.
* 21/10/2020
*/

// Bibliotecas
#include <CircusESP32Lib.h>

// Definindo constante 
#define ledPin 21 //Pino digital para o LED
#define ldrPin 35 //Pino analogico para o LDR
#define pinoPIR 19 //Pino digital para o sensor de presença

int ldrValor = 0; //Valor lido do LDR
int randNumber = 0;
int statusLed = 0;
int modoSelecionado = 0;

/** Estas são as declarações relacionadas ao CircusESP32Lib**/
char ssid[] = "GVT-A6E1";                         
char password[] = "1965002410";                   
char token[] = "eyJhbGciOiJIUzI1NiJ9.eyJqdGkiOiIyMTU5In0.oldlOloegRoX_4FjidV5uoSQN1uCvKHnsBNZhkP0m2g";                               
char server[] = "www.circusofthings.com";
char statusDoLed_key[] = "18454";                           
char modos_key [] = "26204";    
char ligDes_key[] = "1476";
char randNumber_key[] = "8819";                                            
CircusESP32Lib circusESP32(server,ssid,password); // O objeto que representa um ESP32 para você poder solicitar gravação ou leitura


/// Funções
void modoInteligente()
{
  ldrValor = analogRead(ldrPin);
  if ((ldrValor>= 900) && (digitalRead(pinoPIR) == HIGH)){
    statusLed = 1;
    circusESP32.write(statusDoLed_key,statusLed,token);
    digitalWrite(ledPin, HIGH);
  }
  else {
    statusLed = 0;
    circusESP32.write(statusDoLed_key,statusLed,token);
    digitalWrite(ledPin, LOW);
  }
}

void modoFerias()
{
  ldrValor = analogRead(ldrPin);
  randNumber = random(10, 100); // Numero aleatorio entre 10 e 99
  circusESP32.write(randNumber_key,randNumber,token);
  if (ldrValor>= 900 && randNumber >= 50) 
  {
    statusLed = 1;
    circusESP32.write(statusDoLed_key,statusLed,token);
    digitalWrite(ledPin, HIGH);
    delay(3000);
  }
  else 
  {
    statusLed = 0;
    circusESP32.write(statusDoLed_key,statusLed,token);
    digitalWrite(ledPin, LOW);
  }
}

void modoManual()
{
  double dashboard_order = circusESP32.read(ligDes_key, token);
  if (dashboard_order == 1) 
  {
    digitalWrite(ledPin, HIGH);
    statusLed = 1;
    circusESP32.write(statusDoLed_key,statusLed,token);
  }
  else 
  {
    digitalWrite(ledPin, LOW);
    statusLed = 0;
    circusESP32.write(statusDoLed_key,statusLed,token);
  }
}


void setup() 
{
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída
 pinMode(pinoPIR, INPUT); //define o pinoPIR como saida
 Serial.begin(115200); //Inicia a comunicação serial
 circusESP32.begin(); // Deixe o objeto Circuis configurar-se para uma conexão SSL / Secure
}


void loop() 
{
  modoSelecionado = circusESP32.read(modos_key, token);
  if (modoSelecionado == 0) modoInteligente();
  else if (modoSelecionado == 1) modoFerias();
  else modoManual();
}
