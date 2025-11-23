/*Sensores*/

#pragma once

//para iniciar la RandomSeed
#define RSeed randomSeed(analogRead(0));

//para los motores que usara
struct Motor{
	int L1;
	int L2;
	int PWM;
};

//para Contener los sensores ultrasonicos
struct UltraSonico{
	int Pin[2];//pines
	bool Activo;//verifica si se usa (incluimos varios en varias pociciones)
	bool Cerca;//para ver si la distancia de choque se activa
	bool Lejos;
};