/*

  SD_IMPERADOR.hpp - Arquivo para programação da biblioteca SD_IMPERADOR.
  Criado em 14/07/2023 pelo Lambari para implementar no J12 até novembro e servir como base para o J13.

*/
#include "ImperadorSD.hpp"
ImperadorSD::ImperadorSD(){}

ImperadorSD::~ImperadorSD(){}

bool ImperadorSD::iniciar(int CS)
{
  bool iniciou = SD.begin(CS);
  if(!iniciou)
  {
    iniciado = false;
    Serial.println("FALHA AO INICIAR SD");
    return false;
  }

  iniciado = true;
  Serial.println("SD OK");
  return true;
}

void ImperadorSD::escrever(const char* path, const char* mensagem)
{

  if(!iniciado) return;

  arquivo = SD.open(path, FILE_WRITE);

  if(arquivo)
  {
    arquivo.println(mensagem);
    arquivo.close();
  }

}

void ImperadorSD::ler(const char* path)
{
  if(!iniciado) return;

  arquivo = SD.open(path);
  if(arquivo)
  {
    while(arquivo.available())
    {
      Serial.write(arquivo.read());
    }
    arquivo.close();
  }
}

bool ImperadorSD::get_iniciado(){return iniciado;}