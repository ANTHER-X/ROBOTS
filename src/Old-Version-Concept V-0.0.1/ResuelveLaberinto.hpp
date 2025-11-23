
#pragma once

#include <Arduino.h>
#include <Servo.h>
#include "Dependencias-Old/Sensores.hpp"
#include "Robot.hpp"

class ResuelveLaberinto : protected Robot{
	private:
		
		/*En caso de que de problema el usar solo el pin
		Servo servo;*/
		
		int ServoMtr;
		int DistFront;
		int DistDer;
		int DistIzq;
		
		//Me indicara la distancia maxima
		int DistMaxMov;
		int Max;
		bool IsMaxDis;
		
		short MoveTo;
		
		Motor Motors[4];
		
		UltraSonico US;
		
		void MoverGrados(int angle){
			/*map(angulo,desdemin,desdemax,hastamin,hastamax) <- viene en arduino, te da un valor proporcianal de distancia de
			acuerdo al angulo insertado.
			Matematicamente usa esta opercion:
			(pulso) = (angulo - desdemin) * (hastamax - hastamin) / (desdemax - desdemin) + hastamin
       		 = angulo * hastamin / desdemax + hastamin*/
			int pulso = map(angle, 0, 180, 1000, 2000); // convierte grados a microsegundos
		
			for (int i = 0; i < 50; i++) {
			    digitalWrite(ServoMtr, HIGH);
			    delayMicroseconds(pulso);
			    digitalWrite(ServoMtr, LOW);
				delay(20 - pulso / 1000);  // completa el ciclo de 20 ms
			}
		}
		
		int ActivateUS(){
			digitalWrite(US.Pin[0], HIGH); //mando una senial de sonido
		    delayMicroseconds(10);
		    digitalWrite(US.Pin[0], LOW); //detengo la senial
			return (pulseIn(US.Pin[1], HIGH) / 58.2);//medira en centimetros
		}
	
	public:
		
		ResuelveLaberinto(int pinServo, UltraSonico ultrason, Motor D1, Motor D2, Motor AT1, Motor AT2){
			this->ServoMtr = pinServo;
			this->DistMaxMov= 15;
			this->Max = 0;
			
			this->US = ultrason;
			
			pinMode(US.Pin[0], OUTPUT);
			pinMode(US.Pin[1], INPUT);
			US.Activo = true;
			
						
			Motors[0] = D1;
			Motors[1] = D2;
			Motors[2] = AT1;
			Motors[3] = AT2;
			
			AddMotor(Motors,4,255);
			
			MoverGrados(90);
			/*servo.write(180);*/
		}
		
		void ChangeStats(int vel = 255, int distMaxMov = 15){
			AddMotor(Motors,4,vel);
			
			this->DistMaxMov= distMaxMov;
		}
		
		//en bucle
		void Camina(){
			//reseteamos
			Max = 0;
			
			//Giramos y vamos detectando distancias
		    MoverGrados(180); delay(100); DistDer = ActivateUS(); delay(200);
		    MoverGrados(90);  delay(100); DistFront = ActivateUS(); delay(200);
		    MoverGrados(0);   delay(100); DistIzq = ActivateUS(); delay(200);
		    MoverGrados(90);  delay(200);
		    
		    /*En caso de que el usar solo el pin de problemas
			
		    servo.write(180); delay(100); DistDer = ActivateUS(); delay(200);
		    servo.write(90);  delay(100); DistFront = ActivateUS(); delay(200);
		    servo.write(0);   delay(100); DistIzq = ActivateUS(); delay(200);
		    servo.write(90);  delay(200);
			*/
			
			//vemos la DistMax
		    if(DistDer > Max) Max = DistDer;
		    if(DistIzq > Max) Max = DistIzq;
		    if(DistFront > Max) Max = DistFront;
			
			//vemos si detecta un maxDist
			if(Max >= DistMaxMov) IsMaxDis = true;
			else IsMaxDis = false;
			
			//decidimos a donde movernos
			if(DistDer == Max) MoveTo = 0;
			if(DistFront == Max) MoveTo = 1;
			if(DistIzq == Max) MoveTo = 2;
		
			//girar
		    switch(MoveTo){
		        case 0: MDerIzq(Motors,4,true,0); delay(1500); break; //derecha
		        case 2: MDerIzq(Motors,4,false,0); delay(1500); break;//izquierda
		    }
			
			//adelante
		    MDelAtrs(Motors,4,true,0);
		    delay(IsMaxDis ? 750 : 1500);
		}

	
	
};
