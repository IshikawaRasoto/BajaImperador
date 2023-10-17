/*

  ImperadorIR.cpp - Arquivo para declaração da biblioteca Imperador Infra-vermelho.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#include "ImperadorIR.hpp"

ImperadorIR::ImperadorIR():
  ir(Adafruit_MLX90614())
{}

ImperadorIR::~ImperadorIR(){}

bool ImperadorIR::iniciar(){return ir.begin();}

void ImperadorIR::atualizar()
{
  tempAmb = ir.readAmbientTempC();
  tempObj = ir.readObjectTempC();
}

double ImperadorIR::getTemperaturaAmbiente(){return tempAmb;}
double ImperadorIR::getTemperaturaObjeto(){return tempObj;}