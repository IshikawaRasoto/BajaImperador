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

		void enviar(String s);
		String verificar();
};
