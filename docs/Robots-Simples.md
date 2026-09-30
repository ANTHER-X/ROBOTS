# Robots-Simples

Esta carpeta contiene los robots simples. Estas clases son solamente expansiones de las clases base, es decir, usan la misma lógica, solo que agregan sensores, formas de tomar los datos, o cambian un poco la lógica u otro tipo de complemento respecto a las clases base o al tipo de robot.

Si el tipo de robot es complicado o no muy extenso, puede ir aquí.

Las clases son hijas de las clases base, así que si no ves un gran cambio es por eso, pero internamente sí cambian las cosas. Cabe decir que en el código está explicado todo lo que se hace.

## AutRem-SSS (Auto Remoto Servo Steering System)

| Método | Descripción |
|--------|-------------|
| `AutRemSSS` | Pide **pinServo**, el pin para el servomotor. Pide la **velocidad**. Pide el **receivePin** para el Bluetooth (si usas ESP32, no lo usarás). Pide el **transmitPin** (si usas ESP32, tampoco darás este pin). Pide el **typeMotor**, para saber qué controlador de motores tienes. Si usas ESP32, los pines de `transmit` y `receive` serán ignorados. |

## RLB-Servo (Resuelve Laberinto con Servomotor)

| Método | Descripción |
|--------|-------------|
| `RLBServo` | Pide la **velocidadRecta**. Pide la **velocidadGiro**. Pide el **timeGiro**, que es el tiempo máximo para girar antes de accionar sus otros controles, en caso de que no pase nada. Pide el **timeRec**, que es el tiempo máximo para recorrer la recta antes de accionar sus otros controles, en caso de que no pase nada. Pide **us**, es decir, la estructura **UltraSonico** para manejar el sensor ultrasónico. Pide el **pinServo**. Finalmente, pide **typeMotor** para el tipo de controlador de motores. |

## RLB-US (Resuelve Laberinto con Sensores Ultrasónicos)

| Método | Descripción |
|--------|-------------|
| `RLBUS` | Pide la **velocidadRecta**, la velocidad de los motores al andar. Pide **velocidadGiro**, la velocidad al girar. Pide el **timeGiro**, el tiempo máximo de giro antes de accionar sus controles, en caso de que no pase nada. Pide el **timeRec**, el tiempo de recorrido antes de hacer otra cosa, en caso de que no pase nada. Pide 3 sensores tipo **UltraSonico**: **_USDelante**, **_USDerecha** y **_USIzquierda**. Finalmente, pide **typeMotor**, para el tipo de controlador de motores usado. |

## SeguidorLinea

| Método | Descripción |
|--------|-------------|
| `SeguidorLinea` | Pide la **velocidadMedia**, así como, opcionalmente, la **velocidadMaxima** y el **motorDriverType**, que es el tipo de controlador de motores. |
| `AddIRs` | Pide un array con los pines de los sensores IR, así como el tamaño exacto de este array. La lista es para detectar en línea recta, comenzando desde la izquierda con índice `0` hacia la derecha. |
| `AddIRColicion` | De forma opcional, agrega el pin del sensor para detectar una colisión. La detección es digital y está pensada para usarse con sensores IR. |
| `AddSoundSystem` | Agrega el sistema de sonido opcional. Si no se agrega el IR de colisión previamente simplemente no se reproducirá el/los sonido(s), pero el resto del sistema de sonido sí se puede usar. Vea [modules](modules.md) si requiere información sobre el sistema de sonido. |

> **Nota de Seguidor:** En los IRs se toma una lista de izquierda a derecha; el/los índice(s) centrales serán los que definan la línea central a seguir y hacia dónde moverse respecto a los extremos. Sí, se plantea colocar los IRs en vertical, todos juntos: mientras más IRs conectados, más exactos son los pesos y menores los tirones bruscos de lado en curvas fuertes.

## Sumo

| Método | Descripción |
|--------|-------------|
| `AddIR` | Pide el pin del sensor infrarrojo delantero. |
| `AddSUS` | Pide los pines para el sensor ultrasónico delantero. |
| `Sumo` | Pide la **Velocidad** de recta. Pide la **VelocidadGiro**. Pide **_DistAtaq**, la distancia máxima en centímetros para atacar. Pide el **DiametroCM** y el **VelGiro_CMS**, para calcular los tiempos de giro según el ángulo en grados de los sensores. Pide el **TRecorridoRecta**, el tiempo en MS que atacará o se moverá hacia atrás y adelante (esto en casos especiales, como salirse y tener que retroceder) si no detecta nada más. Pide el **typeMotor**, para saber qué tipo de controlador tiene. |
| `AddSoundSystem` | Agrega el sistema de sonido, para reproducirlo en ciertas condiciones de estado. Si necesitas información del sistema de sonido, vea [modules](modules.md). |
| `SetAtackSound` | Configura una melodía para usar como sonido de **Ataque**; la melodía ya debe estar registrada en el sistema de sonido. |
| `SetBackSound` | Configura una melodía para usar como sonido de **Retroceso** (Sumo moviéndose hacia atrás); la melodía ya debe estar registrada en el sistema de sonido. |
| `SetIRSound` | Configura una melodía para usar como sonido de **alerta de salida del dohyō** (el círculo de combate, con centro blanco y perímetro negro); la melodía ya debe estar registrada en el sistema de sonido. |

> **Nota de Sumo:** Los sensores funcionan en un rango de 180 grados: de 1 a 180 para girar a la izquierda, y de -1 a -180 para la derecha. Los 360 grados se distribuyen así: el grado 0 corresponde al mínimo del sensor ultrasónico, siendo el centro desde donde se mueve a la derecha o izquierda; es, en esencia, como los "ojos principales" para atacar de frente.
>
> Necesitas tomar el diámetro del robot y su velocidad máxima en cm/s a la que se mueve, para que los cálculos internos sean lo más precisos posible.

