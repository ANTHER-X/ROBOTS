//ROBOT SUMO

#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "Dependencias-Old/Sensores.hpp"
#include "Robot.hpp"

class SUMO : protected Robot{
	private:
		
		//si crece mucho lo mejor seria usar un for en el constructor
		//Pines de Infrarrojo
		int SirDef[4] = {-1,-1,-1,-1};//para ver cual se activo, 0->atras, 1->adelante, 2->derecha, 3->izquierda
		int SirAccionado[4] = {0,0,0,0};//valores 0->LOW, 1->HIGH
		
		//Pines de Los Ultrasonicos  0->trig, 1->echo
		UltraSonico SensUS[4] = {0};
		
		//Pines de Motores (solo para 2 o 4 motores de momento)
		Motor M2Pin[2] = {0};//les da un valor de 0 a todo
		Motor M4Pin[4] = {0};
		//para guardar los tipos de motores (para un uso mas facil en la funcion camina)
		Motor* Motores[2] = {M2Pin,M4Pin};
		uint8_t cantMotors[2] = {2,4};//para la cantidad de motores usados
		uint8_t MtrUsado = -1;//para ver cual motor se uso 0->2Motores, 1->4Motores
		
		//parametros base
		int Velocidad, TGiro;
		int DistAtac, DistEsq;
		double Distcm ;//guarda la distancia de los SUS cuando se acciona uno
		int Recorrido;//segundos
		
		//para buscar al enemigo
		bool OnlyFront = false;//para ver si solo usa el sensoe US de delante
		
		//En caso de que use el modulo Bluethoot
		bool USE_BT = false;
		SoftwareSerial *BTHT = nullptr;//putero a un Serial para usar el bluethoot sin interferir con el Serial del Arduino
		char Tecla;
		
		//Metodos Privados 
		
		//Los Ultrasonicos para los ojos
		void AddPinSUS(uint8_t Num, uint8_t triger, uint8_t echo){
			SensUS[Num].Pin[0] = triger; pinMode(SensUS[Num].Pin[0], OUTPUT);
			SensUS[Num].Pin[1] = echo; pinMode(SensUS[Num].Pin[1], INPUT);
			SensUS[Num].Activo = true;
		}
		
		//Define los infrarrojos
		void AddInfra(uint8_t num, uint8_t pin){
			SirDef[num] = pin; pinMode(SirDef[num], INPUT);
		}
		
		//define el estado de los Infrarrojos
		void Infrarrojos(){
			Serial.println("Capturando Infrarrojos");
			//verificamos cuales si se usan (-1 quiere decir que no los declaro en los metodos)
			//El accion seria Sir[n]==0->LOW, Sir[n]==1->HIGH
			if(SirDef[0] != -1)SirAccionado[0] = digitalRead(SirDef[0]);
			if(SirDef[1] != -1){SirAccionado[1] = digitalRead(SirDef[1]); Serial.println(SirAccionado[1]);}
			if(SirDef[2] != -1)SirAccionado[2] = digitalRead(SirDef[2]);
			if(SirDef[3] != -1)SirAccionado[3] = digitalRead(SirDef[3]);
		}
		
