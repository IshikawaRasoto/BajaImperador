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

    volatile float velocidade;
    volatile uint16_t RPM;
    volatile float velocidadeRodaE;
    volatile float velocidadeRodaD;
    volatile float velocidadeEixoT;

    volatile uint16_t contadorRPM;
    volatile uint16_t contadorRodaD;
    volatile uint16_t contadorRodaE;
    volatile uint16_t contadorEixoT;

    int valorBateria;
    uint8_t percentualBateria;

    bool estadoFreio;


    bool atualizado;

    void atualizarVelocidadeRodaE();
    void atualizarVelocidadeRodaD();
    void atualizarVelocidadeEixoT();
    void atualizarRPM();
    void atualizarVelocidade();
    void atualizarFreio();
    
  public:

    Veiculo();
    ~Veiculo();

    void incrementarRodaE();
    void incrementarRodaD();
    void incrementarEixoT();
    void incrementarRPM();



    float getVelocidade();
    uint16_t getRPM();
    float getVelocidadeRodaE();
    float getVelocidadeRodaD();
    float getVelocidadeEixoT();
    uint8_t getBateria();
    int8_t getFreio();


    bool estaAtualizado();

    void atualizar();
    void atualizarBateria();

};