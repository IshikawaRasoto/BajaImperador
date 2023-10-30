/*

  Veiculo.cpp - Arquivo para programação da biblioteca do Sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#include "Veiculo.hpp"
#include "defines.hpp"

/* 

  Classe Veículo

*/

Veiculo::Veiculo():
  velocidade(0),
  rpm(0),
  tempo_velocidade(millis()),
  tempo_rpm(millis()),
  valor_bateria(0),
  tensao_bateria(0.0),
  estado_freio(false)
{}

Veiculo::~Veiculo(){}

void Veiculo::atualizar()
{
  atualizar_freio();
  atualizar_bateria();
  atualizar_velocidade();
  atualizar_rpm();
}


void Veiculo::atualizar_freio()
{
  digitalRead(PINO_FREIO) ? estado_freio = true : estado_freio = false;
}

void Veiculo::atualizar_bateria()
{
  valor_bateria = analogRead(PINO_BATERIA);
  tensao_bateria = ((float)valor_bateria / BATERIA_CHEIA) * 12.8;
}

void Veiculo::atualizar_velocidade()
{
  //Serial.println("I V");
  if(millis() - tempo_velocidade > 1000)
  {
    velocidade = 0;
    tempo_velocidade = millis();
  } 
}

void Veiculo::atualizar_rpm()
{
  //Serial.println("I R");
  if(millis() - tempo_rpm > 1000)
  {
    rpm = 0;
    tempo_rpm = millis();
  } 
}

void Veiculo::calcular_velocidade()
{
  volatile unsigned int aux = millis();
  velocidade = (COMPRIMENTO * (1000/7.0) * 3.6 / (aux - tempo_velocidade));
  tempo_velocidade = aux;
}

void Veiculo::calcular_rpm()
{
  volatile unsigned int aux = millis();
  
  if(aux - tempo_rpm < 10) return;
  
  rpm = int(60000/(aux-tempo_rpm));
  tempo_rpm = aux;
}

int8_t Veiculo::get_velocidade() {return velocidade;}
int16_t Veiculo::get_rpm() {return rpm;}
float Veiculo::get_bateria() {return tensao_bateria;}

int8_t Veiculo::get_freio()
{
  return (estado_freio) ? true : false;
}