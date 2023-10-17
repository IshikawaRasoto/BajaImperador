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

    int8_t velocidade;
    volatile uint16_t RPM;

    unsigned long tempo_velocidade;
    unsigned long tempo_rpm;

    int valor_bateria;
    float tensao_bateria;

    bool estado_freio;


    void calcular_velocidade();
    void calcular_rpm();
    void atualizar_freio();
    
  public:

    Veiculo();
    ~Veiculo();



    int8_t get_velocidade();
    uint16_t get_RPM();
    uint8_t get_bateria();
    int8_t get_freio();


    bool esta_atualizado();

    void atualizar();
    void atualizar_bateria();

};