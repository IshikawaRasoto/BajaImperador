/*

  SD_IMPERADOR.hpp - Arquivo para declaração da biblioteca SD_IMPERADOR.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/



#pragma once

#include <Arduino.h>

#include <SD.h>
#include <SPI.h>
#include "ImperadorAcelerometro.hpp"

class ImperadorSD
{

  private:
    
    File arquivo;

    void escrever(const char* path, const char* mensagem);

  public:
    
    ImperadorSD();
    ~ImperadorSD();

    bool iniciar(const int CS);

    
    void registrar(float velocidade, uint16_t rpm, float velRodaE, float velRodaD, float velEixoT, uint8_t bateria, int8_t freio, double temperaturaObj, double velocidadeGps, double latitude, double longitude, double altitude, double curso, Vetor3 aceleracao, Vetor3 giroscopio);
    void registrar(float velocidade, uint16_t rpm, uint8_t bateria, int8_t freio, double temperaturaObj, double latitude, double longitude);
    void registrar(float velocidade, uint16_t rpm, uint8_t bateria, int8_t freio);
    void registrar(float velocidade, uint16_t rpm);

    void ler(const char* path);

};

