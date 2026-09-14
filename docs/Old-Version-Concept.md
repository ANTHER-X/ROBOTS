# Old-Version-Concept V-0.0.1

Este fue el primer concepto de la creación de una librería. Estuve creando un par de clases para un robot y se me ocurrió hacer esto rápido; después hice una mejor estructura y reemplacé esto, pero creo que aún funciona, así que la dejaré. De igual forma, no es la más adecuada, pero aun así puedes usarla.

## Sensores

Aquí están los sensores empleados, existen solo 2:

- **Motor**: contiene `L1`, `L2` y `PWM`.
- **UltraSonico**: contiene sus 2 pines, y más atributos.

## Robot

Esta clase maneja de forma más básica el movimiento de los motores.

## AutoRemoto

| Método | Descripción |
|--------|-------------|
| `AutoRemoto` | Pide los pines RX y TX del controlador Bluetooth, también el pin del servomotor. Además, pide 4 motores para ser controlados y un booleano opcional `X4` para activar o no la potencia de los 4 motores. |
| `Camina` | Mueve el robot; opcionalmente puedes darle 5 caracteres para controlar su movimiento y detenerlo, en caso de que quieras usar otros parámetros para el movimiento. |

## INSECTO

| Método | Descripción |
|--------|-------------|
| `INSECTO` | Pide la velocidad. |
| `Motors_2` | Pide 2 motores para ser agregados. |
| `Motors_4` | Pide 4 motores para ser agregados. |
| `Camina` | Hace que los motores se muevan. |

## ResuelveLaberinto

| Método | Descripción |
|--------|-------------|
| `ResuelveLaberinto` | Pide y agrega 4 motores, así como un sensor ultrasónico y el pin del servomotor. |
| `ChangeStats` | Puedes pasarle opcionalmente la velocidad de los motores y la distancia de visión máxima, para ser cambiadas. |
| `Camina` | Hace que ande; debe estar en loop. |

## SEGUIDORLINEA

| Método | Descripción |
|--------|-------------|
| `SEGUIDORLINEA` | Pide la velocidad de los motores, la duración del recorrido antes de accionar otras cosas, y el tiempo de giro, que es para lo mismo. |
| `SetSir` | Pide 3 pines para los sensores infrarrojos: izquierda, centro y derecha. Los 3 se configuran en el mismo método. |
| `SetMotor` | Pide y agrega 2 motores. |
| `Camina` | Hace que ande; debe estar en loop. |

## SUMO

| Método | Descripción |
|--------|-------------|
| `SUMO` | Pide la distancia de ataque máxima que podrá tomar (en formato CM), así como la distancia de esquive. También pide la velocidad de los motores, así como el tiempo de giro y de recta; ambos funcionan para que se mueva durante N tiempo antes de activar sus otros sensores. |
| `SirAtras` | Pide el pin del sensor IR trasero. |
| `SirAdelante` | Pide el pin del sensor IR delantero. |
| `SirIzq` | Pide el pin del sensor IR izquierdo. |
| `SirDer` | Pide el pin del sensor IR derecho. |
| `SusAtras` | Pide el sensor ultrasónico de atrás. |
| `SusAdelante` | Pide el sensor ultrasónico de adelante. |
| `SusIzq` | Pide el sensor ultrasónico de izquierda. |
| `SusDer` | Pide el sensor ultrasónico de derecha. |
| `Motors_2` | Pide, agrega e inicializa 2 motores. |
| `Motors_4` | Pide, agrega e inicializa 4 motores. |
| `HC05` | Pide los pines RX y TX de un módulo Bluetooth, en caso de que quieras controlarlo desde Bluetooth. |
| `Camina` | Hace andar al sumo. Si configuraste Bluetooth, tienes la opción de enviar 6 caracteres, los cuales dan entrada al control de movimiento, al stop del sumo, así como a deshabilitarlo y dejar que ande solo (si es que puede). |