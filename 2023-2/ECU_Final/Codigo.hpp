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
    ImperadorIR infravermelho;

    bool dev_mode;

    bool box;

    void configurar_pinos();
    void iniciar_serial();

    void atualizar_eixo_traseiro();
    void atualizar_rpm();

    void enviar_dados();
    void enviar_serial();
    void enviar_lora();
    void enviar_CAN();


    void receber_dados();
    void verificar_serial();
    void verificar_lora();
    void verificar_CAN();

  public:

    Codigo();
    ~Codigo();

    void configurar();
    void executar();

    void atualizar();

};