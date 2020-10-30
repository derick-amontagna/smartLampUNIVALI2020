#ifndef matriz_h
#define matriz_h

#define BLYNK_PRINT Serial

/// Bibliotecas
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

/// Definindo constante 
#define ledPin 21 //Pino digital para o LED
#define ldrPin 35 //Pino analogico para o LDR
#define pinoPIR 19 //Pino digital para o sensor de presença

/// Funções
extern void modoInteligente();
extern void modoFerias();
extern void modoManual();

#endif
