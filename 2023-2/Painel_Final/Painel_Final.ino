/*

  Painel - Arquivo únificado para recebimento de dados pela CAN, e envio dos mesmos pela Serial para o display.
  Tratamento de Velocidade e RPM recebidos.
  Criado em 20/10/2020 por Rossi para implementação no J12 até novembro de 2023 e servi como base para o J13.  

*/

#include <CAN.h>

#define TX_GPIO_NUM   5  // Conecta no CTX
#define RX_GPIO_NUM   18  // Conecta no CRX


#define RXPIN 16
#define TXPIN 17
#define EA1 26

char dataRecebida [9];
int RPM;
int VEL;

String temp_string = "";
int temperatura = 0;

String bat_string = "";
float tensao_bateria = 0.0;

char box_char;
bool box = false;;


long timer;


void setup() {
//
//
  Serial.begin(115200);
  Serial.println("Comecando: ");

  pinMode(RXPIN, INPUT);
  pinMode(TXPIN, OUTPUT);

  Serial1.begin(115200, SERIAL_8N1, RXPIN, TXPIN);
//
//
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);

  if (!CAN.begin (500E3)) {
    Serial.println ("Inicialização da CAN falhou.");
    while (1);
  }
  else {
    Serial.println ("CAN Iniciada");
  }

//
//
  delay(500);

}

void loop() {
  

  Envio_para_display();
  canReceiver();


}

void Envio_para_display(){
    if(millis()-timer>100)
  {
  

    sendInt(RPM);
    sendFloat(VEL);

    timer = millis();
  }
}

void sendInt(int numberToSend){

  Serial1.write(0x5A); 
  Serial1.write(0xA5); 
  Serial1.write(2+1+2); 
  Serial1.write(0x82);
  Serial1.write(0x10);
  Serial1.write((byte)0x00); 
  Serial1.write(highByte(numberToSend)); 
  Serial1.write(lowByte(numberToSend)); 
  

}


void sendFloat(float Value){

  Serial1.write(0x5A); 
  Serial1.write(0xA5); 
  Serial1.write(0X07); 
  Serial1.write(0x82);
  Serial1.write(0x11);
  Serial1.write((byte)0x00); 

  byte hex [4] = {0};

  FloatToHex(Value, hex);

  Serial1.write(hex[3]); 
  Serial1.write(hex[2]); 
  Serial1.write(hex[1]); 
  Serial1.write(hex[0]);

}

void FloatToHex(float f, byte*hex)
{
  byte* f_byte = reinterpret_cast<byte*>(&f);
  memcpy(hex, f_byte,4);
}


void canReceiver() {

  int i;
  int packetSize = CAN.parsePacket();

  if (packetSize) {

    Serial.print ("Received ");
  
    if (CAN.packetExtended()) {
      Serial.print ("extended ");
    }

    if (CAN.packetRtr()) {

      Serial.print ("RTR ");
    }

    Serial.print ("packet with id 0x");
    Serial.print (CAN.packetId(), HEX);

    if (CAN.packetRtr()) {
      Serial.print (" and requested length ");
      Serial.println (CAN.packetDlc());
    } else {
      Serial.print (" and length ");
      Serial.println (packetSize);


      while (CAN.available()) {
        dataRecebida[i] = ((char)CAN.read());
        Serial.print ("CAN: ");
        Serial.println(dataRecebida[i]);
        i++;
      }
      i = 0;
      if (dataRecebida[0] == 'R' && dataRecebida[5] == 'V'){
        RPM = atoi(dataRecebida + 1);
        VEL = atoi(dataRecebida + 6);
      }
      else if(dataRecebida[0] == 'C')
      {
        bat_string.concat(dataRecebida[1]);
        bat_string.concat(dataRecebida[2]);
        bat_string.concat(dataRecebida[3]);

        tensao_bateria = (bat_string.toInt()) / 10.0;

        temp_string.concat(dataRecebida[4]);
        temp_string.concat(dataRecebida[5]);
        temp_string.concat(dataRecebida[6]);

        temperatura = temp_string.toInt();

        box_char = dataRecebida[7];

        box_char == '1' ? box = true : box = false;
      }
      Serial.println();
    }
    Serial.println();
  }

}

