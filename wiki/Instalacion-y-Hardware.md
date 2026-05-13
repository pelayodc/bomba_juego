# Instalacion y Hardware

## Requisitos

- Placa compatible con Arduino y pines usados en el sketch. Por los pines y el codigo Wi-Fi comentado, el proyecto esta pensado para una placa tipo ESP32.
- Arduino IDE o entorno compatible.
- Libreria `Keypad`.
- Teclado matricial 4x4.
- Buzzer activo o pasivo conectado como salida digital.
- Dos LEDs rojos para estado de fallos.
- Un LED verde para estado de exito.
- Un LED RGB con tres canales controlados por PWM.

## Librerias

El sketch incluye:

```cpp
#include <Keypad.h>
```

El codigo tambien contiene referencias comentadas a:

```cpp
//#include <WiFi.h>
//#include <WebServer.h>
```

La parte Wi-Fi no esta activa en la version actual.

## Teclado 4x4

Distribucion de teclas:

| Fila/Columna | C1 | C2 | C3 | C4 |
| --- | --- | --- | --- | --- |
| F1 | `1` | `2` | `3` | `A` |
| F2 | `4` | `5` | `6` | `B` |
| F3 | `7` | `8` | `9` | `C` |
| F4 | `*` | `0` | `#` | `D` |

Pines de filas:

```cpp
byte pin_rows[ROW_NUM] = {14, 26, 17, 16};
```

Pines de columnas:

```cpp
byte pin_column[COLUMN_NUM] = {4, 0, 2, 15};
```

## Salidas

| Componente | Pin |
| --- | ---: |
| Buzzer | `23` |
| LED rojo 1 | `19` |
| LED rojo 2 | `21` |
| LED verde | `22` |
| RGB rojo | `32` |
| RGB verde | `33` |
| RGB azul | `13` |

## Controles

| Tecla | Uso |
| --- | --- |
| `*` | Confirma respuestas numericas. |
| `#` | Reinicia la entrada actual. |
| `2` | Movimiento arriba en el laberinto. |
| `4` | Movimiento izquierda en el laberinto. |
| `6` | Movimiento derecha en el laberinto. |
| `8` | Movimiento abajo en el laberinto. |
| `A`, `B`, `C`, `D` | Respuestas de la fase Simon. |

## Estado inicial

En `setup()` se configuran los pines como salida, se inicia `Serial` a `115200` baudios, el buzzer queda apagado en nivel `HIGH` y el LED RGB se inicializa en blanco con:

```cpp
analogWrite(pinRGBRed, 255);
analogWrite(pinRGBGreen, 255);
analogWrite(pinRGBBlue, 255);
```

En este montaje, los valores bajos en los canales RGB encienden color y `255` apaga ese canal.
