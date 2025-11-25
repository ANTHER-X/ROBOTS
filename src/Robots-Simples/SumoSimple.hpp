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

/*
//Esta estructura me dara un control para hacer que la funcion de busqueda este separada del resto, no usada.
struct SensoresBusquedaSimpleSumo{
	Infrarrojo *infDelante;
	Infrarrojo *infAtras;
	Infrarrojo *infIzquierda;
	Infrarrojo *infDerecha;

	UltraSonico *susDelante;
	UltraSonico *susAtras;
	UltraSonico *susIzqueirda;
	UltraSonico *susDerecha;
};
*/

class SumoSimple : public SumoBase{

    protected:

	virtual void SimpleAccion(bool &accion, unsigned long &Time);

	//Nothing :/
	virtual void Extras() override{}
	
	virtual void MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &atUsed, bool &usUsed) override;

	virtual void MoverPorInfrarrojos(unsigned long &timer, bool &used) override;

	//Nothing :/
	virtual void FinAtaque(bool &ataque, bool &infAccion, unsigned long timeInfAccion, unsigned long timeAtaque) override{
		
	}
	virtual void Ataque(bool &ataque, bool &infUsed, unsigned long &timeAtaque, unsigned long &timeInf) override{
		
	}/*
	virtual  override{
		
	}*/

    public:
		SumoSimple(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t _DistAtaq, unsigned int TRecMiliSec, unsigned int TGiroMiliSec);

		//Para agregas mas sensores, recuerda que ya tenemos los INF y SUS de adelante heredados
		virtual void AddInfraAtras(uint8_t pin)     { AddInfra(1,pin);}
		virtual void AddInfraIzquierda(uint8_t pin) { AddInfra(2,pin);}
		virtual void AddInfraDerecha(uint8_t pin)   { AddInfra(3,pin);}
        
		virtual void AddSUSAtras(uint8_t triger, uint8_t echo)      { AddSUS(1, triger, echo);}
		virtual void AddSUSIzquierda(uint8_t triger, uint8_t echo)  { AddSUS(2, triger, echo);}
		virtual void AddSUSDerecha(uint8_t triger, uint8_t echo)    { AddSUS(3, triger, echo);}

		/*Metodos para agregar los motores, Recuerda que ya heredamos Add2Motors.
		AddMotors es para que inserte la cantidad de motores que decee*/
		virtual void AddMotors(std::vector<Motor> Mtrs);

		//Para agregar 4 motores o mas, le decimos el orden ->IZQ->DER->IZQ->DER
		virtual void Add4Motors(Motor izq1, Motor der1, Motor izq2, Motor der2);

};