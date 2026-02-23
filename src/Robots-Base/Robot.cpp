/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/

#include "Robot.hpp"

/*
Robot::
*/

void Robot::AddMotors(Motor* Mtrs, uint8_t size) {
    
    //evita demaciados motores
    if(CantidadMotores + size > MAXMOTORS || size <= 0){
        DBG_PRINTLN("Demaciados motores.");
        return;
    }

    //Agregamos los motores y los inicializamos
    for(uint8_t i=CantidadMotores; i<CantidadMotores+size; i++){
        Motores[i] = &Mtrs[i];
        SetMotor(Motores[i], Vel);
    }
    CantidadMotores += size;

    //info para debugin
    DBG_VALUE("Agregados. Motores: ", CantidadMotores);
}

void Robot::ConfigVelocidad(Motor M[], uint8_t size, uint8_t vel){
    //seteamos velocidad
	for(uint8_t i=0; i<size; i++){
		if(motorType == DRIVER_PWM_SEPARATE) analogWrite(M[i].PWM, vel);
        else  analogWrite(M[i].L1, vel);
        //debugin
        DBG_MOTOR_VELOCIDAD(M[i].L1, M[i].L2, vel);
	}
}

//Movimientos de los motores, supongamos 2 motores (6 pines), aunque puede funcionar para mas
void Robot::MDelAtrs(Motor* M, uint8_t size, bool delante){
    
    for(uint8_t i=0; i<size; i++){
        digitalWrite(M[i].L1, (delante ? HIGH : LOW));
        digitalWrite(M[i].L2, (delante ? LOW : HIGH));
        //debugin
        DBG_PRINT_Var((M[i].L1 + " " + M[i].L2));
        DBG_VALUE_LN(". Camina hacia: ", (delante ? "delante" : "atras"));
    }
}

//si usa true va hacia la derecha, si usa false, hacia la izquierda
//deberia funcionar para motores pares en lineas de 2
void Robot::MDerIzq(Motor* M, uint8_t size, bool Der){
    
    for(uint8_t i=0; i<size; i++){
        digitalWrite(M[i].L1, Der ? LOW : HIGH);
        digitalWrite(M[i].L2, Der ? HIGH : LOW);
        Der = Der ? false : true;//cambia de direccion del siguiente motor (es el de al lado por lo que guirara)
        
        //debugin
        DBG_PRINT_Var((M[i].L1 + " " + M[i].L2));
        DBG_VALUE_LN(". gira hacia: ", (Der ? "derecha" : "izquierda"));
    }
    
}

void Robot::MStop(Motor* M, uint8_t size){
    
    for(uint8_t i=0; i<size; i++){
        digitalWrite(M[i].L1, LOW);
        digitalWrite(M[i].L2, LOW);
        
        //debugin
        DBG_PRINT_Var((M[i].L1 + " " + M[i].L2));
        DBG_PRINTLN(". Se detiene.");
    }
}

//Para definir los motores
void Robot::SetMotor(Motor* M, uint8_t vel){
    //Le damos un modo al pines
    pinMode(M->L1, OUTPUT);
    pinMode(M->L2, OUTPUT);
    
    if(motorType == DRIVER_PWM_SEPARATE){
        pinMode(M->PWM, OUTPUT);
        analogWrite(M->PWM, vel);
    }
    else{
        analogWrite(M->L1, vel);
        M->PWM = M->L1;
    }
    DBG_MOTOR_VELOCIDAD(M->L1, M->L2, vel);
}