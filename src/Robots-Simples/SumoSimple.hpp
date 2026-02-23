/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

//Incluimos el Sumo base y creamos a partir de este
#include "../Robots-Base/SumoBase.hpp"

#pragma once

/*
Aqui ya vemos que, aunque hay listas dinamicas, tenemos una cantidad fija de sensores, aunque eso si,
los motores pueden ser cuantos sean siempre y cuando lleven la jerarquia de, primero izqueirda luego derecha,
recomendable minimo 2.

Aqui la estructura de sensores es asi:
0; Adelante
1; Atras
2; Izquierda
3; Derecha
*/

class SumoSimple : public SumoBase{

    protected:

		virtual void SimpleAccion(bool &accion, unsigned long &Time);

		//Nothing :/
		inline virtual void Extras() override{}
		
		virtual void MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed) override;

		virtual void MoverPorInfrarrojos(unsigned long &timer, bool &used) override;

		/*
		virtual  override{
			
		}*/

    public:
		SumoSimple(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq,
			unsigned int TRecMiliSec, unsigned int TGiroMiliSec, MotorDriverType typeMotor);

		//Para agregas mas sensores, recuerda que ya tenemos los INF y SUS de adelante heredados
		virtual void AddInfraAtras(uint8_t pin)     { AddInfra(1,pin);}
		virtual void AddInfraIzquierda(uint8_t pin) { AddInfra(2,pin);}
		virtual void AddInfraDerecha(uint8_t pin)   { AddInfra(3,pin);}
        
		virtual void AddSUSAtras(uint8_t triger, uint8_t echo)      { AddSUS(1, triger, echo);}
		virtual void AddSUSIzquierda(uint8_t triger, uint8_t echo)  { AddSUS(2, triger, echo);}
		virtual void AddSUSDerecha(uint8_t triger, uint8_t echo)    { AddSUS(3, triger, echo);}

		//Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER
		virtual void Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2);

};