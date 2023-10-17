/*

  Codigo.hpp - Biblioteca principal do sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

  Essa biblioteca possui o código Procedural.

*/

#pragma once 

#include <Arduino.h>

#include "Veiculo.hpp"
#include "ImperadorGPS.hpp"
#include "ImperadorAcelerometro.hpp"
#include "ImperadorIR.hpp"

class Codigo
{

  private:

    Veiculo baja;
    ImperadorGPS gps;
    ImperadorAcelerometro acelerometro;
    ImperadorIR infraVermelho;

    bool dev;

    uint16_t contadorRodaE;
    uint16_t contadorRodaD;
    uint16_t contadorEixoT;
    uint16_t contadorRPM;

    void configuracaoPinos();
    void iniciarSerial();

    void enviarDados();
    void enviarSerial();
    void enviarLora();
    void enviarCAN();


    void receberDados();
    void verificarSerial();
    void verificarLora();
    void verificarCAN();

  public:

    Codigo();
    ~Codigo();

    void configurar();
    void executar();

    void atualizar();
    void atualizarInt();
    void incrementarRPM();
    void incrementarRodaE();
    void incrementarRodaD();
    void incrementarEixoT();

};