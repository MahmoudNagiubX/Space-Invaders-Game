# Space Invaders — Source Package

This directory contains the C++14 and raylib implementation of the game.

For the complete project overview, gameplay details, architecture, controls, screenshots, engineering notes, and developer context, see the repository's [main README](../README.md).

## Run Location

Build and run the executable from this directory because the application loads its resources through relative paths:

```text
Font/
Graphics/
Sounds/
highscore.txt
```

## Main Source Modules

```text
src/
├── main.cpp
├── Game.cpp / Game.hpp
├── SpaceShip.cpp / SpaceShip.hpp
├── Alien.cpp / Alien.hpp
├── Laser.cpp / Laser.hpp
├── Obastacle.cpp / Obastacle.hpp
├── Shield.cpp / Shield.hpp
└── MysteryShip.cpp / MysteryShip.hpp
```

The `ball.cpp` and `ball.h` files are retained from the original raylib starter-template workflow and are not part of the Space Invaders game flow.

## Windows Build

From a raylib-configured MinGW/w64devkit terminal:

```bash
g++ -std=c++14 \
  src/main.cpp src/Game.cpp src/SpaceShip.cpp src/Alien.cpp \
  src/Laser.cpp src/Obastacle.cpp src/Shield.cpp src/MysteryShip.cpp \
  -o SpaceInvaders.exe \
  -lraylib -lopengl32 -lgdi32 -lwinmm
```

Then run:

```bash
./SpaceInvaders.exe
```
