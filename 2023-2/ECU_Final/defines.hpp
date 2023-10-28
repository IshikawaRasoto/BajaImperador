/*

  defines.hpp - Arquivo para declaração das macros do projeto.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/

#pragma once

// Macros Medições

#define CONST_PI 3.14159
#define DIAMETRO 0.51916 // Diâmetro da roda em metros
#define COMPRIMENTO CONST_PI * DIAMETRO


#define LIMIAR_BATERIA  3600 // 4095 (Escala Maxima) * (2,9V/3,3V)
#define BATERIA_ZERO    3542 // 4095 * (2,855V (11,8V Bateria Descarregada)/3,3V) 
#define BATERIA_CHEIA   3847 // 4095 * (3,085V (12,8V da bateria) / 3,3V)

#define AVISO_BATERIA 12.0 // tensão da bateria para dar o aviso
#define AVISO_TEMPERATURA 75 // Temperatura ºC para dar o aviso.

// Macros dos dentes

#define DESTES_RODAD 4
#define DENTES_RODAE 4
#define DENTES_EIXOT 1


// Macros Pinos

#define PINO_RODAD 18 //
#define PINO_RODAE 34 //
#define PINO_EIXOT 35 // 
#define PINO_RPM   19 //

#define RX_GPS 25 //
#define TX_GPS 26 //

#define PINO_BATERIA 27 //
#define PINO_FREIO   32 //
#define PINO_DIF     33

#define TX_LORA 17
#define RX_LORA 16

#define RX_CAN 4
#define TX_CAN 2

//#define SCL 22 //
//#define SDA 21 //

#define SD_MISO 12
#define SD_MOSI 13
#define SD_CLK  14
#define SD_CS   15

#define TERMO_MISO  19
#define TERMO_MOSI  23
#define TERMO_CLK   18
#define TERMO_CS    5


// Macros BaudRates

#define BAUD_SERIAL 115200
#define BAUD_GPS    9600
#define BAUD_LORA   115200