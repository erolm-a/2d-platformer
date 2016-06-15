# README #

Benvenuti nel più brutto ma anche nel più libero clone di CatMario (chiamato qui banalmente "platformer")

### Versioni? ###

A parte la fisica del gioco, non c'è molto di interessante da fare; potete sempre aggiungere nuovi oggetti. Data la natura molto OOP del gioco, è facile aggiungere nuovi modelli, a partire dal gestore di livelli.

### Cosa devo fare per prepararmi allo sviluppo? ###

I software usati sono:

* Qt Creator (versione 4 o 5);
* Compilatore GCC che supporta C++11
* Librerie SDL2 (SDL2, SDL2_image, SDL2_ttf, SD2_mixer)
* Tiled (http://www.mapeditor.org) che offre un editor di mappe 2d molto efficace.

Per installare le librerie sdl2 è necessario consultare le varie guide della propria distribuzione (nel caso di Linux e Mac OS X) o della posizione delle librerie (nel caso di Windows).

Per esempio, sulle distro Debian-like:


```
#!bash

sudo apt-get install libsdl2{,-mixer,-ttf,-image}{,-dev}

```

Per Gentoo Linux:

```
#!bash

sudo emerge sdl2-mixer sdl2-image sdl2-ttf libsdl2

```


In seguito bisogna modificare con un editor testuale il file Platformer_v0-0.pro e modificare le righe INCLUDEPATH e LIBS in questo modo su Linux e Mac OS X:


```


INCLUDEPATH += /usr/include/SDL2
LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

```

Su Windows bisogna specificare dove si sono installati gli header e le librerie.

## Licenza ##


Il progetto è distribuito secondo la licenza **GPLv3**, seppure alcune parti (le risorse png nella cartella build-*) sono rielaborati del prodotto altrui, di cui non ricordo il nome né la fonte.