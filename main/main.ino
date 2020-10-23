

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

/** Estas são as declarações relacionadas ao CircusESP32Lib**/
char ssid[] = "GVT-A6E1";                         
char password[] = "1965002410";                   
char token[] = "eyJhbGciOiJIUzI1NiJ9.eyJqdGkiOiIyMTU5In0.oldlOloegRoX_4FjidV5uoSQN1uCvKHnsBNZhkP0m2g";                               
char server[] = "www.circusofthings.com";
char estadoDoLed_key[] = "18454";                           
char LDR_key [] = "11910";                        
char sensorDePresenca_key [] = "16510";                        
CircusESP32Lib circusESP32(server,ssid,password); // O objeto que representa um ESP32 para você poder solicitar gravação ou leitura

/// Funções
//Sensores
void verificandoLDR()
{

 ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
 
 //se o valor lido for maior ou igual que 1500, liga o led
 if (ldrValor>= 1500) digitalWrite(ledPin,HIGH);
 else digitalWrite(ledPin,LOW);
  
}

void verificandoPresenca()
{

 if(digitalRead(pinoPIR) == HIGH) digitalWrite(ledPin, HIGH); 
 else digitalWrite(ledPin, LOW); //APAGA O LED
  
}


 
void setup() 
{
 pinMode(ledPin,OUTPUT); //define a ledPin como saída
 pinMode(ldrPin,INPUT); //define a ldrPin como saída
 pinMode(pinoPIR, INPUT); //DEFINE O PINO COMO ENTRADA
  
 Serial.begin(115200); //Inicia a comunicação serial
 circusESP32.begin(); // Deixe o objeto Circuis configurar-se para uma conexão SSL / Secure
}


void loop() 
{

  double dashboard_order = circusESP32.write(estadoDoLed_key, token);

}
