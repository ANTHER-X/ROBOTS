//Se supone que es para el uso en un Sumo controlado por BTH
#include "Robot.hpp"

#if defined(__AVR__)
    #include <SoftwareSerial.h>
#else
    #include <BluetoothSerial.h>
#endif


#pragma once

class SumoBTHBase : public Robot{

    protected:

        virtual void BTHMove(){
            
        }


    public:

};