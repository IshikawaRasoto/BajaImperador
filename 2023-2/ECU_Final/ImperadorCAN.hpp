/*
 *
 *	ImperadorCAN.hpp - Biblioteca feita para utilizar o protocolo de comunicação CAN nas ECUs do veículo.
 *
 *	Código escrito pelo Lambari.
 *
 */

#pragma once

#include <Arduino.h>

class ImperadorCAN
{
  private:

    bool iniciado;

	public:

		ImperadorCAN();
		~ImperadorCAN();

    bool iniciar();

		void enviar_rv(int16_t rpm, int8_t velocidade);
    void enviar_btb(float tensao_bateria, double valor_temperatura, bool box);
		String receber();

    bool get_iniciado();
};
