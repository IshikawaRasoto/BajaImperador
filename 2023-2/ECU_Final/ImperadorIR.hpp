/*

  ImperadorIR.hpp - Arquivo para declaração da biblioteca Imperador Infra-vermelho.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#pragma once

#define NAO_INICIADO -50

#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_MLX90614.h>

#include "defines.hpp"

class ImperadorIR
{

  private:

    Adafruit_MLX90614 ir;

    bool iniciado;

    double tempAmb;
    double tempObj;

  public:

    ImperadorIR();
    ~ImperadorIR();

    bool iniciar();

    void atualizar();

    double get_temperatura_objeto();
    double get_temperatura_ambiente(); 
    bool get_iniciado();
};