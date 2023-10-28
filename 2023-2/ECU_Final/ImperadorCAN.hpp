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

		void enviar(int8_t velocidade, uint16_t rpm, bool alarme_bateria, bool alarme_temperatura, bool box);
		String receber();
};