/*Base Class*/
#pragma once
#include "Dependencias-Old/Sensores.hpp"

class Robot{
	protected:
		//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
		virtual void MDelAtrs(Motor M[], int CantMotors, bool delante, int R){
			
			for(int i=0; i<CantMotors; i++){
				digitalWrite(M[i].L1, (delante ? HIGH : LOW));
				digitalWrite(M[i].L2, (delante ? LOW : HIGH));
			}
			delay(R);
		}
		
		//si usa true va hacia la derecha, si usa false, hacia la izquierda
		//deberia funcionar para motores pares en lineas de 2
		virtual void MDerIzq(Motor M[], int CantMotors, bool Der, int giro){
      		
			for(int i=0; i<CantMotors; i++){
				digitalWrite(M[i].L1, Der ? HIGH : LOW);
				digitalWrite(M[i].L2, Der ? LOW : HIGH);
				Der = Der ? false : true;//cambia de direccion del siguiente motor (es el de al lado por lo que guirara)
			}
			delay(giro);
			
		}
		
		virtual void Stop(Motor M[], int CMotor){
			
			for(int i=0; i<CMotor; i++){
				digitalWrite(M[i].L1, LOW);
				digitalWrite(M[i].L2, LOW);
			}
			
		}
		
		//Para definir los motores
		virtual void AddMotor(Motor M[], int Cant, int Vel){
			//Le damos un modo al pines
			for(int i=0; i<Cant; i++){
				pinMode(M[i].L1, OUTPUT);
				pinMode(M[i].L2, OUTPUT);
				//SetSpeed de los motores, si el pin es real, aplicamos la Vel, si no... pues no
				if(M[i].PWM > 0){
					pinMode(M[i].PWM, OUTPUT);
					Serial.println("Agregando Velocidad" + Vel);
					 analogWrite(M[i].PWM, Vel);
				}
				Serial.println("Motor seteado");
			}
		}
	
};
