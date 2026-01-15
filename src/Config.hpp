/*
    Configuracion del proeycto, cada macro sera para definir el uso del codigo.
    Desable = 0
    Enable = 1
*/

#ifndef CONFIG_HPP
#define CONFIG_HPP

//#define USE_WIFI            0 //para modulos wifi (de ESP32 por el momento)
//#define USE_BTH_ARDUINO     0 //para modulos Bluethoot de arduino (SoftwareSerial.h)
//#define USE_BTH_ESP         0 //para el modulo BkueThoot de ESP
#define USE_IR                1 //para sensores infrarrojos

//Mas macros para depuracion:
#ifndef SERIAL_DEBUG
#define SERIAL_DEBUG 1
#endif

#if SERIAL_DEBUG 
    #define DBG_PRINT(x)    Serial.print(x)
    #define DBG_PRINTLN(x)  Serial.println(x)
    #define DBG_MOTORTEXT_PRINT Serial.print("[Motor]: ");

    #define DBG_MOTOR(L1, L2, PWM) \
        do { \
            Serial.print("[Motor] "); \
            Serial.print("L1: "); Serial.print(L1); \
            Serial.print(" L2: "); Serial.print(L2); \
            Serial.print(" PWM: "); Serial.print(PWM); \
        } while (0)

    #define DBG_MOTOR_VELOCIDAD(L1, L2, PWM, VEL) \
        do { \
            DBG_MOTOR(L1, L2, PWM); \
            Serial.print(" Vel: "); Serial.println(VEL); \
        } while (0)
    
    #define DBG_VALUE_LN(T,V) \
        do { \
            Serial.print(T); \
            Serial.println(V); \
        } while (0)

    #define DBG_VALUE(T,V) \
        do { \
            Serial.print(T); \
            Serial.print(V); \
        } while (0)
    
#else
    #define DBG_PRINT(x)
    #define DBG_PRINTLN(x)
    #define DBG_MOTORTEXT_PRINT
    #define DBG_MOTOR(L1, L2, PWM)
    #define DBG_MOTOR_VELOCIDAD(L1, L2, PWM, VEL)
    #define DBG_VALUE_LN(T,V)
    #define DBG_VALUE(T,V)
#endif


#endif