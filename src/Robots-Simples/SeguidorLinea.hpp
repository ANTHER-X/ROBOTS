/*
 * Proyect: ROBOTS
 * Author: ANTHER
 * Licence: MIT
 * GitHub: https://github.com/ANTHER-X/ROBOTS
*/


#ifndef SEGUIDORLINEA_HPP
#define SEGUIDORLINEA_HPP

#include "../Robots-Base/Robot.hpp"

class SeguidorLinea : public Robot{
protected:

    IRSeguidorLinea* irs[MAXIRSEGUIDOR];
    uint8_t tamIrs = 0, vMax;
    unsigned long timeMove;
    bool isPar;
    short centro, pIzq = 0, pDer = 0;

    //Cosas para coliciones
    bool notasInFlash = false;
    SoundBuzzer* notas[MAXNOTAS];
    uint8_t NotasCount = 0;
    uint8_t actualIndexSoundPlayer = 0;
    unsigned long initSoundTime = 0;
    BuzzerType buzzerType;
    Infrarrojo IRColicioner = {0};
    uint8_t pinBuzzerSound = 0;

    void AccionaAllIR();
    void MoveMotorsForIR();
    void PotenciaEquilibrio();
    //Para variar la velocidad de los motores
	void ConfigVelocidad(Motor* M, uint8_t size, uint8_t vDer, uint8_t vIzq);

    //Para poder saber si el sensor de colision se activo
    bool IRColicion();
    void StarSoundColicion();

    //Iniciamos las Stats de los IRs
    void InitStatsIRs();

    //Para no ocultar el metodo de la clase base y evitar errores de metodos no existentes
    using Robot::ConfigVelocidad;

public:
    SeguidorLinea(uint8_t velocidadMedia, uint8_t velocidadMaxima = 255, MotorDriverType motorDriverType = DRIVER_PWM_SEPARATE, BuzzerType buzzerType = BUZZER_ACTIVE);

    void AddIRColicion(uint8_t pin);
    void AddBuzzerPin(uint8_t pin);
    void AddNotas(SoundBuzzer* notas, uint8_t size, bool inFlash = false);
    void AddIRs(uint8_t IRpines[], uint8_t tamIR);
    virtual void Camina(unsigned int TimeMinuts = 0) override;

};




#endif