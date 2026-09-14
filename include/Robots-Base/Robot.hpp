/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

/*Base Class*/
#include <Arduino.h>
#include "../Config.hpp"
#include "../Dependencias/Sensores.hpp"

#pragma once

class Robot{
	protected:
	
		//Motores
        Motor* Motores[MAXMOTORS];
		uint8_t CantidadMotores = 0;
		uint8_t Vel;
		MotorDriverType motorType;

		//Para variar la velocidad de los motores
		void ConfigVelocidad(Motor M[], uint8_t size, uint8_t vel);

		//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
		virtual void MDelAtrs(Motor* M, uint8_t size, bool delante);
		
		//si usa true va hacia la derecha, si usa false, hacia la izquierda
		//deberia funcionar para motores pares en lineas de 2
		virtual void MDerIzq(Motor* M, uint8_t size, bool Der);
		
		virtual void MStop(Motor* M, uint8_t size);
		
		//Para definir los motores
		void SetMotor(Motor* M, uint8_t vel);
	public:
		inline Robot(){};
		inline Robot(uint8_t vel, MotorDriverType mType): Vel(vel), motorType(mType){}
		//Quiza agregre algo... Quiza.
		//Si lees esto quiere decir que si agrege al menos un metodo... Que mal.
		inline virtual void Camina(unsigned int activeTimeMillis = 0){ 
			DBG_PRINTLN("Caminando...");
			ConfigVelocidad(*Motores, CantidadMotores, Vel);
			MDelAtrs(*Motores, CantidadMotores, true);
			delayMicroseconds(1000);

			DBG_PRINTLN("Moviendo hacia atras");
			MDelAtrs(*Motores, CantidadMotores, false);
			delayMicroseconds(1000);
			
			DBG_PRINTLN("Moviendo hacia la derecha");
			MDerIzq(*Motores, CantidadMotores, true);
			delayMicroseconds(1000);
			
			DBG_PRINTLN("Moviendo hacia la izquierda");
			MDerIzq(*Motores, CantidadMotores, false);
			delayMicroseconds(1000);

		 }
		virtual void AddMotors(Motor* Mtrs, uint8_t size);
};
