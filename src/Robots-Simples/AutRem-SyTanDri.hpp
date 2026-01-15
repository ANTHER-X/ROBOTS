#include "../Robots-Base/AutoRemotoBase.hpp"

#pragma once

/*No iniciado*/
class TankDriver : public AutoRemotoBase{
protected:


public:
    TankDriver(uint8_t velocidad, uint8_t receivePin, uint8_t transmitPin, MotorDriverType typeMotor)
    :AutoRemotoBase(velocidad, receivePin, transmitPin, typeMotor){}

};