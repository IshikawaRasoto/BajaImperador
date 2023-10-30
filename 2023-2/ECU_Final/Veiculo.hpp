/*

  Veiculo.hpp - Arquivo para declaração da biblioteca do Sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

  Essa biblioteca possui o código Procedural.

*/

#pragma once

#include <Arduino.h>

class Veiculo
{
  private:

    volatile int8_t velocidade;
    volatile int16_t rpm;

    volatile unsigned long tempo_velocidade;
    volatile unsigned long tempo_rpm;

    int valor_bateria;
    float tensao_bateria;

    bool estado_freio;

    void atualizar_freio();
    
  public:

    Veiculo();
    ~Veiculo();



    int8_t get_velocidade();
    int16_t get_rpm();
    int8_t get_freio();
    float get_bateria();


    bool esta_atualizado();

    void atualizar();
    void atualizar_bateria();
    void atualizar_velocidade();
    void atualizar_rpm();

    void calcular_velocidade();
    void calcular_rpm();

};