/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

/*Sensores*/

#pragma once

//para iniciar la RandomSeed
#define RSeed randomSeed(analogRead(0));

//tipo de motor
enum MotorDriverType : uint8_t {
  DRIVER_PWM_SEPARATE = 0,
  DRIVER_PWM_INTEGRATED = 1
};

//Tipo de Buzzer digital
enum BuzzerType : uint8_t {
	BUZZER_ACTIVE = 0,
	BUZZER_PASSIVE = 1
};

//para los motores que usara
struct Motor{
	uint8_t  L1;
	uint8_t  L2;
	uint8_t  PWM;
};

//para Contener los sensores ultrasonicos
struct UltraSonico{
	uint8_t  Pin[2];//pines
	bool Cerca;//para ver si la distancia de choque se activa
	uint8_t ID;
};

//para Controlar la estancia de un sensor infrarrojo
struct Infrarrojo{
	uint8_t  Pin; //pin
	bool Estado; //para ver si capturo algun valor (0->sin luz, 1->Con luz)
	uint8_t ID;
};

/*
 * Para el seguidor de linea pondremos mas estados para validar correctamente
 * cada sensor
*/
struct IRSeguidorLinea{
	Infrarrojo IR;
	int8_t pesoPotencia; 
};

struct SoundBuzzer {
    uint16_t frecuencia; // Frecuencia en Hz (0 para silencio)
    uint16_t duracion;   // Tiempo en ms
};