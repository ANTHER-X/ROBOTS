# Old-Version-Concept V-0.0.1

Este fue el primero conceptop de la creacion de una libreria, estuve creando un par de clases para un robot y se me ocurrio hacer esto de rapido, despues hice una mejor estructura y remplaze esto pero creo que esta funciona asi que la dejare, de igual forma no es la adecuada pero aun asi puedes usarla.

La clase solo sirve con AVR como arduino

## Sensores

Aqui estan los sensores empleados, existen solo 2 **Motor** el cual contiene **L1**, **L2**, **PWM**, y **UltraSonico**, el cual contiene sus 2 pines, y mas atributos

## Robot

Esta clase maneja de forma mas basica el movimiento de los motores

## AutoRemoto

| Metodo | Descripcion
|--------|-----------
| AutoRemoto | Pide los pines rx y tx del controlador bluethoot, tambien el pin del servo-motor, ademas, pide 4 motores para ser controlado y un boolean opcional "X4" para accionar o no la potencia de los 4 motores
| Camina | Mueve el robot y opcionalmente puedes darle 5 char para controlar su movimiento y detener en caso de que quieras usar otros parametros para mover

## INSECTO

| Metodo | Descripcion
|--------|-----------
| INSECTO | Pide la Velocidad
| Motors_2 | Pide 2 motores para ser agregados
| Motors_4 | Pide 4 motores para ser agregados
| Camina | Hace que los motores se muevan


## ResuelveLaberinto

| Metodo | Descripcion
|--------|-----------
| ResuelveLaberinto | Pide y agrega 4 motores, asi como un sensor ultrasonico y el pin del servo-motor
| ChangeStats | Puedes pasarle opciolamente la velocidad de los motores y la distancia de vista maxima para ser cambiadas.
| Camina | Hace que ande, igual debe estar en loop


## SEGUIDORLINEA

| Metodo | Descripcion
|--------|-----------
| SEGUIDORLINEA | Pide la velocidad de los motores, la duracion de recorrido antes de accionar otras cosas, y el tiempo de giro que es para lo mismo
| SetSir | Pide 3 pines para los sensores infrarrojos, izquierda, centro y dereca, los 3 se configuran en el mismo metodo
| SetMotor | Pide y agrega 2 motores
| Camina | Hace que ande, debe estar en loop


## SUMO

| Metodo | Descripcion
|--------|-----------
| SUMO | Pide la distancia de ataque maxima que podra tomar, esto en formato CM, asi mismo, la distancia de esquivo, pide tambien la velocidad de los motores, asi como el tiempo de giro y recta, ambos funcionan para que se mueva por N tiempo antes de activar sus otros sensores.
| SirAtras | Pide el pin del sensor IR trasero
| SirAdelante | Pide el pin del sensor IR delantero
| SirIzq | Pide el pin del sensor IR izquierdo
| SirDer | Pide el pin del sensor IR derecho
| SusAtras | Pide el sensor ultrasonico de atras
| SusAdelante | Pide el sensor ultrasonico de delante
| SusIzq | Pide el sensor ultrasonico de izquierda
| SusDer | Pide el sensor ultrasonico de derecha
| Motors_2 | Pide, agrega e inicaliza 2 motores
| Motors_4 | Pide, agrega e inicaliza 4 motores
| HC05 | Pide los pines rx y tx de un modulo bluethoot en caso de que quieras controlarlo desde bluethoot
| Camina | hace andar el sumo, si pusiste bluethoot tienes la opcion de cambiar 6 char, los cuales dan entrada al control de movimiento, stop del sumo, asi como deshabilitarlo y dejar que ande solo si es que puede.


