/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/


#include <Arduino.h>
#include <Robots-Base/Robot.hpp>
#include <modules/SoundSystem.hpp>


#ifndef SUMO_HPP
#define SUMO_HPP

class Sumo : public Robot{
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

	// Indices de melodias.	0=Ataque, 1=retroceso, 2=salida de domo
	uint8_t MusicIndex[3] = {0};
	SoundSystem* Sound = nullptr;

	void GetIndexSound(const Nota* const* melody, uint8_t index){ if(Sound != nullptr) MusicIndex[index] = Sound->GetIndexMusic(melody); }

	//metodos privados
	//captura la distancia en CM
	void MedirSUS(UltraSonico &US);
	int TomarDistUS(UltraSonico &US);
	void UsarAllSUS();

	//Para sensores Infrarrojos
	//toma el estado de los infrarrojos
	void ActivaIR(Infrarrojo &IR);
	bool UsaIR(Infrarrojo &IR);
	void UsaAllIR();

	virtual void Extras(){}

	virtual void MoverPorSUS(unsigned long &timer,unsigned long &timerUS, bool &usUsed);
	virtual void MoverPorIR(unsigned long &timer, bool &used, unsigned long timerIR_Uso);
	
	virtual bool ExistSUS(int16_t angle);
	virtual bool ExistIR(int16_t angle);
public:
	Sumo(uint8_t Velocidad, uint8_t VelocidadGiro, uint8_t DistAtaqCM, uint16_t DiametroCM, uint16_t Vel_CMS, unsigned int TRecRect, MotorDriverType typeMotor);

	//Define los infrarrojos
	void AddIR(int16_t angle, uint8_t pin);
	//Los Ultrasonicos para los ojos
	void AddSUS(int16_t angle, uint8_t triger, uint8_t echo);

	// Sonido
	inline void AddSoundSystem(SoundSystem* soundSystem){Sound = soundSystem; }
	void SetAtackSound(const Nota* const* melody){GetIndexSound(melody, 0); }
	void SetBackSound(const Nota* const* melody){GetIndexSound(melody, 1); }
	void SetIRSound(const Nota* const* melody){GetIndexSound(melody, 2); }


	virtual void Camina(unsigned int TimeMinuts = 0) override;
};

#endif // SUMO_HPP