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
	public:

		Imperador_CAN();
		~Imperador_CAN();

		void enviar(String s);
		String verificar();
};
