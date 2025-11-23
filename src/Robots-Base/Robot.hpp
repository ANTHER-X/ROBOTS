/*Base Class*/

#include <Arduino.h>
#include <ArduinoSTL.h>

#pragma once
#include "../Dependencias/Sensores.hpp"

class Robot{
	protected:
	
		//Motores
        std::vector<Motor> Motores;

		//Para variar la velocidad de los motores
		virtual void ConfigVelocidad(std::vector<Motor> &M, uint8_t vel);

		//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
		virtual void MDelAtrs(std::vector<Motor> &M, bool delante);
		
		//si usa true va hacia la derecha, si usa false, hacia la izquierda
		//deberia funcionar para motores pares en lineas de 2
		virtual void MDerIzq(std::vector<Motor> &M, bool Der);
		
		virtual void MStop(std::vector<Motor>& M);
		
		//Para definir los motores
		virtual void SetMotor(Motor &M, uint8_t Vel);

		//Quiza agregre algo... Quiza.
		virtual void Camina(unsigned int TimeMinuts = -1){}
};
