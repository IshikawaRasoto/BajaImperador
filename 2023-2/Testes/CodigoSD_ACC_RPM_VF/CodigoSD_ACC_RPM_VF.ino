/*
	Código para aquisição de dados nos testes de ACC, RPM e VF.
*/

#include <Wire.h>
#include <MPU6050_light.h>
#include <SD.h>
#include <SPI.h>

// Pinos

#define PIN_RPM_M 3
#define PIN_VELOCIDADE 2

// Constantes 

#define GRAVIDADE 9.81

#define CONST_PI 3.14159
#define DIAMETRO 0.51916
#define COMPRIMENTO CONST_PI * DIAMETRO

#define TAXA_ATUALIZACAO 1000/15


#define BAUDRATE 115200

const char tab = 9;
const char pv = 59;


// variaveis globais

volatile unsigned long aux;
volatile unsigned long tempoRPM;
volatile unsigned long tempoVelocidade;
volatile unsigned long tempoCalculo;

unsigned long timer = 0;

volatile uint16_t rpm = 0;
volatile float velocidade = 0;

unsigned short int contadorLora = 0;
String texto = "";
String textoLora = "";

File arquivo;
String diretorio = "";

int testeAtual = 1;

MPU6050 mpu(Wire);

bool statusMpu = false;
bool statusSD = false;



void interrupcaoRPM()
{
	aux = millis();
	rpm = int(60000/(aux - tempoRPM));
	tempoRPM = aux;
}

void interrupcaoVelocidade()
{
	aux = millis();
	velocidade = COMPRIMENTO * (1000/7.0) * 3.6 / (aux - tempoVelocidade);
	tempoVelocidade = aux;
}

void inicializacao_mpu()
{

  Wire.begin();
  
  Serial.println("PRETESTE");
	byte status = mpu.begin();
  Serial.println("TESTE");
	if(status!=0)
	{
		Serial.print("Falha ao iniciar o Acelerômetro, status: ");
		Serial.println(status);
		return;
	}

  statusMpu = true;

	Serial.println(F("Calculando Offsets, não mova o MPU6050"));
	delay(1000);
	mpu.calcOffsets(true, true);
	Serial.println("Calculado");
}


void inicializacaoSD()
{
	
	if(!SD.begin())
	{
		Serial.println("Falha ao iniciar SD");
    return;
	}

  statusSD = true;
	
	diretorio = "testes.txt";

	if(!SD.exists(diretorio)) //Se não existir o arquivo de controle dos testes
	{ 
    Serial.println("Criando Diretório testes.txt");
		arquivo = SD.open(diretorio, FILE_WRITE);
    arquivo.close();
	}

  

	arquivo = SD.open(diretorio, FILE_READ);

	
	String numeroTeste = "";
	
	//int ultimoTeste = 0;

  Serial.println("Lendo Testes");

	while(arquivo.available())
	{
		
		char numero = arquivo.read();

    Serial.println(numero);

    
	}
	
	arquivo.close(); 

	arquivo = SD.open(diretorio, FILE_WRITE);
  
  Serial.print("Teste Atual: ");
  Serial.println(testeAtual);

	arquivo.print(testeAtual);
	arquivo.close();

	diretorio = "teste" + String(testeAtual) + ".csv";

	Serial.print("Criando o diretorio: ");
	Serial.println(diretorio);

	arquivo = SD.open(diretorio, FILE_WRITE);
  arquivo.close();
	
}


void salvarDadosSD(String dados)
{

	arquivo = SD.open(diretorio, FILE_WRITE);
	
	arquivo.print(dados);

	arquivo.close();
}

void setup()
{
	delay(500);

	Serial.begin(BAUDRATE);

  Serial.println("Inicializando MPU");

	//inicializacao_mpu();

  Serial.println("Inicializando SD");

  inicializacaoSD();

	tempoRPM = millis();
	tempoVelocidade = millis();
	tempoCalculo = millis();

	attachInterrupt(digitalPinToInterrupt(PIN_RPM_M), interrupcaoRPM, RISING);
	attachInterrupt(digitalPinToInterrupt(PIN_VELOCIDADE), interrupcaoVelocidade, RISING);
}

void loop()
{
  if(statusMpu)
	  mpu.update();

	long delta = millis() - timer;

	if(delta > TAXA_ATUALIZACAO)
	{

		// Formato String: Velocidade RPM ACCX ACCY ACCZ ANGX ANGY ANGZ
		// Cada item é separado por um tab
		contadorLora++;

		texto = "";

		texto += String(velocidade, 2) + String(pv) + String(rpm);

    if(statusMpu)
    {
      texto += String(pv);
      texto += String(mpu.getAccX() * GRAVIDADE, 2) + String(pv);
      texto += String(mpu.getAccY() * GRAVIDADE, 2) + String(pv);
      texto += String(mpu.getAccZ() * GRAVIDADE, 2) + String(pv);
      
      texto += String(mpu.getAngleX()) + String(pv);
      texto += String(mpu.getAngleY()) + String(pv);
      texto += String(mpu.getAngleY()) + "\n";
    }
    else
    {
      texto += "\n";
    }

		
    if(statusSD)
		  salvarDadosSD(texto);

		if(contadorLora == 15)
		{
			contadorLora = 0;

      textoLora = "";
      textoLora += String(velocidade, 2) + String(tab) + String(rpm);

      if(statusMpu)
      {
        textoLora += String(tab);
        textoLora += String(mpu.getAccX() * GRAVIDADE, 2) + String(tab);
        textoLora += String(mpu.getAccY() * GRAVIDADE, 2) + String(tab);
        textoLora += String(mpu.getAccZ() * GRAVIDADE, 2) + String(tab);
        
        textoLora += String(mpu.getAngleX()) + String(tab);
        textoLora += String(mpu.getAngleY()) + String(tab);
        textoLora += String(mpu.getAngleY()) + "\n";
      }
      else
      {
        textoLora += "\n";
      }
      
      Serial.print(textoLora);
      
		}

    timer = millis();
	}

}



