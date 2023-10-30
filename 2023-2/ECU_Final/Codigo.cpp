/*

  Codigo.cpp - Principal código do sistema.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

  Essa biblioteca possui o código Procedural.

*/

#include "Codigo.hpp"
#include "defines.hpp"

Codigo::Codigo():
  
  gps(BAUD_GPS, RX_GPS, TX_GPS),
  dev_mode(false),
  box(false),
  racing_mode(false)
{}

Codigo::~Codigo()
{}

void Codigo::configurar()
{
  iniciar_serial();
  Serial.println("Serial iniciada");
  delay(1000);
  configurar_pinos();
  Serial.println("Pinos Configurados");

  acelerometro.iniciar();
  infravermelho.iniciar();
  can.iniciar();
}

void Codigo::executar()
{
  //Serial.println("Atualizar");
  atualizar();
  //Serial.println("Eviar Dados");
  enviar_dados();
  //Serial.println("Verificar Serial");
  verificar_serial();
  //verificar_CAN();
}




void Codigo::configurar_pinos()
{
  pinMode(PINO_RODAD, INPUT);
  pinMode(PINO_RODAE, INPUT);
  pinMode(PINO_EIXOT, INPUT);
  pinMode(PINO_RPM, INPUT);

  pinMode(PINO_FREIO, INPUT);

  pinMode(PINO_LED, OUTPUT);

  digitalWrite(PINO_LED, HIGH);
}

void Codigo::iniciar_serial()
{
  Serial.begin(BAUD_SERIAL);
  Serial2.begin(BAUD_SERIAL, SERIAL_8N1, RX_LORA, TX_LORA );
}

void Codigo::enviar_dados()
{
  //Serial.println("Envio Lora");
  enviar_serial();
  //Serial.println("Envio CAN");
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
    Serial.print("|GIROX:");
    Serial.print(acelerometro.get_giro().x);
    Serial.print("|GIROY:");
    Serial.print(acelerometro.get_giro().y);
    Serial.print("|GIROZ:");
    Serial.print(acelerometro.get_giro().z);
    Serial.print("|LAT:");
    Serial.print(gps.get_latitude());
    Serial.print("|LNG:");
    Serial.print(gps.get_longitude());
    Serial.print("|CURSO:");
    Serial.println(gps.get_curso());
    return;
  }

  //!dev
  
  Serial2.print("R");
  Serial2.print(baja.get_rpm()/10);

  Serial2.print("V");
  Serial2.print(baja.get_velocidade(),0);

  Serial2.print("T");
  Serial2.print(infravermelho.get_temperatura_objeto(), 0);

  Serial2.print("B");
  Serial2.print(baja.get_bateria());

  Serial2.print("F");
  Serial2.println(baja.get_freio());
}

void Codigo::enviar_CAN()
{ 
  can.enviar_rv(baja.get_rpm(), baja.get_velocidade());
  delay(50);
  //can.enviar_btb(baja.get_bateria(), infravermelho.get_temperatura_objeto(), box);
}

void Codigo::verificar_serial(){
  if(Serial.available())
  {
    String comando = Serial.readString();

    if(comando == "DEV" || comando == "dev")
    {
      dev_mode = true;
      Serial.println("DEV MODE");
    }
    else if(comando == "NORMAL" || comando == "normal")
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

  if(Serial2.available())
  {
    String comando = Serial2.readString();

    if(comando == "BOX")
    {
      box = !box;
      box ? Serial.println("BOX BOX") : Serial.println("NO BOX");
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
  acelerometro.atualizar();
}

void Codigo::atualizar_eixo_traseiro()
{
  baja.calcular_velocidade();
}

void Codigo::atualizar_rpm()
{
  baja.calcular_rpm();
}