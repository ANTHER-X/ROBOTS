//INSECTO

#pragma once

#include <Arduino.h>
#include "Dependencias-Old/Sensores.hpp"


class INSECTO{
	private:
		int V;//velocidad
		//para los motores
		Motor M2Pin[2] = {0};
		Motor M4Pin[4] = {0};
		//para contener los motores
		Motor *Motores[2] = {M2Pin, M4Pin};
		//para ver cual motor se selecciono y la cantidad de motores
		int MtrSelected = -1, CMtrs[2] = {2,4};
		
		void AddMotor(Motor M[], int Cant){
			
			for(int i=0; i<Cant; i++){
				pinMode(M[i].L1, OUTPUT);
				pinMode(M[i].L2, OUTPUT);
				pinMode(M[i].PWM, OUTPUT);
				analogWrite(M[i].PWM, V);
			}
			
		}
		
		//para que los motores anden
		void AccionarMotor(Motor M[], int CMtrs){
			for(int i=0; i<CMtrs; i++){
				digitalWrite(M[i].L1, HIGH);
				digitalWrite(M[i].L2, LOW);
			}
		}
		
	public:
		//constructor, pasamos la velocidad
		INSECTO(int Velocidad){
			V = Velocidad;
		}
		
		//aniade 2 motores
		void Motors_2(Motor M1, Motor M2){
			M2Pin[0] = M1;
			M2Pin[1] = M2;
			
			AddMotor(Motores[0],2);
			
			MtrSelected = 0;
		}
		
		//aniade 4 motores
		void Motors_4(Motor M1, Motor M2, Motor M3, Motor M4){
			M4Pin[0] = M1;
			M4Pin[1] = M2;
			M4Pin[2] = M3;
			M4Pin[3] = M4;
			
			AddMotor(Motores[1],4);
			
			MtrSelected = 1;
		}
		
		void Camina(){
			if(MtrSelected == -1)return;
			AccionarMotor(Motores[MtrSelected], CMtrs[MtrSelected]);
		}
		
};
