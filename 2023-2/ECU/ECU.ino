/*

  TESTE_JUNCAO_MODULOS.ino - Arquivo para produção e prototipagem do código para atingir sua versão final.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#include "defines.hpp"
#include "Codigo.hpp"

hw_timer_t* timer_500ms = nullptr;

Codigo cod;

void interrupcaoRodaE()
{
  cod.incrementarRodaE();
}

void interrupcaoRodaD()
{
  cod.incrementarRodaD();
}

void interrupcaoEixoT()
{
  cod.incrementarEixoT();
}
void interrupcaoRPM(){
  cod.incrementarRPM();
}

bool led = false;

void interrupcaoTimer()
{
  noInterrupts();

  cod.atualizarInt();

  /*if(led)
  {
    led = false;
    digitalWrite(PINO_BATERIA, LOW);
  }
  else
  {
    led = true;
    digitalWrite(PINO_BATERIA, HIGH);
  }*/

  interrupts();
}

void configurarTimer()
{
  timer_500ms = timerBegin(0, 80, true);
  timerAttachInterrupt(timer_500ms, &interrupcaoTimer, true);
  timerAlarmWrite(timer_500ms, 500000, true);
  timerAlarmEnable(timer_500ms);
}

void configurarIntPin()
{
  attachInterrupt(PINO_RPM, interrupcaoRPM, FALLING);
  attachInterrupt(PINO_RODAD, interrupcaoRodaD, RISING);
  attachInterrupt(PINO_RODAE, interrupcaoRodaE, RISING);
  attachInterrupt(PINO_EIXOT, interrupcaoEixoT, RISING);

  //pinMode(PINO_BATERIA, OUTPUT);
}

void setup(){
  cod.configurar();
  configurarTimer();
  configurarIntPin();

}

void loop(){
  cod.executar();
}