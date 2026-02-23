# Depedencias

Esta carpeta contiene las estructuras y funciones que eh empleado para la creacion de la libreria, son globales ya que se usan en mas de una clase sin relacion entre otra que usa la misma estructura.

## MotorDriverType

Este es un enum que contiene solo 2 constantes, **DRIVER_PWM_SEPARATE** para controladores de motores con PWM en un pin aparte y **DRIVER_PWM_INTEGRATED** que es la constante para controladores de motores con PWM integrado en L1 y/o L2


## Motor

Esta estructura contiene 3 variables tipo byte numerico sin signo (uint8_t). L1, L2 y el PWM para controlar la velocidad.

## UltraSonico

Contiene un bool **Cerca** que nos indica si detecto algo en el rango de distancia de deteccion, tambien un uint8_t para el ID, esto para poder ser usado de forma mas ordenada en las clases y evitar replicas.
Finalmente un array de size 2, que contiene sus pines triger (index 0) y echo (index 1).


## Infrarrojo

Esta estructura contiene el uint8_t para su pin, asi como un bool para guardar su ultimo estado de deteccion y su ID para mejor control en las clases y evitar duplicaciones.


## IRSeguidorLinea

Este struct contiene internamente un strcut de tipo IR y solo le agrega un int8_t (range: -128 - 127) que actua como pesaje para los IR, esto debido a la forma en que funciona esta clase.


## SoundBuzzer

Esta struct tiene 2 variables **uint16_t**, una es para la frecuencia de la nota y la otra para la duracion de la misma


## ActivateUS

Este es un metodo global que toma como parametro un sensor Ultrasonico y retorna la salida de su deteccion en formato CM.