/*

  ImperadorIR.cpp - Arquivo para declaração da biblioteca Imperador Infra-vermelho.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#include "ImperadorIR.hpp"

ImperadorIR::ImperadorIR():
  iniciado(false),
  ir(Adafruit_MLX90614()),
  tempAmb(NAO_INICIADO),
  tempObj(NAO_INICIADO)
{}

ImperadorIR::~ImperadorIR(){}

bool ImperadorIR::iniciar()
{
  bool retorno = ir.begin();
  if(!retorno)
  {
    Serial.println("Falha ao iniciar InfraVermelho");
    iniciado = false;
    return false;
  }
  iniciado = true;
  Serial.println("Infravermelho OK!");
  return true;
}

void ImperadorIR::atualizar()
{
  if(!iniciado) return;
  
  tempAmb = ir.readAmbientTempC();
  tempObj = ir.readObjectTempC();
}

double ImperadorIR::get_temperatura_ambiente(){return tempAmb;}
double ImperadorIR::get_temperatura_objeto(){return tempObj;}

bool ImperadorIR::get_iniciado(){return iniciado;}