		//captura la distancia en cm, Tienes que pasarle cada Pin de los Ultra
		void Ultrasonicos(UltraSonico &US){
			
			digitalWrite(US.Pin[0], HIGH); //mando una senial de sonido
		    delayMicroseconds(100);
		    digitalWrite(US.Pin[0], LOW); //detengo la senial
		    delayMicroseconds(50);
			Distcm = (pulseIn(US.Pin[1], HIGH) / 58.2);//medira en centimetros
			
			Serial.print("La distancia tomada es de: ");
			Serial.println(Distcm);
			
			//verifica la distancia de esquivado
			if(Distcm <= DistEsq){//si esta muy cerca
				Serial.println("Encontramos algo muy cerca");
				US.Cerca = true;//activamos el cerca
			}else if(Distcm <= DistAtac){//si no esta cerca pero esta dentro del rango de ataque seguimos
				Serial.println("Encontramos algo lejos");
				US.Lejos = true;
			}else{//si no todo es false
				US.Cerca = false;
				US.Lejos = false;
			}
		}
		
		
		bool BTHTMOVER(char del = 'W', char atr = 'S', char der ='D', char izq = 'A', char det = 'Z', char Desable = 'E'){
			
			//si le llega algun dato
			if(BTHT->available()){
				
				//lo leemos
				Tecla = BTHT->read();
				
				//dependiendo de la lectura, nos movemos o no
				if(Tecla == del){	MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, 200);		}
				if(Tecla == atr){	MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], false, 200);		}
				if(Tecla == der){	MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], true, 200);		}
				if(Tecla == izq){	MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], false, 200);		}
				if(Tecla == det){	Stop(Motores[MtrUsado], cantMotors[MtrUsado]);	}
				if(Tecla == Desable) return false;
				
				//nos detenemos
				Stop(Motores[MtrUsado], cantMotors[MtrUsado]);
				
				//imprimimos la tecla que se imprimira
  				Serial.println(Tecla);
			}
			
			return true;
		}
		
		/*Este metodo no deja de buscar hasta que encuentra algo de frente.
		Y si algo va hacia el, solo se coloca frente a este, asi que lo pueden tumbar
		si no es tan pesado*/
		bool BuscaEnemy(Motor M[], int Cant, bool RMOV){
			
			Serial.println("Buscando Enemigo");
			uint8_t cicloBucle = 0;
			
			//si solo usa el sesor de delante
			if(OnlyFront == true){
				
				Serial.print(RMOV);
				Serial.println("Buscando Enemigo Con un solo Sensor Delantero");
				
				while(cicloBucle < 15){
					
					cicloBucle++;
					
					MDerIzq(M, Cant, RMOV, TGiro/3);//nos movemos, activando los sensores un poco mas
					Ultrasonicos(SensUS[1]);
					if( SensUS[1].Cerca  ){
						Serial.println("Enemigo Encontrado");
						return true;//decimos que encontramos al enemigo
					}
				}
				
			}else{//si usa un sensor mas
				
				
				while(cicloBucle < 15){
					
					cicloBucle++;
					
					//vemos cuales sensores US estan activos y la distancia que toman
					for(int i=0; i<4; i++){
						if(SensUS[i].Activo) Ultrasonicos(SensUS[i]);
					}
					
					if(SensUS[1].Lejos){//si detecta a lo lejos al enemigo por delante
						Serial.println("Enemigo Encontrado.");
						return true;//decimos que lo encontro
					
					}else if(SensUS[0].Activo && SensUS[0].Lejos){//si detecta al enemigo en la espalda giramos 2 veces
						MDerIzq(M, Cant, RMOV, TGiro*2);
						
					}else if(SensUS[2].Activo && SensUS[2].Lejos){//si detecta en la derecha
						MDerIzq(M, Cant, true, TGiro);
						
					}else if(SensUS[3].Activo && SensUS[3].Lejos){//si detecta en la izquierda
						MDerIzq(M, Cant, false, TGiro);
						
					}else{//si no detecta nada Giramos un poco
						MDerIzq(M, Cant, RMOV, TGiro/3);
					}
				}
			}
			
				
			//si por mas, no encuentra nada, decimos que no habia nada
			return false;
		}
		
	/*Metodos publicos*/
	public:
		//Constructor
		SUMO(int DistAtaque, int DistEsquivo, int Vel, int TiempoGiro, int TRec){
			this->Velocidad = Vel;
			this->DistAtac = DistAtaque;
			this->DistEsq = DistEsquivo;
			this->TGiro = TiempoGiro;
			this->Recorrido = TRec;
		}
		
		~SUMO(){
			//limpiamos la memoria dinamica
			delete BTHT;
		}
		
		//Sensores Infrarrojos (se declaran los pines que usaran)
		void SirAtras(uint8_t pin){
			AddInfra(0,pin);
		}
		void SirAdelante(uint8_t pin){
			AddInfra(1,pin);
		}
		void SirIzq(uint8_t pin){
			AddInfra(3,pin);
		}
		void SirDer(uint8_t pin){
			AddInfra(2,pin);
		}
		
		//Sensores de Ultrasonido (se declaran los pines que usaran)
		void SusAtras(uint8_t triger, uint8_t echo){
			AddPinSUS(0,triger,echo);
		}
		void SusAdelante(uint8_t triger, uint8_t echo){
			AddPinSUS(1,triger,echo);
		}
		void SusDer(uint8_t triger, uint8_t echo){
			AddPinSUS(2,triger,echo);
		}
		void SusIzq(uint8_t triger, uint8_t echo){
			AddPinSUS(3,triger,echo);
		}
		
		//Motores, 2 o 4 Motores (se declaran los pines que usaran)
		void Motors_2(Motor M1, Motor M2){
			M2Pin[0] = M1;
			M2Pin[1] = M2;
			
			AddMotor(M2Pin,2, this->Velocidad);
			
			MtrUsado = 0;
		}
		
		void Motors_4(Motor M1, Motor M2, Motor M3, Motor M4){
			M4Pin[0] = M1;
			M4Pin[1] = M2;
			M4Pin[2] = M3;
			M4Pin[3] = M4;
			
			AddMotor(M4Pin,4, this->Velocidad);
			
			MtrUsado = 1;
		}
		
		/*Para el blueThoot, el modulo que usan creo que si es ese
		(HC05)*/
		void HC05(int rx, int tx){
			//creamos un nuevo Serial para el Bluethoot
			BTHT = new SoftwareSerial(rx,tx);
			BTHT->begin(9600);//Velocidad estandar (bits por segundo)
			//decimos que si usamos el Bluethoot
			USE_BT = true;
		}
		
		/*PARA QUE SE MUEVA DE UNA VEZ
		RMov es para que alterne los giros o movimentos cuando se le acercan, por lo que en
		setup deberia poner 'RSeed' para iniciar la semilla random
		Los caracterez de BT son para moverse si usas el BlueThoot*/
		void Camina(char BTdel = 'W', char BTatr = 'S', char BTder ='D', char BTizq = 'A', char BTdet = 'Z', char BTDes = 'E'){
			
			//si usa caminar y no ah iniciado ninguno de los motores, no hara nada
			if(MtrUsado == -1) {
				Serial.println("Sin Motores");
				return;
			}
			
			bool RMov = random(0,1);//modo random de 0 a 1
			
			//0 atras, 1 delante, 2 derecha, 3 izquierda
			//vemos que sensores usa
			for(uint8_t i=0; i<4; i++){
				
				if(SensUS[i].Activo == true && i == 1) OnlyFront = true;
				
				if(SensUS[i].Activo == true && i != 1){
					 OnlyFront = false;
					 break;
				}
				
			}
			
			while(true){
				/*
				while(1)
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//caminamos hacia adelante*/
				
				//en caso de que use el Bluethoot para moverse
				while(USE_BT == true && BTHTMOVER(BTdel, BTatr, BTder, BTizq, BTdet, BTDes)){
					//puedes meter algo aqui si quieres
				}
				
				//nos detenemos para buscar
				Stop(Motores[MtrUsado], cantMotors[MtrUsado]);
				delayMicroseconds(360);
				
				//bucamos al enemigo, si lo encontramos...]
				if(BuscaEnemy(Motores[MtrUsado], cantMotors[MtrUsado], RMov))
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//caminamos hacia adelante
				
				//DETECCION Y USO DE LOS INFRARROJOS
				Infrarrojos();//captura el estado de cada infrarrojo
				
				//en base a la captura de los infrarrojos
				if(SirDef[0] != -1 && SirAccionado[0] == 0)	//si se sale por atras
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//se mueve hacia adelante
				
				if(SirDef[1] != -1 && SirAccionado[1] == 0){//si se sale por adelante
					Serial.println("Moviendo hacia Atras y a un lado");
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], false, Recorrido);//se mueve para atras
					MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], RMov, TGiro);//va a la izquierda o derecha
					
				}
				if(SirDef[2] != -1 && SirAccionado[2] == 0){//si se sale por la derecha
					MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], false, TGiro);//va a la izquierda
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//luego hacia adelante
					
				}
				if(SirDef[3] != -1 && SirAccionado[3] == 0){//si se sale por la izquierda
					MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], true, TGiro);//va a la derecha
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//luego hacia adelante
				}
				
				
				//en base a la captura de los ultrasonicos
				if(SensUS[0].Cerca){//si le llegan de atras
					Serial.println("Encontramos algo atras");
					MDerIzq(Motores[MtrUsado], cantMotors[MtrUsado], RMov, TGiro);//gira a la derecha o izquierda
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);//luego camina hacia adelanre
					
				}else if(SensUS[2].Cerca || SensUS[3].Cerca){//de le llegan del lado derecho o izquierdo
					Serial.println("Encontramos algo en algun lado");
					MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], RMov, Recorrido);//camina hacia adelanre o atras
				}
				/*
				//camimanos hacia adelante
				Serial.println("Moviendo hacia adelante");
				MDelAtrs(Motores[MtrUsado], cantMotors[MtrUsado], true, Recorrido);*/
			}
		}
	
};
