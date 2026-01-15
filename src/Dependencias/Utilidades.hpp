#include "Sensores.hpp"
#include "../Config.hpp"

#pragma once

//Tomamos esta funcion, la usaremos para leer y capturar la distancia de los sensores Ultrasonicos
unsigned int ActivateUS(UltraSonico US){
	digitalWrite(US.Pin[0], HIGH); //mando una senial de sonido
  delayMicroseconds(10);
  digitalWrite(US.Pin[0], LOW); //detengo la senial

  unsigned int DistanceCM = (pulseIn(US.Pin[1], HIGH) / 58.2);

  DBG_VALUE_LN("Distancia en CM tomada: ", DistanceCM);
	return DistanceCM;//medira en centimetros
}