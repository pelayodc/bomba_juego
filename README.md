# Juego Desactivar Bomba

Proyecto de Arduino/ESP32 para un juego de desactivacion de bomba. El montaje usa un teclado matricial 4x4, LEDs de estado, un LED RGB y un buzzer para guiar al jugador por varias pruebas secuenciales.

## Contenido del proyecto

- `bomba_juego/bomba_juego.ino`: sketch principal del juego.
- `manual.docx`: manual narrativo para los jugadores.
- `wiki/`: documentacion tecnica preparada para GitHub Wiki.

## Funcionamiento

El juego se compone de varias fases que se resuelven en orden:

1. Combinacion numerica.
2. Laberinto con teclas de direccion.
3. Prueba de colores.
4. Simon.
5. Morse.
6. Victoria o derrota segun los fallos acumulados.

Cada error aumenta el contador de fallos. Al llegar a tres fallos, el juego ejecuta la secuencia de derrota y queda bloqueado hasta reiniciar la placa.

## Hardware principal

- Teclado matricial 4x4.
- Buzzer en el pin `23`.
- LEDs rojos en los pines `19` y `21`.
- LED verde en el pin `22`.
- LED RGB en los pines `32`, `33` y `13`.

La documentacion completa de conexiones esta en [wiki/Instalacion-y-Hardware.md](wiki/Instalacion-y-Hardware.md).

## Documentacion

La carpeta [wiki](wiki) contiene paginas Markdown listas para copiar o sincronizar con GitHub Wiki:

- [Inicio](wiki/Home.md)
- [Instalacion y Hardware](wiki/Instalacion-y-Hardware.md)
- [Funcionamiento del Juego](wiki/Funcionamiento-del-Juego.md)
- [Soluciones y Secuencias](wiki/Soluciones-y-Secuencias.md)
- [Arquitectura del Codigo](wiki/Arquitectura-del-Codigo.md)
- [Manual del Jugador](wiki/Manual-del-Jugador.md)
- [Mantenimiento y Mejoras](wiki/Mantenimiento-y-Mejoras.md)

La pagina de soluciones contiene spoilers tecnicos del juego.

## Licencia

Este proyecto se distribuye bajo licencia MIT. Consulta [LICENSE](LICENSE) para mas detalles.
