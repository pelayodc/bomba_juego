# Soluciones y Secuencias

Esta pagina contiene spoilers tecnicos del juego. Esta pensada para mantenimiento, pruebas y preparacion de partidas.

## Combinacion numerica

Clave:

```text
1435
```

Uso:

1. Introducir `1`, `4`, `3`, `5`.
2. Pulsar `*` para confirmar.

`#` reinicia la entrada.

## Laberinto

Secuencia interna:

```cpp
int password[13] = {0,2,2,3,1,3,2,3,2,0,2,2};
```

Mapa de valores:

| Valor | Tecla | Direccion documentada |
| ---: | --- | --- |
| `0` | `2` | Arriba |
| `1` | `4` | Izquierda |
| `2` | `6` | Derecha |
| `3` | `8` | Abajo |

Secuencia de teclas:

```text
2 6 6 8 4 8 6 8 6 2 6 6
```

Nota tecnica: el array esta declarado con 13 posiciones, pero contiene 12 valores. La fase se supera cuando `pos == 12`, por lo que la secuencia efectiva tiene 12 movimientos.

## Colores

La prueba de colores no usa una clave escrita. El jugador debe mantener una tecla pulsada para iniciar la secuencia y soltar en una ventana valida despues de que se active `checkPoint`.

Secuencia de colores en `mostrarLuz()`:

| Fase | Color aproximado | RGB escrito |
| ---: | --- | --- |
| 0 | Azul | `(0, 0, 255)` |
| 1 | Amarillo | `(255, 255, 0)` |
| 2 | Verde azulado | `(0, 255, 128)` |
| 3 | Azul | `(0, 0, 255)` |
| 4 | Cian | `(0, 255, 255)` |
| 5 | Magenta | `(255, 0, 255)` |
| 6 | Amarillo | `(255, 255, 0)` |
| 7 | Verde azulado | `(0, 255, 128)` |
| 8 | Azul | `(0, 0, 255)` |

Ventana valida segun `checkValid()`:

```cpp
if ((fase == 0 || fase == 1 || fase == 4) && checkPoint) {
  superado();
}
```

Como `checkPoint` se activa en la fase 5, el jugador debe soltar en una vuelta posterior de la secuencia, cuando `fase` vuelva a `0`, `1` o `4`.

## Simon

El patron visual mostrado es siempre:

```text
Azul, Amarillo, Rojo, Verde
```

La secuencia que debe introducir el jugador depende del numero de fallos acumulados en el momento de jugar Simon:

| Fallos acumulados | Secuencia completa |
| ---: | --- |
| `0` | `D C A B` |
| `1` | `B D C A` |
| `2` o mas | `C B D A` |

La fase se juega por rondas. En la primera ronda se introduce el primer caracter, en la segunda los dos primeros, y asi hasta completar la secuencia.

## Morse

Clave:

```text
3532
```

Uso:

1. Introducir `3`, `5`, `3`, `2`.
2. Pulsar `*` para confirmar.

`#` reinicia la entrada.
