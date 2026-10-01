# Dependencias

Esta carpeta contiene las estructuras y funciones globales empleadas en la creación de la librería. Son globales porque se usan en más de una clase, sin relación directa entre sí más allá de compartir la misma estructura.

## MotorDriverType

Enum con 3 constantes:

| Constante | Descripción |
|---|---|
| `DRIVER_PWM_SEPARATE` | Controladores de motores con PWM en un pin aparte. |
| `DRIVER_PWM_INTEGRATED` | Controladores de motores con PWM integrado en L1 y/o L2. |
| `NO_SETTER_SPEED` | Indica que el controlador no tiene PWM (no permite controlar la velocidad). |

## Motor

Estructura con 3 variables de tipo `uint8_t` (byte numérico sin signo):

| Campo | Tipo | Descripción |
|---|---|---|
| `L1` | `uint8_t` | Pin de control 1. |
| `L2` | `uint8_t` | Pin de control 2. |
| `PWM` | `uint8_t` | Pin para controlar la velocidad. |

## UltraSonico

| Campo | Tipo | Descripción |
|---|---|---|
| `Cerca` | `bool` | Indica si se detectó algo dentro del rango de distancia. |
| `angle` | `uint8_t` | Grados del sensor, útil para robots que usan ultrasonicos como "ojos". |
| `Pin` | `uint8_t[2]` | Pines del sensor: índice `0` = trigger, índice `1` = echo. |

## Infrarrojo

| Campo | Tipo | Descripción |
|---|---|---|
| `Pin` | `uint8_t` | Pin del sensor. |
| `Estado` | `bool` | Último estado de detección registrado. |
| `angle` | `uint8_t` | Ángulo del sensor, para mejor control y precisión en las clases, evitando duplicaciones. |

## IRSeguidorLinea

Contiene internamente una estructura `Infrarrojo` (campo `IR`), a la que se agrega:

| Campo | Tipo | Descripción |
|---|---|---|
| `IR` | `Infrarrojo` | Estructura base del sensor infrarrojo. |
| `peso` | `int8_t` (rango: -128 a 127) | Actúa como peso para el sensor IR, debido a la forma en que funciona esta clase. |


## NotesStorage

Este enum contiene constantes para decir donde se alojan en memoria las notas

| Constante | Descripción |
| --- | --- |
| NOTES_RAM | Notas Almacenadas en RAM. |
| NOTES_FLASH | Notas almacenadas en Flash. |


## Nota

| Campo | Tipo | Descripción |
|---|---|---|
| `frecuencia` | `uint16_t` | Frecuencia de la nota. |
| `duracion` | `uint16_t` | Duración de la nota. |

Puede usarse, por ejemplo, para emitir sonidos al detectar algo, como en el seguidor de línea.


## BuzzerType
| Constante | Descripción |
| --- | --- |
| BUZZER_ACTIVE | Buzzer tipo activo. |
| BUZZER_PASSIVE | Buzzer tipo pasivo. |

## ActivateUS

Método global que recibe como parámetro un sensor `UltraSonico` y retorna la salida de su detección en formato **CM** (centímetros).