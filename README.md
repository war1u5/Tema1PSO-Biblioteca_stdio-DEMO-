# Tema 1 PSO: _Biblioteca stdio_
_Prelipcean Marius_<br/>
_Grupa: C113D_

## Obiectivele temei
* Familiarizarea cu modul de funcționare al bibliotecii standard input/​output (stdio)
* Aprofundarea conceptelor de:
  * I/O buffering
  * Crearea de procese și rularea de fișiere executabile
  * Redirectearea intrărilor și ieșirilor standard
  * Generarea de biblioteci dinamice

## Enunt
Să se realizeze o implementare minimală a bibliotecii stdio, care să permită lucrul cu fișiere. Biblioteca va trebui să implementeze structura SO_FILE (similar cu FILE din biblioteca standard C), împreună cu funcțiile de citire/scriere. De asemenea, va trebui să ofere funcționalitatea de buffering. <br/>
Rezolvarea temei va trebui să genereze o bibliotecă dinamică numită libso_stdio.so/so_stdio.dll care implementează funcțiile declarate în header-ul [so_stdio.h](https://github.com/systems-cs-pub-ro/so/blob/master/assignments/2-stdio/util/so_stdio.h).
