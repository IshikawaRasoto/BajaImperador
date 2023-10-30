/*

  ImperadorAcelerometro.hpp - Arquivo para declaração da biblioteca ImperadorAcelerometro.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#pragma once

#include <Arduino.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define NAO_INICIADO -20

struct Vetor3
{
  float x;
  float y;
  float z;
};

class ImperadorAcelerometro
{

  private:

    Adafruit_MPU6050 acelerometro;
    Vetor3 acel;
    Vetor3 gir;
    float temp;
    bool iniciado;

  public:

    ImperadorAcelerometro();
    ~ImperadorAcelerometro();

    bool iniciar(uint8_t escalaAcelerometro = 8, uint16_t escalaGiroscopio = 500, uint8_t faixaFiltro = 21);
    void atualizar();

    Vetor3 get_aceleracao();
    Vetor3 get_giro();
    float get_temperatura();
    bool get_iniciado();
};