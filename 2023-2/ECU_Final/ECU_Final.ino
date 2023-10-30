/* 

    ECU_Final.ino - Código destinado para o J12 ir para o Regional Sul de 2023.
    Criado em 17/10/2023 por: Lambari.

*/

#include "defines.hpp"
#include "Codigo.hpp"

hw_timer_t* timer_500ms = nullptr;

Codigo cod;

/*
    As duas funções abaixo estão comentadas pois serão desenvolvidas para o J13
*/

//void interrupcao_roda_esquerda(){}

//void interrupcao_roda_direita(){}

void interrupcao_eixo_traseiro()
{
    //Serial.println("INT ET");
    cod.atualizar_eixo_traseiro();
}

void interrupcao_rpm()
{
  //Serial.println("INT RPM");
    cod.atualizar_rpm();
}



void setup()
{
    attachInterrupt(digitalPinToInterrupt(PINO_EIXOT), interrupcao_eixo_traseiro, RISING);
    attachInterrupt(digitalPinToInterrupt(PINO_RPM), interrupcao_rpm, RISING);
    cod.configurar();
}

void loop()
{
    cod.executar();
}
