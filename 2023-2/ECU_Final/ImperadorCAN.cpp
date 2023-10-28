/*
 *
 * ImperadorCAN.cpp
 *
 */

#include "defines.hpp"
#include "ImperadorCAN.hpp"
#include <CAN.h>

ImperadorCAN::ImperadorCAN()
{
    CAN.setPins(RX_CAN, TX_CAN);
    if(!CAN.begin(500E3)) Serial.println("CAN Falhou para inciar");
}

ImperadorCAN::~ImperadorCAN(){}

void ImperadorCAN::enviar(int8_t velocidade, uint16_t rpm, bool alarme_bateria, bool alarme_temperatura, bool box)
{
    CAN.beginPacket(0x12);

    char rpm_char [5];
    char velocidade_char[5];
    char bateria_char;
    char temperatura_char;
    char box_char;

    itoa(rpm/100, rpm_char, 10);
    itoa(velocidade, velocidade_char, 10);

    alarme_bateria ? bateria_char = '1' : bateria_char = '0';
    alarme_temperatura ? temperatura_char = '1' : temperatura_char = '0';
    box ? box_char = '1' : box_char = '0';

    for(int i = 0; i < 2; i++)
    {
        CAN.write(rpm_char[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        CAN.write(velocidade_char[i]);
    }

    CAN.write(bateria_char);
    CAN.write(temperatura_char);
    CAN.write(box_char);

    CAN.endPacket();
}

String ImperadorCAN::receber()
{
    String retorno;

    while(CAN.available())
    {
        retorno.concat(CAN.read());
    }

    return retorno;
}