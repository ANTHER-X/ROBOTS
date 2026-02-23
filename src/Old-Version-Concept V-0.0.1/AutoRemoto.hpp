/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

//Un Carrito

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Servo.h>
#include "Dependencias-Old/Sensores.hpp"
#include "Robot.hpp"

class AutoRemoto : protected Robot{
	private:
		
		Motor Motors[4];
		SoftwareSerial BTH;
		
		int PinServo;
		/*En caso de que de problema el usar solo el pin
		Servo servo;*/
		
		bool X4;
		bool giro = false;
		
		void MoverGrados(int angle){
			int pulso = map(angle, 0, 180, 1000, 2000);
		
			for (int i = 0; i < 50; i++) {
			    digitalWrite(PinServo, HIGH);
			    delayMicroseconds(pulso);
			    digitalWrite(PinServo, LOW);
				delay(20 - pulso / 1000);
			}
		}
		
		void MoveBTH(char del, char atr, char der, char izq, char det){
			
			if(BTH.available()){
				
				char Tecla = BTH.read();
				
				if(Tecla == del){	MDelAtrs(Motors, (X4? (4):(2)), true, 0);	}
				if(Tecla == atr){	MDelAtrs(Motors, (X4? (4):(2)), false, 0);	}
				if(Tecla == der){	MoverGrados(180);/*servo.write(180);*/				}
				if(Tecla == izq){	MoverGrados(0);/*servo.write(0);*/				}
				if(Tecla == det){	Stop(Motors, (X4? (4):(2)));				}
				
				
			}
			
		}
		
	public:
		AutoRemoto(int rx, int tx, int servopin, Motor D1, Motor D2, Motor AT1, Motor AT2, bool x4 = false) : BTH(rx,tx){
			this->PinServo = servopin;
			//this->servo.attach(servopin);
			this->X4 = x4;
			
			
			Motors[0] = AT1;
			Motors[1] = AT2;
			Motors[2] = D1;
			Motors[3] = D2;
			
			AddMotor(Motors,4,255);
			
			MoverGrados(90);
			/*servo.write(90);*/
		}
		
		void Camina(char del = 'W', char atr = 'S', char der ='D', char izq = 'D', char det = 'Z'){
			MoveBTH(del,atr,der,izq,det);
		}
	
};
