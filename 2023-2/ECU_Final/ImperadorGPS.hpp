
/* GPS_IMPERADOR.hpp - Arquivo para declaração da biblioteca do GPS_IMPERADOR. 
 * Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13. 
 * Esta biblioteca possui o código Orientada a Objetos. Essa biblioteca utiliza como padrão o Serial1 para comunicação com o módulo
 */

#pragma once

#include <Arduino.h>
#include <TinyGPSPlus.h>

class ImperadorGPS
{

  private:

    TinyGPSPlus gps;
    double velocidade;
    double latitude;
    double longitude;
    double altitude;
    double curso;

  public:

    ImperadorGPS(unsigned long br, int8_t rxPin = -1, int8_t txPin = -1);
    ~ImperadorGPS();

    void atualizar();
    
    double get_velocidade();
    double get_latitude();
    double get_longitude();
    double get_altitude();
    double get_curso();
};
