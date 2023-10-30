/*

  ImperadorAcelerometro.cpp - Arquivo para declaração da biblioteca ImperadorAcelerometro.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#include "ImperadorAcelerometro.hpp"

ImperadorAcelerometro::ImperadorAcelerometro():
  iniciado(false),
  temp(NAO_INICIADO)
{
  acel.x = (NAO_INICIADO);
  acel.y = (NAO_INICIADO);
  acel.z = (NAO_INICIADO);
  gir.x = (NAO_INICIADO);
  gir.y = (NAO_INICIADO);
  gir.z = (NAO_INICIADO);
}

ImperadorAcelerometro::~ImperadorAcelerometro()
{}


bool ImperadorAcelerometro::iniciar(uint8_t escalaAcelerometro, uint16_t escalaGiroscopio, uint8_t faixaFiltro)
{
  bool retorno = acelerometro.begin();

  if(!retorno)
  {
    Serial.println("Falha ao iniciar acelerômetro.");
    iniciado = false;
    return false;
  }

  iniciado = true;

  delay(500);

  switch (escalaAcelerometro)
  {
    case 2:
      acelerometro.setAccelerometerRange(MPU6050_RANGE_2_G);
      //Serial.println("Acelerômetro configurado para 2G");
      break;
    
    case 4:
      acelerometro.setAccelerometerRange(MPU6050_RANGE_4_G);
      //Serial.println("Acelerômetro configurado para 4G");
      break;
    
    case 8:
      acelerometro.setAccelerometerRange(MPU6050_RANGE_8_G);
      Serial.println("Acelerômetro configurado para 8G");
      break;

    case 16:
      acelerometro.setAccelerometerRange(MPU6050_RANGE_16_G);
      //Serial.println("Acelerômetro configurado para 16G");
      break;
  }

  switch(escalaGiroscopio)
  {
    case 250:
      acelerometro.setGyroRange(MPU6050_RANGE_250_DEG);
      // Giroscópio configurado para escala de 250 graus/s.
      break;

    case 500:
      acelerometro.setGyroRange(MPU6050_RANGE_500_DEG);
      Serial.println("Giroscópio configurado para escala de 500 graus/s.");
      break;

    case 1000:
      acelerometro.setGyroRange(MPU6050_RANGE_1000_DEG);
      // Giroscópio configurado para escala de 1000 graus/s.
      break;

    case 2000:
      acelerometro.setGyroRange(MPU6050_RANGE_2000_DEG);
      // Giroscópio configurado para escala de 2000 graus/s.
      break;
  }

  switch(faixaFiltro)
  {
    case 5:
      acelerometro.setFilterBandwidth(MPU6050_BAND_5_HZ);
      // Filtro de faixa configurado para 5 Hz
      break;

    case 10:
      acelerometro.setFilterBandwidth(MPU6050_BAND_10_HZ);
      // Filtro de faixa configurado para 10 Hz
      break;
    
    case 21:
      acelerometro.setFilterBandwidth(MPU6050_BAND_21_HZ);
      Serial.println("Filtro de faixa configurado para 21 Hz");
      break;

    case 44:
      acelerometro.setFilterBandwidth(MPU6050_BAND_44_HZ);
      // Filtro de faixa configurado para 44 Hz
      break;

    case 94:
      acelerometro.setFilterBandwidth(MPU6050_BAND_94_HZ);
      // Filtro de faixa configurado para 94 Hz
      break;

    case 184:
      acelerometro.setFilterBandwidth(MPU6050_BAND_184_HZ);
      // Filtro de faixa configurado para 184 Hz
      break;

    case 260:
      acelerometro.setFilterBandwidth(MPU6050_BAND_260_HZ);
      // Filtro de faixa configurado para 260 Hz
      break;
  }

  return true;
}

void ImperadorAcelerometro::atualizar()
{
  if(!iniciado) return;

  sensors_event_t aceleracao;
  sensors_event_t giro;
  sensors_event_t temperatura;

  acelerometro.getEvent(&aceleracao, &giro, &temperatura);

  acel.x = aceleracao.acceleration.x;
  acel.y = aceleracao.acceleration.y;
  acel.z - aceleracao.acceleration.z;
  
  gir.x = giro.gyro.x;
  gir.y = giro.gyro.y;
  gir.z = giro.gyro.z;

  temp = temperatura.temperature;
}

Vetor3 ImperadorAcelerometro::get_aceleracao(){return acel;}
Vetor3 ImperadorAcelerometro::get_giro(){return gir;}
float ImperadorAcelerometro::get_temperatura(){return temp;}
bool ImperadorAcelerometro::get_iniciado(){return iniciado;}