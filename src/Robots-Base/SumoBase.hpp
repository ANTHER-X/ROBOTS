/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/


#include <Arduino.h>
#include "Robot.hpp"


#pragma once

/*
Sumo Base, es el mas simple, solo es para ejemplo pero si alguien gusta, podria usarlo.
De este se desprende el resto de sumos, el simple toma este y le agrega un par de cositas mas,
sencillas pero ya funcionales para probar con algun proyecto
*/
class SumoBase : public Robot{

    protected:
        
        //Sensores basico
        UltraSonico UltraSonicos[MAXSUS];
		uint8_t UltraSonicoCount = 0;
        
		#if USE_IR == 1
			Infrarrojo Infrarrojos[MAXIR];
			uint8_t InfrarrojoCount = 0;
		#endif

        //unidades de medicion basicos
        uint8_t DistAtaq;
        unsigned int Distcm, TRec, TGiro;
		uint8_t VelGiro;
        bool RGiro; //este es para que gire aleatoriamente

        //metodos privados
        //captura la distancia en CM
		void MedirSUS(UltraSonico &US);
		int TomarDistUS(UltraSonico &US);
		void UsarAllSUS();

		//Para sensores Infrarrojos
		//toma el estado de los infrarrojos
		void ActivaInfrarrojo(Infrarrojo &INF);
		bool UsaInfrarrojo(Infrarrojo &INF);
		void UsaAllInfrarrojo();


		virtual void Extras(){}

		virtual void MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed);
		virtual void MoverPorInfrarrojos(unsigned long &timer, bool &used);

		virtual void FinAtaque(bool &ataque, bool &infAccion, unsigned long timeInfAccion, unsigned long timeAtaque);

		virtual void Ataque(bool &ataque, bool &infUsed, unsigned long &timeAtaque, unsigned long &timeInf);

		//Define los infrarrojos
		void AddInfra(uint8_t id, uint8_t pin);
		//Los Ultrasonicos para los ojos
		void AddSUS(uint8_t id, uint8_t triger, uint8_t echo);
		
		virtual bool ExistIR(int ID);
		virtual bool ExistSUS(int ID);

    public:
        SumoBase(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec, unsigned int TGiroMiliSec, MotorDriverType typeMotor);

		virtual void AddInfraAdelante(uint8_t pin);

		virtual void AddSUSAdelante(uint8_t triger, uint8_t echo);

		virtual void Add2Motors(Motor L1, Motor L2);

        virtual void Camina(unsigned int TimeMinuts = 0) override;
};