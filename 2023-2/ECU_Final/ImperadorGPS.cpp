/*

  GPS_IMPERADOR.cpp - Arquivo para programação da biblioteca do GPS_IMPERADOR.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.
  
*/

#include "ImperadorGPS.hpp"
#include "defines.hpp"

ImperadorGPS::ImperadorGPS(unsigned long br, int8_t rxPin, int8_t txPin):
  velocidade(0.0),
  latitude(0.0),
  longitude(0.0),
  altitude(0.0),
  curso(0.0)
{
  if(rxPin < 0 || txPin < 0)
  {
    Serial.println("Pinos Invalidos ImperadorGPS");
  }
  else
  {
    Serial1.begin(br, SERIAL_8N1, rxPin, txPin);
  }
}

ImperadorGPS::~ImperadorGPS()
{}

void ImperadorGPS::atualizar()
{
  while(Serial1.available())
  {
    char c = Serial1.read();
    gps.encode(c);
  }
  
  if(gps.location.isUpdated())
  {
    latitude = gps.location.lat();
    longitude = gps.location.lng();
    velocidade = gps.speed.kmph();
    altitude = gps.altitude.meters();
    curso = gps.course.deg();
  }
}

double ImperadorGPS::get_velocidade() {return velocidade;}
double ImperadorGPS::get_latitude() {return latitude;}
double ImperadorGPS::get_longitude() {return longitude;}
double ImperadorGPS::get_altitude() {return altitude;}
double ImperadorGPS::get_curso() {return curso;}
