/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#pragma once

//para iniciar la RandomSeed
#define RSeed randomSeed(analogRead(0));


/*###### MOTORES ######*/
enum MotorDriverType : uint8_t {
  DRIVER_PWM_SEPARATE = 0,
  DRIVER_PWM_INTEGRATED = 1,
  NO_SETTER_SPEED = 2
};

//para los motores que usara
struct Motor{
	uint8_t  L1;
	uint8_t  L2;
	uint8_t  PWM;
};



/*###### Sensores ######*/
//para Contener los sensores ultrasonicos
struct UltraSonico{
	uint8_t Pin[2];//pines
	bool Cerca;//para ver si la distancia de choque se activa
	int16_t angle; // Angulo en grados
};

//para Controlar la estancia de un sensor infrarrojo
struct Infrarrojo{
	uint8_t  Pin; //pin
	bool Estado; //para ver si capturo algun valor (0->sin luz, 1->Con luz)
	int16_t angle;
};

// Para el seguidor de linea pondremos un peso
struct IRSeguidorLinea{
	Infrarrojo IR;
	int8_t pesoPotencia; 
};



/*###### SONIDO ######*/

enum NotesStorage : uint8_t{
	NOTES_RAM = 0,
	NOTES_FLASH = 1
};

// Notas de sonido
struct Nota {
    uint16_t frecuencia; // Frecuencia en Hz (0 para silencio)
    uint16_t duracion;   // Tiempo en ms
};

// Tipo de Buzzer
enum BuzzerType : uint8_t {
	BUZZER_ACTIVE = 0,
	BUZZER_PASSIVE = 1
};