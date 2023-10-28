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

void ImperadorCAN::enviar_rv(uint16_t rpm, int8_t velocidade)
{
    CAN.beginPacket(0x12);
    
    char rpm_char [10];
    char velocidade_char[5];

    itoa(rpm, rpm_char, 10);
    itoa(velocidade, velocidade_char, 10);

    for(int i = 0; i < 4; i++)
    {
        CAN.write(rpm_char[i]);
    }

    for(int i = 0; i < 2; i++)
    {
        CAN.write(velocidade_char[i]);
    }

    CAN.endPacket();
}


void ImperadorCAN::enviar_btb(float tensao_bateria, double valor_temperatura, bool box)
{
    CAN.beginPacket(0x12);
    
    char bateria_char[10];
    char temperatura_char[10];
    char box_char;

    int8_t bateria_int = int8_t(tensao_bateria * 10);
    int8_t temperatura_int = int8_t(valor_temperatura);

    itoa(bateria_int, bateria_char, 10);
    itoa(temperatura_int, temperatura_char, 10);

    for (int i = 0; i < 3; i++)
    {
        CAN.write(bateria_char[i]);           
    }    

    for(int i = 0; i < 3; i++)
    {
        CAN.write(temperatura_char[i]);
    }


    box ? box_char = '1' : box_char = '0';

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
