# Funcionamiento del Juego

## Flujo general

El `loop()` ejecuta las fases en este orden:

```cpp
combinacionNumerica();
laberinto();
colores();
simon();
morse();
ganar();
```

Cada fase mantiene `jugando = true` y usa un bucle interno hasta que se llama a `superado()` o se produce la derrota. Al superar una fase, `superado()` emite una senal sonora, enciende brevemente el LED verde y cambia `jugando` a `false`.

## Fallos y derrota

La funcion `fallar()` incrementa `fallos`, activa una senal de buzzer y cambia los LEDs rojos segun el numero de fallos:

| Fallos | Estado |
| ---: | --- |
| 1 | LED rojo 1 encendido. |
| 2 | LEDs rojos 1 y 2 encendidos. |
| 3 | Se llama a `perder()` y el juego queda bloqueado. |

`perder()` reproduce una secuencia larga de LEDs rojos y buzzer. Al final entra en `while(true){}`, por lo que la placa debe reiniciarse para volver a jugar.

## Fase 1: combinacion numerica

El jugador introduce cuatro digitos. `*` confirma la respuesta y `#` borra la entrada.

Si se confirma antes de introducir cuatro digitos, cuenta como fallo. Si se introducen mas de cuatro digitos, el buzzer emite una senal breve.

## Fase 2: laberinto

El jugador usa las teclas `2`, `4`, `6` y `8` para seguir una ruta. Cada tecla se compara contra una secuencia interna de movimientos. Un movimiento incorrecto llama a `fallar()`.

## Fase 3: colores

La fase muestra una secuencia de colores con el LED RGB mientras el jugador mantiene pulsada una tecla. Al soltar, `checkValid()` decide si se ha soltado en una ventana valida.

La variable `checkPoint` se activa en un punto concreto de la secuencia. Si el jugador suelta durante una fase valida despues de ese punto, se supera la prueba. La primera pulsacion invalida se ignora por `ignoreFirst`, posiblemente para evitar un fallo accidental al iniciar.

## Fase 4: Simon

El juego muestra una secuencia creciente de colores. El jugador debe repetirla con teclas `A`, `B`, `C` y `D`.

La respuesta esperada cambia segun el numero de fallos acumulados. Cada ronda aumenta la longitud de la secuencia hasta superar cuatro rondas. Si el jugador tarda mas de 8 segundos en introducir una tecla durante una ronda, la ronda se reinicia.

## Fase 5: Morse

El LED RGB muestra una secuencia de destellos en azul. El jugador debe interpretar la secuencia y escribir una clave de cuatro digitos. `*` confirma y `#` borra.

## Victoria

Tras superar Morse, `loop()` llama a `ganar()`, que deja encendido el LED verde y apaga los LEDs rojos.
