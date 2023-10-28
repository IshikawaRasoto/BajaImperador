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
	public:

		ImperadorCAN();
		~ImperadorCAN();

		void enviar_rv(uint16_t rpm, int8_t velocidade);
    	void enviar_btb(float tensao_bateria, double valor_temperatura, bool box);
		String receber();
};
