//SEGUIDOR DE LINEA

#pragma once

#include <Arduino.h>
#include "Dependencias-Old/Sensores.hpp"

class SEGUIDORLINEA{
	private:
		
		Motor Motores[2] = {0};
		int Sir[3] = {0};
		int V, DurReco, Giro, Accionados[2] = {0};
		
		//para caminar
		void GiroDerIzq(bool Der){//metemos un bool para cambiar la direccion
			
			for(int i=0; i<2; i++){
				//ve cual de las direcciones es, (true->adelante, false->atras)
				digitalWrite(Motores[i].L1, Der ? HIGH : LOW);
				digitalWrite(Motores[i].L2, Der ? LOW : HIGH);
				//cambia el estado del bool
				Der = Der ? false : true;
			}
			delay(Giro);
		}
		
		void Recto(){
			//camina hacia adelante
			for(int i=0; i<2; i++){
				digitalWrite(Motores[i].L1, HIGH);
				digitalWrite(Motores[i].L1, LOW);
			}
			delay(DurReco);
		}
		
	public:
		SEGUIDORLINEA(int Velocidad, int Drec, int TGiro){
			V = Velocidad;
			DurReco = Drec;
			Giro = TGiro;
		}
		
		void SetSir(int IF_Izq, int IF_Center, int IF_Der){
			Sir[0] = IF_Izq;
			Sir[1] = IF_Center;
			Sir[2] = IF_Der;
			
			for(int i=0; i<3; i++){
				pinMode(Sir[i], INPUT);
			}
			Accionados[0] = 1;
		}
		
		void SetMotor(Motor M1, Motor M2){
			Motores[0] = M1; 
			Motores[1] = M2; 
			
			for(int i=0; i<2; i++){
				pinMode(Motores[i].L1, OUTPUT);
				pinMode(Motores[i].L2, OUTPUT);
				pinMode(Motores[i].PWM, OUTPUT);
			}
			
			analogWrite(Motores[0].PWM, V);
			analogWrite(Motores[1].PWM, V);
			
		}
		
		void Camina(){
			//si no a iniciado nada
			if(Accionados[0] == 0 && Accionados[1] == 0) return;
			
			/*izquierda*/
			if(digitalRead(Sir[0]) == LOW){	GiroDerIzq(false);	}
			//hacia adelante
			if(digitalRead(Sir[1]) == LOW){	Recto();			}
			//derecha
			if(digitalRead(Sir[2]) == LOW){	GiroDerIzq(true);	}
			
		}
		
};
