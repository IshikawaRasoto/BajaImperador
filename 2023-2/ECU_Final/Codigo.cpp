/*

  Codigo.cpp - Principal código do sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

  Essa biblioteca possui o código Procedural.

*/

#include "Codigo.hpp"
#include "defines.hpp"

Codigo::Codigo():
  
  gps(BAUD_GPS, RX_GPS, TX_GPS),
  acelerometro(),
  infravermelho(),
  dev_mode(false),
  box(false),
  racing_mode(false)
{}

Codigo::~Codigo()
{}

void Codigo::configurar()
{
  iniciar_serial();
  delay(1000);
  configurar_pinos();

  if(!acelerometro.iniciar())
  {
    Serial.println("Falha ao iniciar Acelerômetro.");
  }
  else
  {
    Serial.println("Acelerômetro iniciado");
  }

  if(!infravermelho.iniciar())
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
  enviar_dados();
  verificar_serial();
  verificar_CAN();
}




void Codigo::configurar_pinos()
{
  pinMode(PINO_RODAD, INPUT);
  pinMode(PINO_RODAE, INPUT);
  pinMode(PINO_EIXOT, INPUT);
  pinMode(PINO_RPM, INPUT);

  pinMode(PINO_FREIO, INPUT);
}

void Codigo::iniciar_serial()
{
  Serial.begin(BAUD_SERIAL);
}

void Codigo::enviar_dados()
{
  enviar_serial();
  enviar_CAN();
}

void Codigo::enviar_serial()
{
  if(dev_mode)
  {
    Serial.print("RPM:");
    Serial.print(baja.get_rpm());
    Serial.print("|Vel:");
    Serial.print(baja.get_velocidade(), 0);
    Serial.print("|TEMP:");
    Serial.print(infravermelho.get_temperatura_objeto(), 0);
    Serial.print("|BAT:");
    Serial.print(baja.get_bateria());
    Serial.print("|FRE:");
    Serial.print(baja.get_freio());
    Serial.print("|ACLX:");
    Serial.print(acelerometro.get_aceleracao().x);
    Serial.print("|ACLY:");
    Serial.print(acelerometro.get_aceleracao().y);
    Serial.print("|ACLZ:");
    Serial.print(acelerometro.get_aceleracao().z);
    Serial.print("|LAT:");
    Serial.print(gps.get_latitude());
    Serial.print("|LNG:");
    Serial.print(gps.get_longitude());
    Serial.print("|CURSO:");
    Serial.println(gps.get_curso());
    return;
  }

  //!dev
  
  Serial.print("R");
  Serial.print(baja.get_rpm()/10);

  Serial.print("V");
  Serial.print(baja.get_velocidade(),0);

  Serial.print("T");
  Serial.print(infravermelho.get_temperatura_objeto(), 0);

  Serial.print("B");
  Serial.print(baja.get_bateria());

  Serial.print("F");
  Serial.println(baja.get_freio());
}

void Codigo::enviar_CAN()
{

}

void Codigo::verificar_serial(){
  if(Serial.available())
  {
    String comando = Serial.readString();

    if(comando == "DEV")
    {
      dev_mode = true;
    }
    else if(comando == "NOTDEV")
    {
      dev_mode = false;
    }
    else if(comando == "BOX")
    {
      box = !box;
      box ? Serial.println("BOX BOX") : Serial.println("NO BOX");
    }
	  else if(comando == "RACE")
	  {
		  racing_mode = true;
	  }
    else if(comando == "TESTE")
    {
      racing_mode = false;
    }
  }
}


void Codigo::verificar_CAN(){}


void Codigo::atualizar()
{
  gps.atualizar();
  infravermelho.atualizar();
  baja.atualizar();
  baja.atualizar_bateria();
  if(racing_mode)
  {
    acelerometro.atualizar();
    // Salvar no SD 
  }
}

void Codigo::atualizar_eixo_traseiro()
{
  baja.calcular_velocidade();
}

void Codigo::atualizar_rpm()
{
  baja.calcular_rpm();
}
