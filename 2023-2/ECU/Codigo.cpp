/*

  Codigo.cpp - Principal código do sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

  Essa biblioteca possui o código Procedural.

*/

#include "Codigo.hpp"
#include "defines.hpp"

Codigo::Codigo():
  contadorRodaE(0),
  contadorRodaD(0),
  contadorEixoT(0),
  contadorRPM(0),
  gps(BAUD_GPS, RX_GPS, TX_GPS),
  acelerometro(),
  infraVermelho(),
  dev(false)
{}

Codigo::~Codigo()
{}

void Codigo::configurar()
{
  iniciarSerial();
  delay(1000);
  configuracaoPinos();

  if(!acelerometro.iniciar())
  {
    Serial.println("Falha ao iniciar Acelerômetro.");
  }
  else
  {
    Serial.println("Acelerômetro iniciado");
  }

  if(!infraVermelho.iniciar())
  {
    Serial.println("Falha ao iniciar InfraVermelho.");
  }
  else
  {
    Serial.println("Infravermelho iniciado");
  }
}

void Codigo::executar()
{
  atualizar();
  enviarDados();
  receberDados();
}




void Codigo::configuracaoPinos()
{
  pinMode(PINO_RODAD, INPUT);
  pinMode(PINO_RODAE, INPUT);
  pinMode(PINO_EIXOT, INPUT);
  pinMode(PINO_RPM, INPUT);

  pinMode(PINO_FREIO, INPUT);
}

void Codigo::iniciarSerial()
{
  Serial.begin(BAUD_SERIAL);
}

void Codigo::enviarDados()
{
  enviarSerial();
  enviarCAN();
}

void Codigo::enviarSerial()
{
  if(dev)
  {
    Serial.print("RPM:");
    Serial.print(baja.getRPM());
    Serial.print("|Vel:");
    Serial.print(baja.getVelocidade(), 0);
    Serial.print("|VRD:");
    Serial.print(baja.getVelocidadeRodaD(),0);
    Serial.print("|VRE:");
    Serial.print(baja.getVelocidadeRodaE(),0);
    Serial.print("|VET:");
    Serial.print(baja.getVelocidadeEixoT(),0);
    Serial.print("|TEMP:");
    Serial.print(infraVermelho.getTemperaturaObjeto(), 0);
    Serial.print("|BAT:");
    Serial.print(baja.getBateria());
    Serial.print("|FRE:");
    Serial.print(baja.getFreio());
    Serial.print("|ACLX:");
    Serial.print(acelerometro.getAceleracao().x);
    Serial.print("|ACLY:");
    Serial.print(acelerometro.getAceleracao().y);
    Serial.print("|ACLZ:");
    Serial.print(acelerometro.getAceleracao().z);
    Serial.print("|LAT:");
    Serial.print(gps.getLatitude());
    Serial.print("|LNG:");
    Serial.print(gps.getLongitude());
    Serial.print("|CURSO:");
    Serial.println(gps.getCurso());
    return;
  }

  //!dev
  
  Serial.print("R");
  Serial.print(baja.getRPM());

  Serial.print("V");
  Serial.print(baja.getVelocidade(),0);

  Serial.print("T");
  Serial.print(infraVermelho.getTemperaturaObjeto(), 0);

  Serial.print("B");
  Serial.print(baja.getBateria());

  Serial.print("F");
  Serial.println(baja.getFreio());
}

void Codigo::enviarLora()
{

}

void Codigo::enviarCAN()
{

}

void Codigo::receberDados()
{
  verificarSerial();
}

void Codigo::verificarSerial(){
  if(Serial.available())
  {
    String comando = Serial.readString();

    if(comando == "DEV" || comando == "dev")
    {
      dev = true;
    }
    else if(comando == "NORMAL" || comando == "normal")
    {
      dev = false;
    }
  }
}

void Codigo::verificarLora(){}

void Codigo::verificarCAN(){}


void Codigo::atualizar()
{
  gps.atualizar();
  infraVermelho.atualizar();
  acelerometro.atualizar();
  baja.atualizarBateria();
}

void Codigo::atualizarInt()
{
  baja.atualizar();
}

void Codigo::incrementarRodaE(){baja.incrementarRodaE();}
void Codigo::incrementarRodaD(){baja.incrementarRodaD();}
void Codigo::incrementarEixoT(){baja.incrementarEixoT();}
void Codigo::incrementarRPM(){baja.incrementarRPM();}